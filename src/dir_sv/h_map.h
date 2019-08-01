#ifndef H_MAP_H
#define H_MAP_H

#include"node.h"

struct h_map_t
{
	struct node *ctrlrs;
	struct node *clients;
};

struct h_map_t **h_map_alloc(int);
void h_map_dealloc(struct h_map_t **, int);

#endif
