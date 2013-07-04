#include "http.h"

#ifndef  __ESERV_ANALYSIS_H__
#define  __ESERV_ANALYSIS_H__

#ifdef __cplusplus
extern "C" {
#endif

int checkmethod(ExHttp *pHttp);
int parseURL(ExHttp *pHttp);
int parseHeader(ExHttp *pHttp);
int checkpath(ExHttp *pHttp);
int cacheCheck(const ExHttp *pHttp);
int decodeParam(ExHttp *pHttp);

#ifdef __cplusplus
}
#endif
#endif

