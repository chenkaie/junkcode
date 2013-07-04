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
    unsigned int echolen;
    int yes = 1;
    if (argc != 3) 
    {
        fprintf(stderr, "USAGE: %s <port> <word>\n", argv[0]);
        exit(1);
    }
 
   /* Create the UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
    {
        Die("Failed to create socket");
    }

#if 0
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
    echoserver.sin_port = htons(atoi(argv[1]));
    echoserver.sin_family = PF_INET;
 
    if (bind(sock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0) 
    {
        Die("Failed to bind server socket");
    }
#endif

    if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int)) < 0)
    {
        Die("Failed to bind server socket");
    }

    /* -1 = 255.255.255.255 this is a BROADCAST address,
       a local broadcast address could also be used.
       you can comput the local broadcat using NIC address and its NETMASK */
 
    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
    echoserver.sin_family = PF_INET; 
    //echoserver.sin_addr.s_addr = htonl(INADDR_BROADCAST); //  #define INADDR_BROADCAST    ((in_addr_t) 0xffffffff)
    echoserver.sin_addr.s_addr = inet_addr("192.168.101.255");
    echoserver.sin_port = htons(atoi(argv[1])); /* server port */

    /* Send the word to the server */
    echolen = strlen(argv[2]);
    if (sendto(sock, argv[2], echolen, 0, (struct sockaddr *) &echoserver, sizeof(echoserver)) != echolen) 
    {
        Die("Mismatch in number of sent bytes");
    }

    echoserver.sin_addr.s_addr = inet_addr("172.16.255.255");
    if (sendto(sock, argv[2], echolen, 0,
        (struct sockaddr *) &echoserver,
        sizeof(echoserver)) != echolen) 
    {
        Die("Mismatch in number of sent bytes");
    }

    close(sock);
    exit(EXIT_SUCCESS);
}
