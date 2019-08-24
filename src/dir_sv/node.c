#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"mem_mgr.h"
#include"node.h"

struct node *alloc_list()
{
	struct node *start=alloc_node("START", 0);

	return start;
}

void dealloc_list(struct node *start, int flag)
{
	struct node *curr=start->nxt;
	for(curr; start->nxt!=NULL; curr=start->nxt){
		start->nxt=curr->nxt;
		if(curr->nxt!=NULL)
			curr->nxt->prev=curr->prev;

		dealloc_node(curr, flag);
	}

	dealloc_node(start, 1);
}

struct node *alloc_node(char *ip, int uid)
{
	struct node *curr=alloc("struct node", 1);
	if(ip!=NULL){
		curr->ctrlr.ip=alloc("char", 128);
		sprintf(curr->ctrlr.ip, "%s", ip);
	}else{
		curr->cli.uid=uid;
		curr->cli.ctrlr=NULL;
	}
	curr->nxt=NULL;
	curr->prev=NULL;

	return curr;
}

void dealloc_node(struct node *curr, int flag)
{
	if(flag)
		dealloc("char", 128, curr->ctrlr.ip);

	dealloc("struct node", 1, curr);
}

void add_node(struct node *start, struct node *new)
{
	struct node *curr=start;
	for(curr; curr->nxt!=NULL; curr=curr->nxt);

	curr->nxt=new;
	new->prev=curr;
}

struct node *find_memb(struct node *start, char *ip, int uid)
{
	struct node *curr=start;
	int flag=0;

	if(ip!=NULL){
		for(curr; curr!=NULL; curr=curr->nxt){
			if(!strcmp(ip, curr->ctrlr.ip)){
				flag=1;
				break;
			}
		}
	}else{
		for(curr; curr!=NULL; curr=curr->nxt){
			if(uid==curr->cli.uid){
				flag=1;
				break;
			}
		}
	}

	if(!flag)
		return NULL;
	return curr;
}
