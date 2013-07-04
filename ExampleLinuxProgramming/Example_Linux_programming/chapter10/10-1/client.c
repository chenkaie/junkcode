#include <sys/socket.h>
#include <netinet/in.h>

int main(void){
	struct sockaddr_in server;
	int sock;
	char buf[]="TCP TEST";

	bzero(&server,sizeof(server));
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(6789);

	sock=socket(PF_INET,SOCK_STREAM,0);
	connect(sock,(struct sockaddr *)&server,sizeof(server));

	write(sock,buf,sizeof(buf)); 
}
