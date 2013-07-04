#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void){
	struct sockaddr_un unix_addr;
	char buf[128];
	int len,readSize;

	int sock=socket(PF_UNIX, SOCK_STREAM, 0);

	bzero(&unix_addr,sizeof(unix_addr));	
	unix_addr.sun_family=PF_UNIX;
	strcpy(unix_addr.sun_path,"stream");
	len=sizeof(unix_addr.sun_family)+strlen(unix_addr.sun_path);

	if(connect(sock,(struct sockaddr *)&unix_addr,len)<0){
		perror("connect failed:");
	}

	readSize=read(sock,buf,sizeof(buf));
	buf[readSize]=0;
	printf("%s\n",buf);
	
}
