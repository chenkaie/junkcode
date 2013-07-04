#ifndef  __ESERV_IO_H__
#define  __ESERV_IO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "http.h"

int ex_sock_nwrite(SOCKET sock, char *buf, size_t n);

int ex_read_head(SOCKET sock, char *buf, size_t bufsize);
int ex_load_body(ExHttp *pHttp);
int sendFileStream(const ExHttp *pHttp, const char *filePath);

#ifdef __cplusplus
}
#endif

#endif

