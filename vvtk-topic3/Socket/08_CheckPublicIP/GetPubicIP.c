#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h> /* hostent struct, gethostbyname() */
#include <arpa/inet.h> /* inet_ntoa() to format IP address */
#include <netinet/in.h> /* in_addr structure */

#define BUFFSIZE 32
#define HTTP 80
void Die(char *mess) { perror(mess); exit(1); }


int main(int argc, char *argv[]) 
{
    int sock;
    struct sockaddr_in echoserver;
    char buffer[BUFFSIZE];
    unsigned int echolen;
    int received = 0;
    static const char IPServer[] = "checkip.dyndns.org";

    struct hostent *host; /* host information */
    struct in_addr h_addr; /* Internet address */

    //printf("wtf\n");
    if ((host = gethostbyname(IPServer)) == NULL)
    {
        fprintf(stderr, "(mini) nslookup failed on '%s'\n", IPServer);
        exit(1);
    }
    h_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);
    fprintf(stdout, "%s\n", inet_ntoa(h_addr));
    

    /* Create the TCP socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    {
        Die("Failed to create socket");
    }

    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver));      /* Clear struct */
    echoserver.sin_family = AF_INET;                 /* Internet/IP */
    echoserver.sin_addr.s_addr = h_addr.s_addr; /* IP address */
    echoserver.sin_port = htons(HTTP);      /* server port */
    /* Establish connection */
    if (connect(sock,
                (struct sockaddr *) &echoserver,
                 sizeof(echoserver)) < 0) {
        Die("Failed to connect with server");
    }

    /* Send the word to the server */
    
    static const char packetbuffer[] = 
    "GET / HTTP/1.1\r\n\
    Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash,\
    application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, */*\r\n\
    Accept-Language: zh-tw,en-US;q=0.5\r\n\
    UA-CPU: x86\r\n\
    Accept-Encoding: gzip, deflate\r\n\
    User-Agent: Mozilla/4.0 \(compatible; MSIE 7.0; Windows NT 5.1\)\r\n\
    Host: checkip.dyndns.org\r\n\
    Connection: Keep-Alive\r\n\
    \r\n";
    printf("packetbuffer = %s\n",packetbuffer);

    echolen = strlen(packetbuffer);
    //printf("echolen = %d\n",echolen);
    if (send(sock, packetbuffer, echolen, 0) != echolen) 
    {
        Die("Mismatch in number of sent bytes");
    }

    char temp[1024];
    memset(&temp, 0, sizeof(temp));      /* Clear struct */

    /* Receive the word back from the server */
    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) 
    {
        //printf("Error in recv(): %s\n", strerror(errno));
        Die("Failed to receive initial bytes from server");
    }
    strcpy(temp,buffer); 

    fprintf(stdout, "Received: ");
    int i = 1;
    while(received > 0) 
    {
        if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) 
        {
            Die("Failed to receive bytes from server");
        }
        buffer[received] = '\0'; /* Assure null terminated string */
        strcat(temp,buffer);
        //fprintf(stdout, buffer);

    }
    printf("%s\n",temp);
    
   /*  <html><head><title>Current IP Check</title></head><body>Current IP Address: 59.120.3.16</body></html>  */
   
    char ip[16]; // xxx.xxx.xxx.xxx + '\0'
    memset(&ip, 0, sizeof(ip));      /* Clear struct */
    //sscanf(temp,"%*[^<]<%*75c%[^<]",ip);
    sscanf(temp,"%*[^<]<html><head><title>Current IP Check</title></head><body>Current IP Address: %[0-9.]",ip);
    printf("IP = %s\n",ip);
   
    return 0;
}
