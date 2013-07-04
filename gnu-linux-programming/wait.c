#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int spawn(char *prog, char **arg_list)
{
   pid_t child;

   child = fork();

   if (child != 0) {
      return child;
   } else {
      execvp(prog, arg_list);
      fprintf(stderr, "spawn error\n");
      return -1;
   }
}

int main()
{
   int child_status;

   char *arg_list[] = {		/* 外部程式參數列 (配合字尾 v) */
      "ls",                     /* argv[0] 即程式名稱 */
      "-l",
      "/tmp",
      NULL };			/* 以 NULL 為結尾 */

   spawn("ls", arg_list);       /* 結合 fork() 與 execv 的 spawn() */

   wait(&child_status);         /* 等待 child process 執行完畢 */

   if (WIFEXITED (child_status))
      printf("child process exited normally, and its exit code is %d\n",
             WEXITSTATUS(child_status));
   else
      printf("child process exited abnormally\n");

   return 0;
}
