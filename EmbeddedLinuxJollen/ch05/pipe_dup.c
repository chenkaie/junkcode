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

      stream = fdopen(fds[1], "w");

      for (i = 0; i < 50; i++) {
         fprintf(stream, "Hello\n");
         fflush(stream);
      }

      close(fds[1]);

      waitpid(child, NULL, 0);
   } else {
      close(fds[1]);

      dup2(fds[0], 0);
      execvp("more", arg_list);
   }

   return 0;
}
