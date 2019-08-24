#include<stdio.h>

#include"h_map.h"

int main(int argc, char *argv[])
{
	struct h_map_t *h_map=h_map_alloc(10);

	h_map_add(h_map, argv[1], 0);
	h_map_add(h_map, argv[1], 23);

	h_map_dealloc(h_map);
}
