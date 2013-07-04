#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <error.h>
#include <sys/select.h>

extern int errno;
void Die(char *mess) { perror(mess); exit(1); }
#define BUFFSIZE 32

int main(void){
	fd_set wfds;
	struct sockaddr_in server;
	int sock,value,size;
	char buf[]="TCP TEST\n";

#if 0
	bzero(&server,sizeof(server));
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5678);

	sock=socket(PF_INET,SOCK_STREAM,0);
	value=1;
	ioctl(sock,FIONBIO,&value);
	connect(sock,(struct sockaddr *)&server,sizeof(server));
	perror("connect");

#else
    struct sockaddr_in echoserver;
    char buffer[BUFFSIZE];
    unsigned int echolen;
    int received = 0;

    /* Create the TCP socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    {
        Die("Failed to create socket");
    }

    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver));      /* Clear struct */
    echoserver.sin_family = AF_INET;                 /* Internet/IP */
    echoserver.sin_addr.s_addr = inet_addr("127.0.0.1"); /* IP address */
    echoserver.sin_port = htons(45678);      /* server port */
    /* Establish connection */
    if (connect(sock,
                (struct sockaddr *) &echoserver,
                 sizeof(echoserver)) < 0) {
        Die("Failed to connect with server");
    }

#endif

	FD_ZERO(&wfds);
	FD_SET(sock,&wfds);

	select(sock+1,0,&wfds,0,0);
	if(FD_ISSET(sock,&wfds)){
		printf("FD_ISSET...\n");
		sleep(3);
		size=sizeof(value);
		/*getsockopt(sock,SOL_SOCKET,SO_ERROR,&value,&size);
		printf("error:%s\n",strerror(value));*/
		if(value==0){
			/*sleep(10000);
			printf("sleep 100000... before write\n");*/
			write(sock,buf,sizeof(buf)); 
		}
	}
}
