/*
 * mkset.c - Create a signal set
 */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void err_quit(char *);

int main(void)
{
     sigset_t newset;

     /* Create the set */
     if((sigemptyset(&newset)) < 0)
	  err_quit("sigemptyset");
     /* Add SIGCHLD to the set */
     if((sigaddset(&newset, SIGCHLD)) < 0)
	  err_quit("sigaddset");

     /* Check the signal mask */
     if(sigismember(&newset, SIGCHLD))
	  puts("SIGCHLD is in signal mask");
     else
	  puts("SIGCHLD not in signal mask");
     /* SIGTERM shouldn't be there */
     if(sigismember(&newset, SIGTERM))
	  puts("SIGTERM in signal mask");
     else
	  puts("SIGTERM not in signal mask");

     exit(EXIT_SUCCESS);
}
     
void err_quit(char *msg)
{
     perror(msg);
     exit(EXIT_FAILURE);
}
