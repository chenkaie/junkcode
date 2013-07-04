#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
   pid_t child;

   child = fork();
  
   if (child != 0) {
      sleep(60);
   } else { 
      return 0;
   }

   return 0;
}
