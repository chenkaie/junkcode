#ifndef _HTTP_H_
#define _HTTP_H_

struct http_operations {
   int (*open)(struct http_operations *);
   int (*read)(struct http_operations *, char *);
   int (*write)(struct http_operations *, char *, int n);
   void (*close)(struct http_operations *);
   void *priv;
};

#define MAX_OPS 5
#define SOCKET_OPS 0
#define FILE_OPS 1

struct http_data {
    struct http_operatons *fops;
} http_data[MAX_OPS];


int http_register(struct http_operations *, int);
int http_unregister(struct http_operations *);

#endif
