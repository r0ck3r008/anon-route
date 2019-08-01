#include<stdio.h>

#include"mem_mgr.h"
#include"node.h"

void add_node(struct node *start, struct node *new)
{
	struct node *curr=start;

	for(curr; curr->nxt!=NULL; curr=curr->nxt);
	curr->nxt=new;
	new->prev=curr;
}

struct node *alloc_node(char *ip, int uid)
{
	struct node *new=alloc("struct node", 1);

	if(ip!=NULL){
		new->ip=alloc("char", 512);
		sprintf(new->ip, "%s", ip);
	}else{
		new->ip=NULL;
	}
	new->uid=uid;
	new->nxt=NULL;
	new->prev=NULL;

	return new;
}

void dealloc_node(struct node *curr)
{
	if(curr->ip!=NULL)
		dealloc("char", 512, curr->ip);

	dealloc("struct node", 1, curr);
}

struct node *alloc_list()
{
	struct node *start=alloc_node("START", -1);

	return start;
}

void dealloc_list(struct node *start)
{
	struct node *curr=start->nxt;
	for(curr; start->nxt!=NULL;){
		start->nxt=curr->nxt;
		if(curr->nxt!=NULL)
			curr->nxt->prev=start;
		dealloc_node(curr);
		curr=start->nxt;
	}

	dealloc_node(start);
}

struct node *find_memb(struct node *start, int uid)
{
	int flag=0;
	struct node *curr=start->nxt;
	for(curr; curr!=NULL; curr=curr->nxt){
		if(curr->uid==uid){
			flag=1;
			break;
		}
	}

	if(flag)
		return curr;
	return NULL;
}
