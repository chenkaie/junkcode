#ifndef __HTTP_H__
#define __HTTP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "entry.h"
#include "hash.h"

#define IndexFile 	"index.html"
#define RootPath 	"www"
#define CgiExt		".cgi"

/* for cache usage, default is ony-day. */
#define ExpireTime 	(24 * 60 * 60)

#define SERVER "eServ/1.1"

/* default listen port */
#define  PORT			8000

/* the max thread number */
#define EX_MAX_THREADS 		10

/* socket receive timeout, 500ms may be ok */
#define  EX_SOCK_RTT		500

/* max pending-socket number */
#define  EX_SOCK_BACKLOG 	5

/* max heads in http/1.1 support max:64.
 * but here we only support 40*/
#define	MAX_HTTP_HEADERS	40

/* we use it when read/write file */
#define PAGE_SIZE		4096

#define MAX_HEADER_SIZE 	(2 * 1024)

#define MAX_POST_SIZE 		(8 * 1024)

/* the max size we read socket once */
#define EX_TCP_QUAN 		(2 * 1024)

typedef struct {
	char *method;
	char *url;
	char *protocol;

	union {
		char *queryString;	/* for GET */
		char *postData;		/* for POST */
	};
	ex_mpool mp;
	ex_hashmap headMap;
	ex_hashmap paramMap;

	/* the file stat(if static file) */
	struct stat st;
	SOCKET sock;
	int recvLen;
	char *curPos;
	char *paramEndPos;
} ExHttp;

/*static*/ struct {
	ex_hashmap mimeMap;
	ex_hashmap pageMap;
	volatile int threadCnt;
	volatile int quitFlag;
} ExContext;

int ex_init();
int ex_uninit();
void cgi_page_add(const char * pageName, void *);
void *cgi_page_find(const char *pageName);

void print_header(const ExHttp *pHttp);
void print_param(const ExHttp *pHttp);
const char *get_head_info(const ExHttp *pHttp, const char *key);
const char *get_param_info(const ExHttp *pHttp, const char *key);

const char *get_mime_type(const char *path);
int ex_send_msg(ExHttp *pHttp, const char *type, const char *buf, size_t len);
int ex_send_file(ExHttp *pHttp, const char *filePath);
int ex_error_reply(const ExHttp *pHttp, int stscode);

#ifdef __cplusplus
}
#endif

#endif

