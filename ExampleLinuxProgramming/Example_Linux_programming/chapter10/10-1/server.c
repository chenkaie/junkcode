#include <sys/socket.h>
#include <netinet/in.h>

int main(void){
	struct sockaddr_in server,client;
	struct sockaddr_in local,foreign;
	int sock,csock,readSize,addressSize;
	char buf[256];

	bzero(&server,sizeof(server));
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(6789);

	sock=socket(PF_INET,SOCK_STREAM,0);
	bind(sock,(struct sockaddr *)&server,sizeof(server));

	listen(sock,5);
	addressSize=sizeof(client);
	csock=accept(sock,(struct sockaddr *)&server, &addressSize);

	addressSize=sizeof(local);
        getsockname(csock,(struct sockaddr *)&local, &addressSize);
        printf("local   sock name=%s port=%d\n",inet_ntoa(local.sin_addr.s_addr),ntohs(local.sin_port));

	addressSize=sizeof(foreign);
        getpeername(csock,(struct sockaddr *)&foreign, &addressSize);
        printf("foreign sock name=%s port=%d\n",inet_ntoa(foreign.sin_addr.s_addr),ntohs(foreign.sin_port));

	readSize=read(csock,buf,sizeof(buf)); 
	buf[readSize]=0;
	printf("read message:%s\n",buf);
}
