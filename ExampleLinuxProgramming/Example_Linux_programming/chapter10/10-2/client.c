#include <sys/socket.h>
#include <netinet/in.h>

int main(void){
	struct sockaddr_in server;
	int sock;
	char buf[]="UDP TEST";

	bzero(&server,sizeof(server));
	server.sin_family=PF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5678);

	sock=socket(PF_INET,SOCK_DGRAM,0);

	sendto(sock,buf,sizeof(buf),0,(struct sockaddr *)&server,sizeof(server)); 
}
