#include "misc.h"
#include "analysis.h"
#include "io.h"
#include "cgi.h"

/* set MIME type, content length, and cache control like expire and
 * last-modified
*/
static int fileSet(char *buf, const ExHttp *pHttp)
{
	return sprintf(buf,
	               "Content-Type: %s\n"
	               "Content-Length: %d\n"
	               "Cache-Control: max-age=%ld\n"
	               "ETag: %lx.%lx\n",
	               get_mime_type(pHttp->url),
	               (int) pHttp->st.st_size,
	               (long int) ExpireTime,
	               pHttp->st.st_size,
	               pHttp->st.st_mtime
	              );
}

static int typeSet(char *buf, const char *type)
{
	return sprintf(buf, "Content-Type: %s\n", get_mime_type(type));
}

static int lengthSet(char *buf, int len)
{
	return sprintf(buf, "Content-Length: %d\n", len);
}

static int sendHead(const ExHttp *pHttp, char *pBuf, size_t len)
{
	size_t nLen;
	nLen = sprintf(pBuf + len, "Server: " SERVER "\n\n");
	DBG("%s", pBuf);
	return ex_sock_nwrite(pHttp->sock, pBuf, len + nLen);
}

static int codeSet(char *pBuf , int code)
{
	const char *c200 = "OK";
	const char *c304 = "Not Modified";
	const char *c400 = "Bad Request";
	const char *c404 = "Not Found";
	const char *c501 = "Not Implemented";

	const char *msg = NULL;
	switch (code) {
	case 200:
		msg = c200;
		break;
	case 304:
		msg = c304;
		break;
	case 400:
		msg = c400;
		break;
	case 404:
		msg = c404;
		break;
	case 501:
		msg = c501;
		break;
	default:
		break;
	}
	return sprintf(pBuf, "HTTP/1.1 %d %s\n", code, msg);
}

int ex_error_reply(const ExHttp *pHttp , int stscode)
{
	char buf[128];
	char *pBuf = buf;

	pBuf += codeSet(pBuf, stscode);
	return sendHead(pHttp, buf, pBuf - buf);
}

int ex_send_msg(ExHttp *pHttp, const char *type, const char *buf, size_t len)
{
	char hBuf[BUFSIZ];
	char *pBuf = hBuf;
	int ret;
	pBuf += codeSet(pBuf, 200);
	pBuf += typeSet(pBuf, type);
	pBuf += lengthSet(pBuf, len);

	do {
		if ((ret = sendHead(pHttp, hBuf, pBuf - hBuf)) < 0)
			break;
		if ((ret = ex_sock_nwrite(pHttp->sock, (char *) buf, len)) < 0)
			break;
	} while (0);
	return ret;
}

int ex_send_file(ExHttp *pHttp , const char *filePath)
{
	char buf[BUFSIZ];
	char *pBuf = buf;
	int ret = 0;
	pBuf += codeSet(pBuf, 200);
	pHttp->url = (char *) filePath;
	stat(filePath, &pHttp->st);
	pBuf += fileSet(pBuf, pHttp);
	do {
		if ((ret = sendHead(pHttp, buf, pBuf - buf)) < 0)
			break;

		if ((ret = sendFileStream(pHttp, filePath)) < 0)
			break;
	} while (0);
	return ret;
}

static int staticProcess(const ExHttp *pHttp)
{
	char buf[BUFSIZ];
	char *pBuf = buf;
	int ret = 0;

	int code = cacheCheck(pHttp);
	pBuf += codeSet(pBuf , code);
	if (code == 200) {
		pBuf += fileSet(pBuf , pHttp);
	}
	do {
		if ((ret = sendHead(pHttp, buf , pBuf - buf)) < 0)
			break;

		if (code == 304 || 'H' == *(pHttp->method))
			break;
		ret = sendFileStream(pHttp, pHttp->url);
	} while (0);
	return ret;
}

static int cgiProcess(ExHttp *pHttp)
{
	int ret = 0;
	void *handle = NULL;
	do {
		if ((handle = cgi_page_find(pHttp->url)) == NULL) {
			errorLog(pHttp, "CGI page not find");
			ret = -1;
			break;
		}
		if (('P' == *(pHttp->method)) && ex_load_body(pHttp) < 0) {
			errorLog(pHttp, "body check error");
			ret = -2;
			break;
		}
		if (decodeParam(pHttp) < 0) {
			errorLog(pHttp, "param decode error");
			ret = -3;
			break;
		}
		if (cgi_handler(pHttp, handle) < 0) {
			errorLog(pHttp, "handler error");
			ret = -4;
		}
	} while (0);

	if (*(pHttp->method) == 'P' &&
	    pHttp->postData != pHttp->curPos)
		free(pHttp->postData);

	ex_hash_clear(&(pHttp->paramMap));
	return ret;
}

static void clearHttp(ExHttp *pHttp)
{
	ex_hash_clear(&(pHttp->headMap));
	ex_mpool_clear(&(pHttp->mp));
}

static int replyHandler(ExHttp *pHttp)
{
	int rType;
	int ret = -1;

	rType = checkpath(pHttp);
	DBG("filetype: %d\n", rType);
	switch (rType) {
	case 0: 	/* static file */
		ret = staticProcess(pHttp);
		break;
	case 1: 	/* dyanamic page: '.cgi' extension */
		ret = cgiProcess(pHttp);
		break;
	default:
		ex_error_reply(pHttp, rType);
	}
	clearHttp(pHttp);
	return ret;
}

void requestHandler(void *s)
{
	SOCKET sock = *((SOCKET*)s);
	char recvBuf[MAX_HEADER_SIZE + 8];

	char pool[512];
	static const char *skipBrake = "  \n\n:\n\n";
	ExHttp httpInfo;

	++ExContext.threadCnt;

	httpInfo.sock = sock;
	ex_mpool_init(&httpInfo.mp, pool, sizeof(pool));
	do {
		if (ExContext.quitFlag == 1)
			break;

		httpInfo.recvLen = ex_read_head(sock, recvBuf, MAX_HEADER_SIZE);
		if (httpInfo.recvLen <= 0)
			break;

		httpInfo.curPos = recvBuf;
		recvBuf[httpInfo.recvLen] = '\0';
		strcat(recvBuf + httpInfo.recvLen , skipBrake);

		/* if method is not implemented */
		if (checkmethod(&httpInfo) < 0) {
			DBG("len: %d %s\n", httpInfo.method);
			ex_error_reply(&httpInfo, 501);
			break;
		}
		if (parseURL(&httpInfo) < 0) {
			ex_error_reply(&httpInfo, 400);
			errorLog(&httpInfo, "parseURL error");
			break;
		}
		/* if parse head error */
		if (parseHeader(&httpInfo) < 0) {
			ex_error_reply(&httpInfo, 400);
				/* bad Request */
			errorLog(&httpInfo, "parse head error");
			clearHttp(&httpInfo);
			break;
		}
		/* if reply error */
		if (replyHandler(&httpInfo) < 0) {
			break;
		}
	} while (1);

	closesocket(sock);
	--ExContext.threadCnt;
}
