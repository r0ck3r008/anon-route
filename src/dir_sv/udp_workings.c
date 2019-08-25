#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>

#include"mem_mgr.h"
#include"h_map.h"
#include"udp_workings.h"

int sock_create(char *addr)
{
	int sock=-1;
	int flag=0;

	if((sock=socket(AF_INET, SOCK_DGRAM, 0))==-1){
		fprintf(stderr, "[-]Error in creating the socket: %s\n",
			strerror(errno));
		goto exit;
	}

	struct sockaddr_in addr_in;
	explicit_bzero(&addr_in, sizeof(struct sockaddr_in));
	addr_in.sin_family=AF_INET;
	addr_in.sin_addr.s_addr=inet_addr(strtok(addr, ":"));
	addr_in.sin_port=htons(strtol(strtok(NULL, ":"), NULL, 10));

	if(bind(sock, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in))<0){
		fprintf(stderr, "[-]Error in binding the socket: %s\n",
			strerror(errno));
		flag=1;
	}

exit:
	if(flag){
		close(sock);
		sock=-1;
	}

	return sock;
}

void sig_callback(int signal)
{
	printf("[!]Received signal %d\n[!]Cleaning up memory now...\t", signal);

	//clear memory here

	printf("Done!\n");
	close(srv_sock);
	_exit(0);
}

void udp_workings(char *addr)
{
	if(signal(SIGINT, sig_callback)==SIG_ERR)
		_exit(-1);

	srv_sock=sock_create(addr);
	if(srv_sock==-1)
		_exit(-1);

	char *cmdr, *cmds;
	struct sockaddr_in cli_addr;
	struct sockaddr_in *cli_addr_ptr=&cli_addr;
	while(1){
		cmds=alloc("char", 512);
		explicit_bzero(&cli_addr, sizeof(struct sockaddr_in));

		if((cmdr=rcv(srv_sock, &cli_addr_ptr))==NULL)
			goto loop_restart;

		//various conditions


loop_restart:
		dealloc("char", 512, cmdr);
	}
}

char *rcv(int sock, struct sockaddr_in **addr)
{
	char *cmdr=alloc("char", 512);
	socklen_t len=sizeof(struct sockaddr_in);
	int flag=0;

	if(recvfrom(sock, cmdr, sizeof(char)*512,
			0, (struct sockaddr *)*addr, &len)==-1){
		fprintf(stderr, "[-]Error in receving from sock %d: %s\n",
			sock, strerror(errno));
		flag=1;
	}

	if(flag){
		dealloc("char", 512, cmdr);
		cmdr=NULL;
	}

	return cmdr;
}

void snd(int sock, char *cmds, struct sockaddr_in *addr)
{
	socklen_t len=sizeof(struct sockaddr_in);
	if(sendto(sock, cmds, sizeof(char)*512, 0,
			(struct sockaddr *)addr, len)==-1){
		fprintf(stderr, "[-]Error in sending to %s: %s\n",
			inet_ntoa(addr->sin_addr), strerror(errno));
	}

	dealloc("char", 512, cmds);
}
