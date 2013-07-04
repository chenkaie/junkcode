#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <error.h>

extern int erron;

int main(void){

	fd_set rfds,arfds;
	int tableSize,i,value;

	struct sockaddr_in server,client;
	int sock,csock,readSize,addressSize;
	char buf[256];

	bzero(&server,sizeof(server));
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5678);

	sock=socket(PF_INET,SOCK_STREAM,0);

	bind(sock,(struct sockaddr *)&server,sizeof(server));
	perror("bind");

	listen(sock,5);

	FD_ZERO(&rfds);
	FD_SET(sock,&rfds);
	tableSize=getdtablesize();

	for(;;){
		memcpy(&arfds,&rfds,sizeof(fd_set));
		select(tableSize,&arfds,0,0,0);
		if(FD_ISSET(sock,&arfds)){	
			int addressSize=sizeof(client);
			csock=accept(sock,(struct sockaddr *)&client,&addressSize);
			printf("new connection from %s:%d\n",inet_ntoa(client.sin_addr.s_addr),ntohs(client.sin_port));
			FD_SET(csock,&rfds);
			FD_CLR(sock,&arfds);
		}
	
		for(i=0;i<tableSize;i++){
			if(FD_ISSET(i,&arfds)){
				if((readSize=read(i,buf,sizeof(buf)))<=0){
					printf("connection closed\n");
					FD_CLR(i,&rfds);
					close(i);
				}else{
					buf[readSize]=0;
					printf("read:%s",buf);
					write(i,buf,strlen(buf));
				}
			}
		}
	}
}
