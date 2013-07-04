#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
	int fd=open("fifo",O_WRONLY);
	write(fd,"fifo test\n",10);
}
