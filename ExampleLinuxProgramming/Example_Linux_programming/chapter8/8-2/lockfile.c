#include <unistd.h>
#include <fcntl.h>
#include <error.h>
extern int errno;

int main(int argc,char *argv[]){
	int fd,status;
	struct flock lock;

	fd=open("test.tmp", O_RDWR);
	printf("file descriptor:%d\n",fd);

	lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;	//lock whole file

	status=fcntl(fd,F_SETLKW,&lock);
	printf("get lock\n");
	while(1) sleep(60);
	
}
