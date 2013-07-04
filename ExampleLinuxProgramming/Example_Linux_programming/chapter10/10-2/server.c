#include <sys/socket.h>
#include <netinet/in.h>

int main(void){
	struct sockaddr_in server,client;
	int sock,readSize,addressSize;
	char buf[256];

	bzero(&server,sizeof(server));
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5678);

	sock=socket(PF_INET,SOCK_DGRAM,0);
	bind(sock,(struct sockaddr *)&server,sizeof(server));

	addressSize=sizeof(client);
	readSize=recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&client,&addressSize); 
	buf[readSize]=0;
	printf("read message:%s\n",buf);
}
