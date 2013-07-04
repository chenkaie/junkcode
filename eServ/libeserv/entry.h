#ifndef __ESERV_ENTRY_H__
#define __ESERV_ENTRY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>

#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdint.h>

#include <pwd.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#define	DIRSEP			'/'
#define	IS_DIRSEP_CHAR(c)	((c) == '/')
#define	O_BINARY		0
#define	closesocket(a)		close(a)
#define	ERRNO			errno
#define	INVALID_SOCKET		(-1)

#ifdef __FREEBSD__
#  define __WORDSIZE WORD_BIT
#endif

# if __WORDSIZE == 64
typedef long SOCKET;
#else
typedef int SOCKET;
#endif

#define  EX_SOCK_ERRNO errno
#define	 EX_EINTR EINTR
#endif

#if !defined(MIN)
#define MIN(a, b) ((a)<(b)?(a):(b))
#endif

#if !defined(MAX)
#define MAX(a, b) ((a)>(b)?(a):(b))
#endif

int start_thread(void *(*func)(void *), void *param);

extern void ex_sleep(size_t ms);

#ifdef __cplusplus
}
#endif

