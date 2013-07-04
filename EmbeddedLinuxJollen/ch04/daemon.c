/*
 * Linux Daemon Programming: Its Framework.
 *
 * Copyright(c) 2005 www.jollen.org
 *
 * This file is GPL.
 *
 */
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>	// syslogd

#define	LOCK_FILE	"mydaemon.lock"

int spawn_ls()
{
   pid_t child;
   char *arg_list[] = {		/* 外部程式參數列 (配合字尾 v) */
      "ls",                 /* argv[0] 即程式名稱 */
      "-l",
      "/tmp",
      NULL };			    /* 以 NULL 為結尾 */

   child = fork();

   if (child != 0) {
      return child;
   } else {
      execvp(arg_list[0], arg_list);
      fprintf(stderr, "spawn error\n");
      return -1;
   }
}

/*
 * 使用 'sysklogd' 套件做紀錄檔處理, 
 * 設定檔 /etc/syslog.conf
 */
void log_message(char *msg)
{
   openlog("mydaemon", LOG_PID, LOG_DAEMON);
   syslog(LOG_INFO, "%s", msg);
   closelog();
}

void signal_handler(int sig)
{
   switch (sig) {
      case SIGHUP: 
         spawn_ls();     /* 在 daemon 裡 "spwan" 一個外部程式 */
         log_message("mydaemon received SIGHUP");
         break;
      case SIGTERM:
         log_message("mydaemon exits");
         exit(0);
   }
}

void run_daemon()
{
   pid_t pid;
   int fd;
   int lfd;	// lock file 
   char str[64];

   // 1. 使用 fork() 設計能在背景執行的程式
   pid = fork();
   if (pid < 0) {
      perror("run_daemon:fork()");
      exit(-1);
   }
   if (pid > 0) exit(0);	// parent exits
   
   /* 
    * begin child process (the daemon) 
    */

   // daemon (child process) 執行後立即關閉 file descriptor
   for (fd = getdtablesize(); fd >= 0; --fd) close(fd);

   // 2. detach tty
   setsid();

   // 3. file handling and standard I/O
   fd = open("/dev/null", O_RDWR);
   dup(fd);
   dup(fd);
   umask(027);
   chdir("/tmp");

   // 4. locking
   lfd = open(LOCK_FILE, O_RDWR | O_CREAT, 0640);
   if (lfd < 0) exit(1);	// error
   if (lockf(lfd, F_TLOCK, 0) < 0) exit(0);	// can't lock

   sprintf(str, "mydaemon started (pid: %d)\n", getpid());
   write(lfd, str, strlen(str));

   // 5. signal handling
   signal(SIGCHLD, SIG_IGN);

   signal(SIGHUP, signal_handler);
   signal(SIGTERM, signal_handler);
}

int main()
{
   /* 若 parent process 為 init, 表示已經是一個 daemon 了 */
   if (getppid() == 1) {
      log_message("already a daemon");
      return;
   }

   run_daemon();
   while (1)
      ;		// child process forever loop
}