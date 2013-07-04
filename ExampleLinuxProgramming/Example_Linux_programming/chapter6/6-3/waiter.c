/*
 * waiter.c - Simple wait usage
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t child;
    int status;
    
    if((child = fork()) == -1) {
	perror("fork");
	exit(EXIT_FAILURE);
    } else if(child == 0) {
	puts("in child");
	printf("\tchild pid = %d\n", getpid());
	printf("\tchild ppid = %d\n", getppid());
	exit(EXIT_SUCCESS);
    } else {
	/* Wait for the child to exit */
	waitpid(child, &status, 0); 
	printf("in parent\n");
	printf("\tparent pid = %d\n", getpid());
	printf("\tparent ppid = %d\n", getppid());
	printf("\tchild exited with %d\n", status);
    }
    exit(EXIT_SUCCESS);
}
