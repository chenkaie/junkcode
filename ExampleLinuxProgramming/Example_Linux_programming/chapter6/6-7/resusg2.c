/*
 * resusg2.c - Get resource usage with getrusage
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

void err_quit(char *);
void doit(char *, long);

int main(void)
{
    struct rusage usage;
    
    /* Redirect output to prevent screen clutter */
    system("grep the /home/*/* > /dev/null 2> /dev/null");
    
    /* Get the resource structure for the parent */
    if((getrusage(RUSAGE_SELF, &usage)) == -1)
	err_quit("getrusage");
    
    puts("parent times");
    doit("\tuser CPU", usage.ru_utime.tv_sec);
    doit("\tsys  CPU", usage.ru_stime.tv_sec);
    
    puts("parent memory stats");
    doit("\tminor faults", usage.ru_minflt);
    doit("\tmajor faults", usage.ru_majflt);
    doit("\tpage   swaps", usage.ru_nswap);
    
    /* Get the resource structure for the child */
    if((getrusage(RUSAGE_CHILDREN, &usage)) == -1)
	err_quit("getrusage");
    
    puts("child times");
    doit("\tuser CPU", usage.ru_utime.tv_sec);
    doit("\tsys  CPU", usage.ru_utime.tv_sec);
    
    puts("child memory stats");
    doit("\tminor faults", usage.ru_minflt);
    doit("\tmajor faults", usage.ru_majflt);
    doit("\tpage   swaps", usage.ru_nswap);
    
    exit(EXIT_SUCCESS);
}

void doit(char *str, long resval)
{
    printf("%s: %ld\n", str, resval);
}

void err_quit(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}
