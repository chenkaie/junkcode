#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void dump(int signo)
{
    char buf[1024];
    char cmd[1024];
    FILE *fh;

    snprintf(buf, sizeof(buf), "/proc/%d/cmdline", getpid());
    if(!(fh = fopen(buf, "r")))
        exit(0);
    if(!fgets(buf, sizeof(buf), fh))
        exit(0);
    fclose(fh);
    if(buf[strlen(buf) - 1] == '\n')
        buf[strlen(buf) - 1] = '\0';
	/*snprintf(cmd, sizeof(cmd), "gdb %s %d", buf, getpid());*/
	snprintf(cmd, sizeof(cmd), "gdb --command=/home/kent/Repos/DotFiles/.gdbinit-7.3 %s %d", buf, getpid());
	printf("%s\n", cmd);
    /*system(cmd);*/

    exit(0);
}

void dummy_function (void)
{
	char die = 1;
	if (die)
	{
		printf("DEAD!\n");
		unsigned char *ptr = 0x00;
		*ptr = 0x00;
	}
	else
	{
		printf("ALIVE!\n");
		unsigned char *ptr = malloc(sizeof(char));
		*ptr = 0x00;
	}
}

int main (void)
{
    signal(SIGSEGV, &dump);
    dummy_function ();

    return 0;
}
