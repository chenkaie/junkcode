#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
   FILE *stream;
   int fds[2];
   int i;
   pid_t child;
   char *arg_list[] = { "more", NULL };

   /* create a pipe */
   pipe(fds);

   /* fork a child process */
   child = fork();

   if (child != 0) {
      close(fds[0]);

      dup2(fds[1], 1);
      execlp("ls", "ls", "-l", "/lib", 0);

      waitpid(child, NULL, 0);
   } else {
      close(fds[1]);

      dup2(fds[0], 0);
      execvp("more", arg_list);
   }

   exit(0);
}
