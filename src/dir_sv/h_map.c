#include<stdio.h>

#include"mem_mgr.h"
#include"h_map.h"

struct h_map_t **h_map_alloc(int rows)
{
	struct h_map_t **h_map=alloc("struct h_map_t *", 1);
	*h_map=alloc("struct h_map_t", rows);
	for(int i=0; i<rows; i++){
		h_map[i]->ctrlrs=alloc_list();
		h_map[i]->clients=alloc_list();
	}
	return h_map;
}

void h_map_dealloc(struct h_map_t **h_map, int rows)
{
	for(int i=0; i<rows; i++){
		dealloc_list(h_map[i]->ctrlrs);
		dealloc_list(h_map[i]->clients);
		dealloc("struct h_map_t", 1, h_map[i]);
	}

	dealloc("struct h_map_t *", 1, h_map);
}
