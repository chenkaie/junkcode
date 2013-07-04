#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 255
#define GROUP_PORT 3838
#define GROUP_IP "225.0.0.37"

void Die(char *mess) 
{ 
	perror(mess); exit(1); 
}

int main(int argc, char *argv[]) 
{
	int sock ;
	struct sockaddr_in echoserver;
	struct sockaddr_in echoclient;
	char buffer[BUFFSIZE];
	unsigned int clientlen, serverlen;
	int received = 0;
	int yes=1;
	struct ip_mreq mreq;


	if (argc != 1) 
	{
		fprintf(stderr, "USAGE: %s \n", argv[0]);
		exit(1);
	}

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
	{
		Die("Failed to create socket");
	}

	/* allow multiple sockets to use the same PORT number */
    if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) 
	{
       Die("Reusing ADDR failed");
    }
	
	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
	echoserver.sin_family = AF_INET; /* Internet/IP */
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY); /* Any IP address */
	/*echoserver.sin_addr.s_addr = inet_addr("172.16.5.31");*/
	echoserver.sin_port = htons(GROUP_PORT); /* server port */
	
	/* Bind the socket */
	serverlen = sizeof(echoserver);
	if (bind(sock, (struct sockaddr *) &echoserver, serverlen) < 0) 
	{
		Die("Failed to bind server socket");
	}

	/* use setsockopt() to request that the kernel join a multicast group */
     mreq.imr_multiaddr.s_addr=inet_addr(GROUP_IP);
	 mreq.imr_interface.s_addr=htonl(INADDR_ANY);
	 /*mreq.imr_interface.s_addr=inet_addr("172.16.5.31");*/

     if (setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) 
	 {
		 Die("setsockopt");
     }

     /* now just enter a read-print loop */
	 while(1)
	 {

		/* Receive a message from the client */
		clientlen = sizeof(echoclient);
		if ((received = recvfrom(sock, buffer, BUFFSIZE, 0, (struct sockaddr *) &echoclient, &clientlen)) < 0) 
		{
			Die("Failed to receive message");
		}
		buffer[received] = '\0';
		fprintf(stderr, "Receive from: %s\n", inet_ntoa(echoclient.sin_addr));
		fprintf(stderr, "receive: %s\n", buffer);

	 }
	 
	 close(sock);
	 exit(0);
}

