#include "cgi.h"
#include "misc.h"
#include "http.h"
#include "hash.h"

static int ex_hashcasecmp_str(const char *s1, const char *s2)
{
	return (0 == strcasecmp(s1, s2));
}

void ex_sleep(size_t ms)
{
	usleep(ms * 1000);
}

int ex_uninit()
{
	ExContext.quitFlag = 1;
	while (ExContext.threadCnt > 0)
		ex_sleep(EX_SOCK_RTT);

	cgi_uninit();

	ex_hash_clear(&ExContext.mimeMap);
	ex_hash_clear(&ExContext.pageMap);
	printf("eServ terminated.\n");
	return 0;
}

extern void  requestHandler(void * s);

static int ex_http_start()
{
	SOCKET ser_fd, cli_fd;  /* listen on sock_fd, new connection on new_fd */
	struct sockaddr_in ser_addr, cli_addr; /* connector's address information */
	int opt, sin_size;

	/* Setup the default values */
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = EX_SOCK_RTT * 1000;

	/*
	* Setup the sockets and wait and process connections
	*/
	if ((ser_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* Let the kernel reuse the socket address. This lets us run
	   twice in a row without waiting for the (ip, port) tuple
	   to time out. */
	opt = 1;
	setsockopt(ser_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	setsockopt(ser_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));

	ser_addr.sin_family = AF_INET;		/* host byte order */
	ser_addr.sin_port = htons(PORT);	/* short, network byte order */
	ser_addr.sin_addr.s_addr = INADDR_ANY;	/* auto-fill with my IP */

	if (bind(ser_fd, (struct sockaddr *) &ser_addr,
	         sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(ser_fd, EX_SOCK_BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	if (chdir(RootPath) != 0) {
		perror("chdir");
		exit(1);
	}

	DBG("\n " SERVER " is running.  Port: %d\n", PORT);

	sin_size = sizeof(struct sockaddr_in);
	while (1) {  /* main accept() loop */
		if (ExContext.quitFlag == 1)
			break;
		if ((cli_fd = accept(ser_fd,
		                     (struct sockaddr *) & cli_addr,
				     (socklen_t *) &sin_size)) == -1)
			continue;
		while (1) {
			if (ExContext.threadCnt < EX_MAX_THREADS) {
				start_thread((void *) requestHandler,
				             (void *) &cli_fd);
				break;
			} else
				ex_sleep(50);
		}
	}
	return 0;
}

const char *get_mime_type(const char *path)
{
	const char *extension;
	const char *ret = NULL;

	if (path != NULL &&
	    (extension = strrchr(path, '.')) != NULL) {
		ret = ex_hash_find(&ExContext.mimeMap , ++extension);
	}
	return (ret != NULL) ? ret : ("text/plain");
}

void cgi_page_add(const char * pageName, void *f)
{
	ex_hash_add(&ExContext.pageMap, pageName, f);
}

void* cgi_page_find(const char *pageName)
{
	return ex_hash_find(&ExContext.pageMap , pageName);
}

int ex_init()
{
	int i = -1;
	static char pool[2048];
	static ex_mpool mpool;

	ex_mpool_init(&mpool, pool, sizeof(pool));
	ex_hash_init(&ExContext.mimeMap, &mpool, 97);
	ex_hash_init(&ExContext.pageMap, &mpool, 97);
	ExContext.pageMap.hashcmp = (void *) ex_hashcasecmp_str;
	ExContext.mimeMap.hashcmp = (void *) ex_hashcasecmp_str;
	/* add MIME type map */
	while (mmt[++i].ext != NULL) {
		ex_hash_add(&ExContext.mimeMap, mmt[i].ext, mmt[i].type);
	}

	ExContext.quitFlag = 0;
	ExContext.threadCnt = 0;

	cgi_init();
	return start_thread((void *) ex_http_start, NULL);
}

