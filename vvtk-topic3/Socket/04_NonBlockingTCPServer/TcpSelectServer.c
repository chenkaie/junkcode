#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "header.h"
#include <time.h>
#include <sys/ioctl.h>

#define MAXPENDING 5 /* Max connection requests */
#define BUFFSIZE 8 
void Die(char *mess) { perror(mess); exit(1); }

#if 0
void HandleClient(int sock) 
{
    char buffer[BUFFSIZE];
    int received = -1;
    /* Receive message */
    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) 
    {
        Die("Failed to receive initial bytes from client");
    }
    buffer[received]='\0';

    printf("Recv Message = \n");
    /* Send bytes and check for more incoming data in loop */
    int i = 1;
    while (received > 0) 
    {
        /* Send back received data */
        if (send(sock, buffer, received, 0) != received) 
        {
            Die("Failed to send bytes to client");
        }
        
        printf("%d-th : %s\n",i,buffer);
   
        /* Check for more data */
        if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) 
        {

            Die("Failed to receive additional bytes from client");
        }
        i++;
    }
    close(sock);
}
#endif

int main(int argc, char *argv[]) 
{
    int serversock, clientsock;
    struct sockaddr_in echoserver, echoclient;
    if (argc != 2) 
    {
        fprintf(stderr, "USAGE: %s <port>\n",argv[0]);
        exit(1);
    }

    /* Create socket */
    serversock = socket(AF_INET, SOCK_STREAM, 0);
    if (serversock < 0) {
       fprintf(stderr, "Error creating socket (%d %s)\n", errno, strerror(errno));
       exit(0);
    }
	
	int value=1;
	setsockopt(serversock,SOL_SOCKET,SO_REUSEADDR,&value,sizeof(value));

    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver)); /* Clear struct */
    echoserver.sin_family = AF_INET; /* Internet/IP */
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY); /* Incoming addr */
    echoserver.sin_port = htons(atoi(argv[1])); /* server port */

    /* Bind the server socket */
    if (bind(serversock, (struct sockaddr *) &echoserver,
    sizeof(echoserver)) < 0) 
    {
        Die("Failed to bind the server socket");
    }

    /* Listen on the server socket */
    if (listen(serversock, MAXPENDING) < 0) 
    {
        Die("Failed to listen on server socket");
    }


    fd_set readset, tempset;
    int maxfd;
    int j, result, result1, sent;
    struct timeval tv;
    char buffer[BUFFSIZE];

    FD_ZERO(&readset); // initialize the readset
    FD_SET(serversock, &readset); //turn on serversock in readset
    maxfd = serversock; //a variable (maxfd) to hold the value of serversock descriptor

    do {
        memcpy(&tempset, &readset, sizeof(tempset));
        tv.tv_sec = 60;
        tv.tv_usec = 0;

        result = select(maxfd + 1, &tempset, NULL, NULL, &tv); 
        /*
           int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

            select() can return one of -1, 0, > 0
            -1: Means an error was encountered, you should do something about it.
            0: Means the call timed out without any event ready for the sockets monitored
            > 0: Is the number of sockets that have events pending (readability, writability, exception-ability ) 
        */

        if (result == 0) 
        {
           printf("select() timed out!\n");
        }
        else if (result < 0 && errno != EINTR) 
        {
           printf("Error in select(): %s\n", strerror(errno));
        }
        else if (result > 0) 
        {
            if (FD_ISSET(serversock, &tempset)) // Test if serversock in tempset is set
            {
                unsigned int clientlen = sizeof(echoclient);
                clientsock = accept(serversock, (struct sockaddr *) &echoclient, &clientlen);
                if (clientsock < 0) 
                {
                    printf("Error in accept(): %s\n", strerror(errno));
                }
                else 
                {
					printf("[accept] ok\n");
					sleep(3);

                    // +--------------------------------------------------------------------------+
                    // | NON-BLOCKING mode note:                                                  |
                    // | Each fd in select must be set to O_NONBLOCK to work properly!            |
                    // | Otherwise some fd which is not set to NON-BLOCK mode would cause whole   |
                    // | select to be blocked!                                                    |
                    // +--------------------------------------------------------------------------+
                    
/*#define _NON_BLOCKING_MODE*/
#ifdef _NON_BLOCKING_MODE
                    /* Set non-blocking Start*/                                              
                    int arg = 0;                                                             
                    if( (arg = fcntl(clientsock, F_GETFL, NULL)) < 0) {              
                        fprintf(stderr, "Error fcntl(..., F_GETFL) (%s)\n", strerror(errno));
                        exit(0);
                    }
                    arg |= O_NONBLOCK;
                    if( fcntl(clientsock, F_SETFL, arg) < 0) {
                        fprintf(stderr, "Error fcntl(..., F_SETFL) (%s)\n", strerror(errno));
                        exit(0);
                    }
                    /* Set non-blocking End*/
#endif 
                    FD_SET(clientsock, &readset); // Turn on clientsock fd in readset
                    maxfd = (maxfd < clientsock)?clientsock:maxfd;
                }
				FD_CLR(serversock, &tempset);
            }
        
			printf("[for] scan fd from 0 to maxfd: %d\n", maxfd);

			/*
			 * [Kent] it may call recv() more than once, if recv data is
			 * larger than BUFFSIZE.
			 * Therefore it won't be blocked even we don't set clientsock 
			 * non-blocking mode, because it use FD_ISSET() to check if a
			 * fd is readable, if not... it won't be selected.
			 */
            for (j = 0; j < maxfd+1; j++) 
            {
                if (FD_ISSET(j, &tempset)) 
                {
					printf("[FD_ISSET]: %d\n", j);

#if 0 
                    // Testing according to uartmgr
                    result = read(j, buffer, BUFFSIZE);
                    //result = ioctl(j, FIONREAD, &result);
                    while (result > 0)
                    {
                        result = read(j, buffer, BUFFSIZE);
                    }
#endif
                    do 
                    {
                        result = recv(j, buffer, BUFFSIZE, 0);
						printf(">> result= %d, errno = %d\n", result, errno);
                    } while (result == -1 && errno == EINTR);

                    if (result > 0) 
                    {
						/*fprintf(stderr, "[%s] recvlen = %d\n", __func__, result);*/
                        buffer[result] = '\0';
                        printf("Echoing: %s\n", buffer);
                        sent = 0;

						/*usleep(30000);*/
                        do{
                              result1 = send(j, buffer+sent, result-sent, MSG_NOSIGNAL);
                              if (result1 > 0)
                              {
                                  sent += result1;
                              }
                              else if ((result1 < 0) && (errno != EINTR))
                              {
                                  break;
                              }
							  /*printf("ohya..., result1= %d\n", result1);*/
                         } while (result > sent);
                     }
                     else if (result == 0) 
                     {
                        printf("result=0 in recv(): %s\n", strerror(errno));
                        close(j);
                        FD_CLR(j, &readset); // Turn off fd j in readset
                     }
                     else // result < 0 
                     {
                        printf("Error in recv(): %s\n", strerror(errno));
                     }
              }      // end if (FD_ISSET(j, &tempset))
           }      // end for (j=0;...)
        }      // end else if (result > 0)
    } while (1);

    return 0;
}


/* this source was from http://www.developerweb.net/forum/showthread.php?t=2933  */
