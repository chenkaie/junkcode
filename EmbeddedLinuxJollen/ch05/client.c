/*
   client.c,
   a socket client program.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 2571
#define MAX 1024

void HandleMsgs(int fd)
{
  char buff[MAX+4];

  while (1) {
     scanf("%s", buff);
     if (strlen(buff) > MAX) buff[MAX-1] = '\0';

     if (strncmp(buff, "quit", 4) == 0) {
        return;
     } else {
        write(fd, buff, strlen(buff));
        write(fd, "\n", 1);
        printf("Sent: %s\n", buff);
     }
   }
}

int main(int argc, char *argv[])
{
   int sockfd;		/* socket's file descriptor */
   struct sockaddr_in serv_addr;

   if (argc != 2) {
      fprintf(stderr, "Usage: %s server_IPaddr\n", argv[0]);
      exit(1);
   }

   /* 1. Create a socket. */
   sockfd = socket(PF_INET, SOCK_STREAM, 0);
   if (sockfd == -1) {
      perror("create socket failed");
      exit(1);
   }

   /* 2. Connect to server. */
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
   serv_addr.sin_port = htons(PORT);

   if (connect(sockfd, &serv_addr, sizeof(struct sockaddr_in)) < 0) {
      perror(NULL);
      exit(1);
   }

   printf("type 'quit' to exit.\n\n");
   HandleMsgs(sockfd);
   close(sockfd);
   exit(0);
}
