#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

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
   char *arg_list[] = {		/* 外部程式參數列 (配合字尾 v) */
      "ls",                     /* argv[0] 即程式名稱 */
      "-l",
      "/tmp",
      NULL };			/* 以 NULL 為結尾 */

   spawn("ls", arg_list);       /* 結合 fork() 與 execv 的 spawn() */
   printf("The end of the program.\n");

   return 0;
}
