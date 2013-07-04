#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
   /* getpriority() 傳回的類別是 int */
   int prio_process, prio_pgroup, prio_user; 
   pid_t pid;

   if (argc != 2)
      return -1;

   pid = atoi(argv[1]);
   prio_process = getpriority(PRIO_PROCESS, pid);

   printf("Process (%d) Priority is %d.\n", pid, prio_process);
   return 0;
}
