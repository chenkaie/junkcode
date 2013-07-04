#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFSIZE 255
void Die(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) 
{
    int sock;
    struct sockaddr_in echoserver;
    struct sockaddr_in echoclient;
    char buffer[BUFFSIZE];
    unsigned int echolen, clientlen;
    int received = 0;
    if (argc != 4) 
    {
        fprintf(stderr, "USAGE: %s <server_ip> <word> <port>\n", argv[0]);
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
    echoserver.sin_addr.s_addr = inet_addr(argv[1]); /* IP address */
    echoserver.sin_port = htons(atoi(argv[3])); /* server port */

    /* Send the word to the server */
    echolen = strlen(argv[2]);
    if (sendto(sock, argv[2], echolen, 0,
        (struct sockaddr *) &echoserver,
        sizeof(echoserver)) != echolen) 
    {
        Die("Mismatch in number of sent bytes");
    }

    /* Receive the word back from the server */
    fprintf(stdout, "Received: ");
    clientlen = sizeof(echoclient);
    if ((received = recvfrom(sock, buffer, BUFFSIZE, 0,
        (struct sockaddr *) &echoclient,
        &clientlen)) != echolen) 
    {
        Die("Mismatch in number of received bytes");
    }

    /* Check that client and server are using same socket */
    if (echoserver.sin_addr.s_addr != echoclient.sin_addr.s_addr) 
    {
        Die("Received a packet from an unexpected server");
    }

    buffer[received] = '\0'; /* Assure null-terminated string */
    fprintf(stdout, buffer);
    fprintf(stdout, "\n");
    close(sock);
    exit(EXIT_SUCCESS);
}
