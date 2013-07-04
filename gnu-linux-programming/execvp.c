#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
   char *arg_list[] = {		/* 场祘Α把计 (皌Ю v) */
      "ls",                     /* argv[0] 祘Α嘿 */
      "-l",
      "/tmp",
      NULL };			/*  NULL 挡Ю */

   execvp("ls", arg_list);      /*  PATH 隔畖碝т场祘Α */
   printf("The end of the program.\n");
}
