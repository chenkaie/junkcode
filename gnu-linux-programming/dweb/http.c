/*
   web.c,
   a dirty embedded Web server.
*/
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netinet/in.h>
#include "http.h"

#define CR '\r'
#define LF '\n'

#define MAX 4096

int http_get;

int http_parser(char *s)
{
    if (s[0] == CR && s[1] == LF)
	return -1;
    else if (strncmp(s, "GET", 3) == 0)
	http_get = 1;
    return 0;
}

struct http_operations *http_ops[MAX_OPS];

void *http_main(int n)
{
	struct http_operations *ops = http_data[n].fops;
	char buf[MAX];
	int ret;

	/* blocking open */
	printf("ops->open\n");
	if (ops == NULL)
	   printf("ops = NULL\n");
	if (ops->open) {
	   ops->open(ops);
	} else {
	   printf("ops->open = NULL\n");
	}
	printf("exit ops->open\n");

        while (1) {
	   printf("ops->read\n");
	   ret = ops->read(ops, buf);
	   printf("client: %s [%d]\n", buf, ret);
           http_parser(buf);
	   if (buf[0] == CR && buf[1] == LF)
	      break;
	}

	if (http_get) {
	   ops->write(ops, "hihi", 4);
	}

	printf("ops->close\n");
	ops->close(ops);

	return NULL;
}

int http_register(struct http_operations *ops, int opsno)
{
   	pthread_t thread_id1;

	switch (opsno) {
		case SOCKET_OPS:
			   http_data[SOCKET_OPS].fops = ops;
			   //pthread_create(&thread_id1, NULL, &http_main, );
			   http_main(SOCKET_OPS);
			break;
		case FILE_OPS:
			http_ops[FILE_OPS] = ops;
			break;
		default:
			printf("error\n");
			return -1;
	}
	printf("exit http_register\n");

	return 0;
}
