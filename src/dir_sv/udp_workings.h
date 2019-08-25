#ifndef UDP_WORKINGS_H
#define UDP_WORKINGS_H

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int sock_create(char *);
void udp_workings(char *);
char *rcv(int, struct sockaddr_in **);
void snd(int, char *, struct sockaddr_in *);

#endif
