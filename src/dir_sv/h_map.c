#include<stdio.h>

#include"mem_mgr.h"
#include"h_map.h"

struct h_map_t *h_map_alloc(int rows)
{
	struct h_map_t *h_map=alloc("struct h_map_t", 1);
	h_map->rows=rows;
	h_map->bands=alloc("struct band_t *", rows);

	for(int i=0; i<h_map->rows; i++){
		h_map->bands[i]=alloc("struct band_t", 1);
		h_map->bands[i]->ctrlr=alloc_list();
		h_map->bands[i]->cli=alloc_list();
	}

	return h_map;
}

void h_map_dealloc(struct h_map_t *h_map)
{
	for(int i=0; i<h_map->rows; i++){
		dealloc_list(h_map->bands[i]->ctrlr, 1);
		dealloc_list(h_map->bands[i]->cli, 0);
		dealloc("struct band_t", 1, h_map->bands[i]);
	}

	dealloc("struct band_t *", 1, h_map->bands);
	dealloc("struct h_map_t", 1, h_map);
}

int h_map_key(char *ip, int rows)
{
	char *ptr=ip;
	int count=0;

	while(*ptr!='\0'){
		count+=(int)*ptr;
		ptr+=sizeof(char);
	}

	return count%rows;
}

void h_map_add(struct h_map_t *h_map, char *ip, int uid)
{
	struct node *curr;
	int key=h_map_key(ip, h_map->rows);

	if(!uid){
		//ctrlr registering itself for the first time
		curr=alloc_node(ip, 0);
		add_node(h_map->bands[key]->ctrlr, curr);

	}else{
		//pre-registered ctrlr registering a client
		curr=alloc_node(NULL, uid);
		struct node *ctrlr=h_map_find(h_map, ip, 0);
		curr->cli.ctrlr=ctrlr;
		add_node(h_map->bands[key]->cli, curr);

	}
}

struct node *h_map_find(struct h_map_t *h_map, char *ip, int uid)
{
	struct node *curr=NULL;
	int key=h_map_key(ip, h_map->rows);

	if(!uid){
		//find a ctrlr
		curr=find_memb(h_map->bands[key]->ctrlr, ip, 0);

	}else{
		//find a client
		curr=find_memb(h_map->bands[key]->cli, NULL, uid);
	}

	return curr;
}
