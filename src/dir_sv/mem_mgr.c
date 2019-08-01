#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"node.h"

void *alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char")){
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	}else if(!strcmp(type, "struct node")){
		ret=malloc(sizeof(struct node)*size);
		explicit_bzero(ret, sizeof(struct node)*size);
	}

	if(ret==NULL){
		fprintf(stderr, "[-]Error in allocating %d bytes for %s type\n"
			);
		_exit(-1);
	}

	return ret;
}

void dealloc(char *type, int size, void *buf)
{
	if(!strcmp(type, "char"))
		explicit_bzero(buf, sizeof(char)*size);
	else if(!strcmp(type, "struct node"))
		explicit_bzero(buf, sizeof(struct node)*size);

	free(buf);
}
