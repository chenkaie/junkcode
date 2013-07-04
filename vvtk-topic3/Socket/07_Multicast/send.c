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



Die(char *mess) 
{
	perror(mess); exit(1); 
}

int main(int argc, char *argv[]) 
{
	int sock;
	struct sockaddr_in echoserver;

	unsigned int echolen ;

	if (argc != 2) 
	{
		fprintf(stderr, "USAGE: %s <word>\n", argv[0]);
		exit(1);
	}
	
	/* Create the UDP socket */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
	{
		Die("Failed to create socket");
	}

	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
	echoserver.sin_family = AF_INET; /* Internet/IP */
	echoserver.sin_port = htons(GROUP_PORT); /* server port */
	echoserver.sin_addr.s_addr = inet_addr(GROUP_IP);

	/* Send the word to the server */
	echolen = strlen(argv[1]);
	if (sendto(sock, argv[1], echolen, 0, (struct sockaddr *) &echoserver, sizeof(echoserver)) != echolen) 
	{
		Die("Mismatch in number of sent bytes");
	}

	close(sock);
	exit(0);
}

