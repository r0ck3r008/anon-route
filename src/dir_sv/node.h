#ifndef NODE_H
#define NODE_H

struct ctrlr
{
	char *ip;
};

struct client
{
	int uid;
	struct node *ctrlr;
};

struct node
{
	struct node *nxt;
	struct node *prev;
	union
	{
		struct ctrlr ctrlr_node;
		struct client client_node;
	};
};

void add_node(struct node *, struct node *);
struct node *alloc_node(char *, int);
void dealloc_node(struct node *);
struct node *alloc_list();
void dealloc_list(struct node *);
struct node *find_memb(struct node *, int);

#endif
