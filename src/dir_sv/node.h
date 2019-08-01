#ifndef NODE_H
#define NODE_H

struct node
{
	int uid;
	char *ip;
	struct node *nxt;
	struct node *prev;
};

void add_node(struct node *, struct node *);
struct node *alloc_node(char *, int);
void dealloc_node(struct node *);
struct node *alloc_list();
void dealloc_list(struct node *);
struct node *find_memb(struct node *, int);

#endif
