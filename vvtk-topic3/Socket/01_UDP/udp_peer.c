#include <stdio.h>
#include <stdlib.h>		/* atoi */
#include <string.h>		/* memset */
#include <unistd.h>		/* sleep */
/* For socket */
#include <sys/types.h>	/* socket, bind */
#include <sys/socket.h> /* socket, bind */
#include <netinet/in.h> /* sockaddr_in */
#include <arpa/inet.h>	/* htons, htonl */
/* For pthread */
#include <pthread.h>	/* pthread_create */


#define BUFFERSIZE	4096
#define SEND_INTERVAL	5


void MyError(char *pcMessage)
{
	perror(pcMessage);
	exit(EXIT_FAILURE);
}

void *RecvData(void *pvSocket)
{
	int iSocket;
	int iReceived;
	unsigned int uiClientLen;
	char acBuffer[BUFFERSIZE];
	struct sockaddr_in addrClient;

	iSocket = *((int *) pvSocket);
	while (1)
	{
		uiClientLen = sizeof(addrClient);
		iReceived = recvfrom(iSocket, acBuffer, BUFFERSIZE, 0, 
					(struct sockaddr *) &addrClient, &uiClientLen);
		acBuffer[iReceived] = '\0';
		printf("%s from %s:%d\n", acBuffer, inet_ntoa(addrClient.sin_addr), 
				ntohs(addrClient.sin_port));
	}

	pthread_exit(NULL);
}

int main(int iArgc, char *acArgv[])
{
	int iSocket;
	struct sockaddr_in addrServer;
	struct sockaddr_in addrRemote;
	char *pcRemoteIP, *pcRemotePort;
	int iServerLen;
	pthread_t tThread;

	if (iArgc != 4)
	{
		fprintf(stderr, "Usage: udp_peer <remote_ip> <remote_port> <local_port>\n");
		exit(EXIT_FAILURE);
	}

	/* Create the UDP socket */
	iSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (iSocket < 0)
	{
		MyError("Failed to create socket");
	}

	pcRemoteIP = acArgv[1];
	pcRemotePort = acArgv[2];

	iServerLen = sizeof(addrServer);
	memset(&addrServer, 0, iServerLen);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(atoi(acArgv[3]));
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Bind the socket */
	if (bind(iSocket, (struct sockaddr *) &addrServer, iServerLen) < 0)
	{
		MyError("Failed to bind socket");
	}
	
	/* A thread to receive data */
	pthread_create(&tThread, NULL, RecvData, (void *) &iSocket);
	
	/* Master thread to send data */
	addrRemote.sin_family = AF_INET;
	addrRemote.sin_port = htons(atoi(pcRemotePort));
	addrRemote.sin_addr.s_addr = inet_addr(pcRemoteIP);
	while (1)
	{
		sendto(iSocket, "hello", strlen("hello"), 0, 
				(struct sockaddr *) &addrRemote, sizeof(addrRemote));
		sleep(SEND_INTERVAL);
	}

	close(iSocket);
	pthread_exit(NULL);

	return 0;
}
