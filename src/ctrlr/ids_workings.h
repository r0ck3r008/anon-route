#ifndef IDS_WORKIINGS_H
#define IDS_WORKINGS_H

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int sock_create(struct sockaddr_in *, int, int);

#endif
