/*
 *  Purpose of this utility is to timestamp each line coming over stdin
 *  USAGES:
 *     tstamp.exe < /dev/ttyS0
 *     <commands> | tstamp.exe
 *
 *  Kent: 
 *   	1. /usr/sbin/venc --chain -p /var/run/venc.pid 2>&1 | /home/kent/practice/tstamp.dm365.out
 *   	2. find /usr 2>&1 | /home/kent/practice/tstamp.dm365.out
 *
 *  Note: sometimes you have to set stand stream unbuffered to take effect. e.g., configer.II
 *		  setvbuf(stdout, 0, 2, 0);
 *  	  setvbuf(stderr, 0, 2, 0);
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <sys/signal.h>

#define MAX_BUF_SIZE	(10*1024)

//Kent, add for read()
#include <string.h>
#include <unistd.h>
#define STDIN_FD        (0)

char buf[MAX_BUF_SIZE];

// Global variables that control process shutdown.
sig_atomic_t graceful_quit = 0;

// Signal handler for SIGINT.
void SIGINT_handler (int signum)
{
	assert (signum == SIGINT);
	graceful_quit = 1;
}

// Signal handler for SIGQUIT.
void SIGQUIT_handler (int signum)
{
	assert (signum == SIGQUIT);
	graceful_quit = 1;
}

int main(int argc, const char *argv[])
{
	struct timeval tv;
	double time_start,time_now,time_prev;
	int first = 1;
	int bNewlineTerminated = 0;
	struct sigaction sa;

	//Kent
	int read_ret = 0;
	char *fgets_ret = NULL;
	char crln = '\n';

	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;

	// as of now no arguments are allowed. print usage
	if (argc != 1)
	{
		if (0 == strncmp("-n", argv[1], 2))
		{
			printf("[info] Use newline terminated\n");
			bNewlineTerminated = 1;
			crln = ' ';
		}
		else
		{
			printf(
				"Timestamps each line coming over stdin\n"
				"\tUSAGES:\n"
				"\t\t-n : use newline terminated mode\n"
				"\tEXAMPLES:\n"
				"\t\ttstamp.exe < /dev/ttyS0\n"
				"\t\t<commands> | tstamp.exe\n"
				"\n"
			);

			exit(0);
		}
	}

	// Register the handler for SIGINT.
	sa.sa_handler = SIGINT_handler;
	sigaction (SIGINT, &sa, 0);

	// Register the handler for SIGQUIT.
	sa.sa_handler =  SIGQUIT_handler;
	sigaction (SIGQUIT, &sa, 0);

	printf(
		"\tcolumn1 is elapsed time since first message\n"
		"\tcolumn2 is elapsed time since previous message\n"
		"\tcolumn3 is the message\n"
	);

	while (graceful_quit == 0)
	{
		if(bNewlineTerminated)
		{
			// NOTE: fgets() is enabled by default, thus it stop only when newline terminated.
			fgets_ret = fgets(buf, MAX_BUF_SIZE, stdin);
		}
		else
		{
			read_ret = read(STDIN_FD, buf, MAX_BUF_SIZE);
		}

		if((fgets_ret != NULL) || (read_ret != 0))
		{
			// get system time
			gettimeofday(&tv, NULL);

			// convert to double
			time_now = tv.tv_sec + (tv.tv_usec*(1.0/1000000.0));

			// if first time, notedown the time_start
			if (first)
			{
				first = 0,  time_start = time_prev = time_now;
			}

			fprintf(stderr
				,"%c%08li.%06li %03.3f %02.3f: %s"
				,crln
				,(tv.tv_sec)
				,(long)(tv.tv_usec)
				,(float)(time_now-time_start)
				,(float)(time_now-time_prev)
				,buf
			);

			time_prev = time_now;
		}
	}

	fflush(NULL);
	exit(0);
}

