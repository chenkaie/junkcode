/*
   web.c,
   a dirty embedded Web server.
*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define CR '\r'
#define LF '\n'

#define PORT 6001
#define MAX 4096

int http_get;

char *GetLine(int fd)
{
   char netread[MAX], readch;
   ssize_t n;
   int len;

   len = 0;
   netread[0] = CR;
   netread[1] = LF;

   while (len < MAX) {
      n = read(fd, &readch, 1);
      if (n <= 0) break;

      netread[len++] = readch;
      if (readch == LF) break;
   }

   netread[len] = '\0';
   return netread;
}

int HandleMsgs(char *s)
{
   if (s[0] == CR && s[1] == LF)
      return -1;
   else if (strncmp(s, "GET", 3) == 0)
      http_get = 1;
   return 0;
}

int main(int argc, char *argv[])
{
   int sockfd;
   int client_sockfd, len;
   int r;
   char msg[MAX];
   struct sockaddr_in server_addr;
   struct sockaddr_in client_addr;

   /* 1. Create a socket. */
   sockfd = socket(PF_INET, SOCK_STREAM, 0);
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

   /* Start Web server. */
   for (;;) {
      listen(sockfd, 25);

      len = sizeof(struct sockaddr_in);
      client_sockfd = accept(sockfd, &client_addr, &len);

      if (client_sockfd == -1) {
         perror(NULL);
         exit(1);
      }

      r = 0;

      /* http initialize */
      http_get = 0;

      while (r != -1) {
         strcpy(msg, GetLine(client_sockfd));
         r = HandleMsgs(msg);
         printf("%s\n", msg);
      }

      if (http_get) {
         printf("[Response to client.]\n");
         write(client_sockfd, "<HTML>\n", 7);
         write(client_sockfd, "<H3>HELLO!</H3>\n", 16);
         write(client_sockfd, "</HTML>\n\n", 8);
         write(client_sockfd, '\0', 1);
      }

      close(client_sockfd);
   }
}
