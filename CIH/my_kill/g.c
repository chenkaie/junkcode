/*
 CIH<Software Magician> IamCIH@gmail.com
*/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <dlfcn.h>

int kill(pid_t pid, int sig)
{
        void *h;
        static int (*my_kill)(pid_t, int) = 0;

        fprintf(stderr, "CIH kill ==> pid %i sig %i\n", pid, sig);

        if ( my_kill == 0 )
        {
                h = dlopen("/lib/libc.so.6", RTLD_LAZY);
                my_kill = dlsym(h, "kill");
        }

        return my_kill(pid, sig);
}

