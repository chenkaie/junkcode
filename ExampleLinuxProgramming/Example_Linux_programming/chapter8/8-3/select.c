#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd1,fd2,n,total,i;
	char buf[128];
	fd_set rfds,arfds;
	
	fd1=open("fifo1",O_RDONLY|O_NONBLOCK);
	fd2=open("fifo2",O_RDONLY|O_NONBLOCK);
	total=2;

	printf("ready to read\n");
	n=getdtablesize();
	FD_ZERO(&rfds);
	FD_SET(fd1,&rfds);
	FD_SET(fd2,&rfds);

	while(total>0){
		memcpy(&arfds,&rfds,sizeof(fd_set));
		select(n,&arfds,0,0,0);
		for(i=0;i<n;i++){
			if(FD_ISSET(i,&arfds)){
				int readSize;
				if((readSize=read(i,buf,sizeof(buf)))<=0){
					printf("%d closed\n",i);
					FD_CLR(i,&rfds);
					total--;
				}else{
					buf[readSize]=0;
					printf("%d: %s",i,buf);
				}
			}
		}	
	}
	close(fd1);
	close(fd2);
}
