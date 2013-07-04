#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void sighup_handler()
{
   printf("Receive SIGHUP signal.\n");
}

int main()
{
   struct sigaction sa;

   memset(&sa, 0, sizeof(sa));
   sa.sa_handler = &sighup_handler;
   sigaction(SIGHUP, &sa, NULL);

   while (1);

   return 0;
}
