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
    int SendSock;
    struct sockaddr_in echoserver;
    struct sockaddr_in echoclient;
    char buffer[BUFFSIZE];
    unsigned int echolen, clientlen;
    int received = 0;
    if (argc != 5) 
    {
        fprintf(stderr, "USAGE: %s <server_ip> <word> <R_port> <L_port>\n", argv[0]);
        exit(1);
    }
 
   /* Create the UDP socket */
    if ((SendSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
    {
        Die("Failed to create socket");
    }
    
    /* Construct the server sockaddr_in structure for sending messaged to Server*/
    memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
    echoserver.sin_family = AF_INET; /* Internet/IP */
    echoserver.sin_addr.s_addr = inet_addr(argv[1]); /* IP address */
    echoserver.sin_port = htons(atoi(argv[3])); /* server port */

    /* Send the word to the server */
    echolen = strlen(argv[2]);
    if (sendto(SendSock, argv[2], echolen, 0,
        (struct sockaddr *) &echoserver,
        sizeof(echoserver)) != echolen) 
    {
        Die("Mismatch in number of sent bytes");
    }
    
    echolen = strlen(argv[4]);
    if (sendto(SendSock, argv[4], echolen, 0,
        (struct sockaddr *) &echoserver,
        sizeof(echoserver)) != echolen) 
    {
        Die("Mismatch in number of sent bytes");
    }

    printf("send %s to Remote IP = %s, port = %d\n",
           argv[2],inet_ntoa(echoserver.sin_addr) ,ntohs(echoserver.sin_port));

    /* close this socket */
    close(SendSock);

    int RecvSock;
    /* Create the UDP socket */
    if ((RecvSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
    {
        Die("Failed to create socket");
    }

    /* Construct another server sockaddr_in structure for receiving message from server*/
    memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
    echoserver.sin_family = AF_INET; /* Internet/IP */
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY);  /* IP address */
    echoserver.sin_port = htons(atoi(argv[4])); /* server port */

    /* Bind the socket */
    if (bind(RecvSock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0)
    {
        Die("Failed to bind server socket");
    }

    /* Receive the word back from the server */
    fprintf(stdout, "Received: ");
   
    clientlen = sizeof(echoclient);
    if ((received = recvfrom(RecvSock, buffer, BUFFSIZE, 0,
        (struct sockaddr *) &echoclient,
        &clientlen)) < 0) 
    {
        Die("Failed to receive message");
    }


    /* Check that client and server are using same socket 
    if (echoserver.sin_addr.s_addr != echoclient.sin_addr.s_addr) 
    {
        Die("Received a packet from an unexpected server");
    }*/

    buffer[received] = '\0'; /* Assure null-terminated string */
    printf("(%s), len = %d", buffer, received);


    printf(" at Local  IP = %s, port = %d\n",inet_ntoa(echoserver.sin_addr) ,ntohs(echoserver.sin_port));

    close(RecvSock);
    exit(EXIT_SUCCESS);
}
