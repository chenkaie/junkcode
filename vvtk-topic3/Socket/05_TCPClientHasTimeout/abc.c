#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <time.h>
#include <fcntl.h>
//#include <errno.h>

#define BUFFSIZE 32
void Die(char *mess) { perror(mess); exit(1); }

struct sockaddr_in {
  sa_family_t		sin_family;	/* Address family		*/
  unsigned short int	sin_port;	/* Port number			*/
  struct in_addr	sin_addr;	/* Internet address		*/

  /* Pad to size of `struct sockaddr'. */
  unsigned char		__pad[__SOCK_SIZE__ - sizeof(short int) -
			sizeof(unsigned short int) - sizeof(struct in_addr)];
};

int main(int argc, char *argv[]) 
{
    int sock;
    struct sockaddr_in echoserver;
    char buffer[BUFFSIZE];
    unsigned int echolen;
    int received = 0;

    
    if (argc != 4) 
    {
        fprintf(stderr, "USAGE: TCPecho <server_ip> <word> <port>\n");
        exit(1);
    }

    /* Create the TCP socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    {
        Die("Failed to create socket");
    }

    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver));      /* Clear struct */
    echoserver.sin_family = AF_INET;                 /* Internet/IP */
    echoserver.sin_addr.s_addr = inet_addr(argv[1]); /* IP address */
    echoserver.sin_port = htons(atoi(argv[3]));      /* server port */

    /* Establish connection */
    if (connect(sock,
                (struct sockaddr *) &echoserver,
                 sizeof(echoserver)) < 0) {
        Die("Failed to connect with server");
    }

    /* Set a socket as nonblocking */
    //int iFlag = fcntl(sock, F_GETFL);
    //fcntl(sock, F_SETFL, iFlag | O_NONBLOCK);

    struct timeval sv,timeout;
    int svlen = sizeof(sv);
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    /* get the original socket option */
    if (getsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&sv, &svlen) < 0)
    {
        Die("Failed to getsockopt\n");
        return -1;
    }
    printf("Original  : Socket Opt SO_RCVTIMEO = %d,%d\n",(struct timeval *)sv.tv_sec,(struct timeval *)sv.tv_usec);

    /* set the socket recv timeout value */
    if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
        Die("Failed to getsockopt\n");
        return -1;
    }

    /* show the socket option value after set */
    if (getsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&sv, &svlen) < 0)
    {
        Die("Failed to getsockopt\n");
        return -1;
    }
    printf("After Set : Socket Opt SO_RCVTIMEO = %d,%d\n",(struct timeval *)sv.tv_sec,(struct timeval *)sv.tv_usec);

    /* Send the word to the server */
    echolen = strlen(argv[2]);
    if (send(sock, argv[2], echolen, 0) != echolen) 
    {
        Die("Mismatch in number of sent bytes");
    }


    /* Receive the word back from the server */
    fprintf(stdout, "Received: ");
    while (received < echolen)
    {
        int bytes = 0;
        if ((bytes = recv(sock, buffer, 10, 0)) < 1) 
        {
            Die("Failed to receive bytes from server");
        }
        sleep(1);

        received += bytes;
        buffer[bytes] = '\0'; /* Assure null terminated string */
        fprintf(stdout, buffer);
    }
    printf("\n");

    // set back to the original
    setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&sv, sizeof sv);

    return 0;
}
