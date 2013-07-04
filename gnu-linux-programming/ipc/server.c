/*
   server.c,
   a socket server program.
*/
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 2571
#define MAX 1024

char *GetLine(int fd)
{
   char netread[MAX+4], readch;
   ssize_t n;
   int len;

   len = 0;

   while (len < MAX) {
      n = read(fd, &readch, 1);

      if (n <= 0) break;
      if (strncmp(&readch, "\n", 1) == 0) break;

      netread[len++] = readch;
   }

   netread[len] = '\0';
   return netread;
}

int HandleMsgs(char *s)
{
   if (s[0] == '\0') 
      return -1;
   else if (strncmp(s, "quit", 4) == 0)
      return -1;
   return 0;
}

int main(int argc, char *argv[])
{
   int sockfd;
   int client_sockfd, len;
   int r;
   char msg[MAX+4];
   struct sockaddr_in server_addr;
   struct sockaddr_in client_addr;

   /* 1. Create a socket. */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == -1) {
      perror(NULL);
      exit(1);
   }

   /* 2. Bind an address to the socket. */
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   server_addr.sin_port = htons(PORT);

   if (bind(sockfd, &server_addr, sizeof(struct sockaddr_in)) < 0) {
      perror(NULL);
      exit(1);
   }

   /* 3. Listen for connections. */
   printf("Listening for connections...\n");
   listen(sockfd, 5);

   /* 4. Accept connections. */
   len = sizeof(struct sockaddr_in);
   client_sockfd = accept(sockfd, &client_addr, &len);

   if (client_sockfd == -1) {
      perror(NULL);
      exit(1);
   }
   printf("Connection Accepted!\n\n");

   /* Receiving and handling messages. */
   r = 0;
   while (1) {
      strcpy(msg, GetLine(client_sockfd));
      r = HandleMsgs(msg);

      if (r == -1) break;
      printf("Receive: %s\n", msg);
   }

   close(client_sockfd);
   exit(0);
}
