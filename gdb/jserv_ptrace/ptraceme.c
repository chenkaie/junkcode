#include <sys/ptrace.h>
#include <stdio.h>

int main()                                                                      
{
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0 ) {
        printf("No, I don't want to serve you.\n");
        while (1) {
            /* endless loop */ ;
        }
    }
    printf("Yes, real routines go here\n");
    return 0;
}

