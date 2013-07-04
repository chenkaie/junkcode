#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void){
	struct sockaddr_un server_addr,client_addr;
	socklen_t size;
	int len;
	int sock,csock;

	sock=socket(PF_UNIX, SOCK_STREAM, 0);

	bzero(&server_addr,sizeof(server_addr));	
	server_addr.sun_family=PF_UNIX;
	strcpy(server_addr.sun_path,"stream");
	len=sizeof(server_addr.sun_family)+strlen(server_addr.sun_path);

	unlink("stream");
	bind(sock,(struct sockaddr *)&server_addr,len);

	listen(sock,5);
	size=sizeof(client_addr);
	csock=accept(sock,(struct sockaddr *)&client_addr,&size);

	write(csock,"Unix domain TEST",16);
}
