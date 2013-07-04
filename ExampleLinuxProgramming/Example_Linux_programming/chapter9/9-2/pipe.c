#include <unistd.h>

int main(void){
	int fd[2];
	int pid;

	pipe(fd); //create pipe

	if((pid=fork())==0){ //child
		int n;
		char buf[128];

		close(fd[1]);
		n=read(fd[0],buf,128);
		write(0,buf,n);
	}else{ //parent
		close(fd[0]);
		write(fd[1],"hello world\n",12);
		wait(NULL);
	}
}
