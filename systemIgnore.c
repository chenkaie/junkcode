#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>

/* A "fire and forget" version of system().
   I.E. we don't have to wait for the child */
void systemIgnore(char *command) {
	int pid;
	if (command == 0) {
		fprintf(stderr,"NULL command passed to systemIgnore?\n");
		return;
	}
	pid = fork();
	if (pid == -1) {
		fprintf(stderr,"systemIgnore couldn't fork(1)!\n");
		return;
	}
	if (pid != 0) { //parent
		pid_t retpid;
		retpid = waitpid(pid, NULL, 0); //reap temp child
		//fprintf(stderr,"systemIgnore::waitpid returned [%d]\n", retpid);
	} else { //child
		int tmppid;
		tmppid = fork();
		if (tmppid == -1) {
			fprintf(stderr,"systemIgnore couldn't fork(2)!\n");
			_exit(127);
		}
		if (tmppid != 0) {
			_exit(0);
		} else { //grandchild will be reaped by init on exit
			setpgrp(); //so one can kill the whole group
			char *argv[4];
			argv[0] = "sh";
			argv[1] = "-c";
			argv[2] = command;
			argv[3] = NULL;
			execv("/bin/sh", argv);
			_exit(127); //error if get to here
		}
	}
}

#ifndef TEST_SI
int main(int argc, char** argv) {
	systemIgnore(argv[1]);
	//while(1){sleep(1);}
	return 0;
}
#endif
