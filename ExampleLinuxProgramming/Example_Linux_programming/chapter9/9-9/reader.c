#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
	char buf[256];
	int fd=open("fifo",O_RDONLY);
	read(fd,buf,256);
	printf("%s",buf);
}
