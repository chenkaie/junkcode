#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFSIZE 255
void Die(char *mess) { perror(mess); printf("\n"); exit(1); }

int main(int argc, char *argv[]) 
{
    int RecvSock;
    struct sockaddr_in echoserver;
    struct sockaddr_in echoclient;
    char buffer[BUFFSIZE];
    unsigned int echolen, clientlen, serverlen;
    int received = 0;
    if (argc != 2) 
    {
        fprintf(stderr, "USAGE: %s <port>\n", argv[0]);
        exit(1);
    }
    
    /* Create the UDP socket */
    if ((RecvSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
    {
        Die("Failed to create socket");
    }
    
    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
    echoserver.sin_family = AF_INET; /* Internet/IP */
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY); /* Any IP address */
    echoserver.sin_port = htons(atoi(argv[1])); /* server port */
    
    /* Bind the socket */
    serverlen = sizeof(echoserver);
    if (bind(RecvSock, (struct sockaddr *) &echoserver, serverlen) < 0) 
    {
        Die("Failed to bind server socket");
    }

    memset(&buffer, 0, sizeof(buffer)); /* Clear struct */
    /* Receive a message from the client */
    clientlen = sizeof(echoclient);
    if ((received = recvfrom(RecvSock, buffer, BUFFSIZE, 0,
        (struct sockaddr *) &echoclient,
        &clientlen)) < 0) 
    {
        Die("Failed to receive message");
    }
    
    fprintf(stderr,"recv %s\n", buffer);

    if ((received = recvfrom(RecvSock, buffer, BUFFSIZE, 0,
        (struct sockaddr *) &echoclient,
        &clientlen)) < 0) 
    {
        Die("Failed to receive message");
    }
    buffer[received] = '\0';

    fprintf(stderr,"recv PortAddress = %s at client: %s\n", buffer,inet_ntoa(echoclient.sin_addr));

    close(RecvSock);



    int SendSock;

    /* Create the UDP socket */
    if ((SendSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
    {
        Die("Failed to create socket");
    }
    
    /* Construct the server sockaddr_in structure for sending messaged to Server*/
    memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
    echoserver.sin_family = AF_INET; /* Internet/IP */
    echoserver.sin_addr.s_addr = echoclient.sin_addr.s_addr; /* IP address */
    echoserver.sin_port = htons(atoi(buffer)); /* server port */

    /* Send the word to the server */
    sprintf(buffer,"Send back you");
    echolen = strlen(buffer);
    if (sendto(SendSock, buffer, echolen, 0,
        (struct sockaddr *) &echoserver,
        sizeof(echoserver)) != echolen) 
    {
        Die("Mismatch in number of sent bytes");
    }

    fprintf(stderr,"Send back to IP = %s, Port = %d\n", inet_ntoa(echoclient.sin_addr),ntohs(echoserver.sin_port));
    close(SendSock);

    exit(EXIT_SUCCESS);
}
