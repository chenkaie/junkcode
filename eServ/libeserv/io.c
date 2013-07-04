#include "io.h"
#include "misc.h"
#include "analysis.h"

static inline int sendFileStream_posix(const ExHttp *pHttp, const char *filePath)
{
	char buf[PAGE_SIZE];
	int rSize;
	int ret = 0;
	int fd = open(filePath, O_RDONLY | O_BINARY);
	assert(fd >= 0);
	while ((rSize = read(fd, buf, sizeof(buf))) > 0) {
		if ((ret = ex_sock_nwrite(pHttp->sock, buf, rSize)) < 0)
			break;
	}
	close(fd);
	return ret;
}

int sendFileStream(const ExHttp *pHttp, const char *filePath)
{
	return sendFileStream_posix(pHttp, filePath);
}

static int ex_sock_recv(SOCKET sock, char *buf, size_t bufsize)
{
	int ret;
	do {
		ret = recv(sock, buf, bufsize, 0);
	} while (ret < 0 && EX_SOCK_ERRNO == EINTR);
	return ret;
}

int ex_sock_nread(SOCKET sock, char *buf, size_t n)
{
	size_t nRead = 0;
	size_t nLeft = n;
	int ret;
	while (nLeft > 0) {
		ret = ex_sock_recv(sock, buf + nRead,
		                   MIN(nLeft, EX_TCP_QUAN));
		if (ret <= 0)
			break;
		else {
			nRead += ret;
			nLeft -= ret;
		}
	}
	return nRead == n ? (int) n : -1;
}

int ex_sock_nwrite(SOCKET sock, char *buf, size_t n)
{
	size_t nLeft = n;
	size_t nExite = 0;
	int ret;
	while (nLeft > 0) {
		ret = send(sock, buf + nExite, nLeft, 0);
		if (ret == 0 || (ret < 0 && EX_SOCK_ERRNO != EINTR))
			break;
		else {
			nLeft -= ret;
			nExite += ret;
		}
	}
	return (nExite == n) ? (int) n : -1;
}

static int isHeadEnd(char *pBuf, char *cPos, int len)
{
	int i = -1;
	while (++i < len) {
		if ('\n' == *cPos) {
			if ((cPos - 1 >= pBuf &&
			     '\n' == *(cPos - 1)) ||
			    (cPos - 2 >= pBuf &&
			     '\r' == *(cPos - 1) &&
			     '\n' == *(cPos - 2))) {
				return i;
			}
		}
		++cPos;
	}
	return -1;
}

int ex_read_head(SOCKET sock, char *buf, size_t bufsize)
{
	int nRead = 0;
	int rsize;
	int flag = -1;
	do {
		rsize = ex_sock_recv(sock, buf + nRead, bufsize - nRead);
		if (rsize <= 0)
			break;
		flag = isHeadEnd(buf, buf + nRead, rsize);
		nRead += rsize;
	} while (flag < 0);

	return (flag < 0) ? -1 : nRead;
}

int ex_load_body(ExHttp *pHttp)
{
	int ret;
	int cLen , rLen , sLen;
	const char *pType , *pLen;
	do {
		/* "x-www-form-urlencoded" */
		pType = get_head_info(pHttp, "Content-Type");
		pLen = get_head_info(pHttp, "Content-Length");
		if (pType == NULL || pLen == NULL) {
			ret = -1;
			break;
		}

		/* content length */
		cLen = atoi(pLen);
		if (cLen <= 0 || cLen > MAX_POST_SIZE) {
			ret = -2;
			break;
		}
		rLen = pHttp->curPos - pHttp->method + cLen;
		sLen = pHttp->recvLen - (pHttp->curPos - pHttp->method);

		DBG("cLen, rLen, sLen: %d %d %d\n", cLen, rLen, sLen);
		if (cLen == sLen) {
			pHttp->postData = pHttp->curPos;
			ret = 1;
		}
		else if (cLen > sLen) {
			if (cLen + pHttp->curPos - pHttp->method > MAX_HEADER_SIZE) {
				pHttp->postData = malloc(cLen + 8);
				memmove(pHttp->postData , pHttp->curPos , sLen);
			}
			ret = ex_sock_nread(pHttp->sock,
			                    pHttp->postData + sLen,
					    cLen - sLen);
			if (cLen - sLen == ret) {
				ret = 2;
			}
			else
				ret = -3;
		}
		else {
			ret = -4;
		}
	} while (0);

	if (ret > 0) {
		pHttp->paramEndPos = pHttp->postData + cLen;
		*(pHttp->paramEndPos) = '\0';
	}
	DBG("contentType: %d\n", ret);
	return ret;
}

