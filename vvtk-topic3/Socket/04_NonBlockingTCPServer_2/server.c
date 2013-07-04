#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <error.h>

extern int erron;
#define MAXPENDING 1 /* Max connection requests */

int main(void){

	fd_set rfds,arfds;
	int tableSize,i,value;

	struct sockaddr_in server,client;
	int sock,csock,readSize,addressSize;
	char buf[256];

	bzero(&server,sizeof(server));
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	/*server.sin_addr.s_addr=htonl(INADDR_ANY);*/
	server.sin_port=htons(45678);

	sock=socket(PF_INET,SOCK_STREAM,0);

	value=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&value,sizeof(value));

	bind(sock,(struct sockaddr *)&server,sizeof(server));
	perror("bind");

	listen(sock, MAXPENDING);

	FD_ZERO(&rfds);
	FD_SET(sock,&rfds);

#define  _DONT_USE_GETDTABLESIZE
#ifdef _DONT_USE_GETDTABLESIZE
	tableSize=sock;
	printf("sock = %d\n", sock);
#else
	tableSize=getdtablesize();
#endif

	for(;;){
		memcpy(&arfds,&rfds,sizeof(fd_set));
		select(tableSize+1,&arfds,0,0,0);
		if(FD_ISSET(sock,&arfds)){	
			int addressSize=sizeof(client);
			csock=accept(sock,(struct sockaddr *)&client,&addressSize);
			printf("accept\n");
			//FIXME: SEGV on rd1-2
			//printf("net connection from %s:%d\n",inet_ntoa(client.sin_addr.s_addr),ntohs(client.sin_port));
			FD_SET(csock,&rfds);
            tableSize = (tableSize<csock)?csock:tableSize;

			FD_CLR(sock,&arfds);
		}

		printf("[for] scan fd from 0 to maxfd: %d\n", tableSize);
		for(i=0;i<=tableSize;i++){
			if(FD_ISSET(i,&arfds)){
				printf("[FD_ISSET]: %d\n", i);
				if((readSize=read(i,buf,sizeof(buf)))<=0){
					printf("connection closed\n");
					FD_CLR(i,&rfds);
					close(i);
				}else{
					buf[readSize]=0;
					printf("read:%s",buf);
				}
			}
		}

		/*usleep(300000);*/
	}
}
