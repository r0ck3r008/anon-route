#ifndef H_MAP_H
#define H_MAP_H

#include"node.h"

struct band_t{
	struct node *ctrlr;
	struct node *cli;
};

struct h_map_t{
	int rows;
	struct band_t **bands;
};

struct h_map_t *h_map_alloc(int);
void h_map_dealloc(struct h_map_t *);
int h_map_key(char *, int);
void h_map_add(struct h_map_t *, char *, int);
struct node *h_map_find(struct h_map_t *, char *, int);

#endif
