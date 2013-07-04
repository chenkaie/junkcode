#include	<signal.h>

static void	sig_alrm(int);

int
main(void)
{
	int		n;
	char	line[256];

        struct sigaction sig;

        sig.sa_handler=sig_alrm;
        sigemptyset(&sig.sa_mask);
        //sig.sa_flags=0;
        sig.sa_flags=SA_RESTART;

        sigaction(SIGALRM,&sig,0);


	alarm(3);
	if ( (n = read(0, line, 256)) < 0)
		printf("error\n");
	alarm(0);

	if(n>=0) write(1, line, n);

	exit(0);
}

static void
sig_alrm(int signo)
{
	printf("receive SIGALRM\n");
	return;	/* nothing to do, just return to interrupt the read */
}
