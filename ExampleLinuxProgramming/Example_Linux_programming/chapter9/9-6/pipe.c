#include <unistd.h>
#include <stdio.h>

int main(void){
	int fd[2],pid;

	pipe(fd); //create pipe
	if((pid=fork())==0){ //child
		char buf[128];

		close(fd[1]);
		dup2(fd[0],0);	
		close(fd[0]);
		fgets(buf,128,stdin);
		printf("%s",buf);
	}else{ //parent
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		printf("hello world\n");
		close(1);
		wait(NULL);
	}
}
