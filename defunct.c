#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	system("/bin/ls -al; sleep 3");
	printf("Alive!\n");

	int status = -1;
	if(!fork()){
		printf("child pid=%d\n", getpid());
		exit(0);
	}

	// Comment below line to observe [defunct] status in "ps ux | grep defunct"
	// wait(&status);

	printf("status = %d, %d, %d\n", status, WIFEXITED(status), WEXITSTATUS(status));
	sleep(20);

	printf("parent pid=%d \n", getpid());
	exit(0);
}
