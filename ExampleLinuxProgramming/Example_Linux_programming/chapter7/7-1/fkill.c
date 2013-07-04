/*
 * fkill.c - Send a signal using kill(2)
 */
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
     pid_t child;
     int errret;
 
     if((child = fork()) < 0) {
	  perror("fork");
	  exit(EXIT_FAILURE);
     } else if(child == 0) {	/* in the child process */
	  sleep(2);
     } else {			/* in the parent */
	//sleep(100);
	  waitpid(child, NULL, 0 );
	  /* send a signal that gets ignored */
	  printf("sending SIGCHLD to %d\n", child);
	  errret = kill(child, SIGCHLD);
	  if(errret < 0)
	       perror("kill:SIGCHLD");
	  else
	       printf("%d still alive\n", child);

	  /* now murder the child */
	  printf("killing %d\n", child);
	  if((kill(child, SIGTERM)) < 0)
	       perror("kill:SIGTERM");
     }
     exit(EXIT_SUCCESS);
}
