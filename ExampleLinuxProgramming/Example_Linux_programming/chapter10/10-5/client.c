#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <error.h>
#include <sys/select.h>

extern int errno;

int main(void){
	fd_set wfds;
	struct sockaddr_in server;
	int sock,value,size;
	char buf[]="TCP TEST\n";

	bzero(&server,sizeof(server));
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5678);

	sock=socket(PF_INET,SOCK_STREAM,0);
	value=1;
	ioctl(sock,FIONBIO,&value);
	connect(sock,(struct sockaddr *)&server,sizeof(server));
	perror("connect");

	FD_ZERO(&wfds);
	FD_SET(sock,&wfds);

	select(sock+1,0,&wfds,0,0);
	if(FD_ISSET(sock,&wfds)){
		size=sizeof(value);
		getsockopt(sock,SOL_SOCKET,SO_ERROR,&value,&size);
		printf("error:%s\n",strerror(value));
		if(value==0){
			write(sock,buf,sizeof(buf)); 
		}
	}
}
