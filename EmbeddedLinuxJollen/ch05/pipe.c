#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void pipe_write(const char *msg, FILE *stream)
{
   int i;

   for (i = 0; i < 10; i++) {
      fprintf(stream, "%s\n", msg);

      fflush(stream);
      sleep(3);
   }
}

void pipe_read(FILE *stream)
{
   char buffer[1024];

   while (!feof(stream) && !ferror(stream) &&
          fgets(buffer, sizeof(buffer), stream) != NULL)
      fputs(buffer, stdout);
}

int main()
{
   int fds[2];
   FILE *stream;
   pid_t self, child;

   /* create a pipe */
   pipe(fds);

   /* fork a child process */
   self = getpid();
   child = fork();

   if (child != 0) {
      printf("Parent process, PID: %d\n", (int) self);
      printf("Child process ID: %d\n", (int) child);

      close(fds[0]);

      /* write pipe from the parent process */
      stream = fdopen(fds[1], "w");
      pipe_write("Hello, Pipes!", stream);
      close(fds[1]);
   } else {
      printf("This is the child process. PID: %d\n", (int) getpid());

      close(fds[1]);

      /* read pipe from the child process */
      stream = fdopen(fds[0], "r");
      pipe_read(stream);
      close(fds[0]);
   }

   return 0;
}
