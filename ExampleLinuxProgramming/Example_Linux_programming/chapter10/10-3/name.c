#include <sys/socket.h>
#include <netinet/in.h>

int main(void){
	struct sockaddr_in addr,addr2;
	int sock,addressSize;

	sock=socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr,sizeof(addr));
	addr.sin_family=PF_INET;
	//addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_addr.s_addr=inet_addr("192.168.77.2");
	addr.sin_port=htons(5678);
	bind(sock,(struct sockaddr *)&addr,sizeof(addr));

	addressSize=sizeof(addr2);
	getsockname(sock,(struct sockaddr *)&addr2, &addressSize);
	printf("sock name=%s port=%d\n",inet_ntoa(addr2.sin_addr.s_addr),ntohs(addr2.sin_port));
}
