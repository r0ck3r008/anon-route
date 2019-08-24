#ifndef NODE_H
#define NODE_H

struct ctrlr_node{
	char *ip;
};

struct cli_node{
	int uid;
	struct node *ctrlr;
};

struct node{
	struct node *nxt, *prev;
	union{
		struct ctrlr_node ctrlr;
		struct cli_node cli;
	};
};

struct node *alloc_list();
void dealloc_list(struct node *, int);
struct node *alloc_node(char *, int);
void dealloc_node(struct node *, int);
void add_node(struct node *, struct node *);
struct node *find_memb(struct node *, char *, int);

#endif
