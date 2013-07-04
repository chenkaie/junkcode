#ifndef __ESERV_CGI_H__
#define __ESERV_CGI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "http.h"

void cgi_init();

void cgi_uninit();

int cgi_handler(ExHttp *pHttp, void *handle);

int errorLog(ExHttp *pHttp, const char *mess);

typedef struct {
	char *name;
	int (*callback)(ExHttp *pHttp);
} cgi_page;

#define CGI_DECL_BEGIN \
/* customized page handler declare here */ \
cgi_page cgi_pages[] = {

#define CGI_ENTRY(NAME) \
	{ \
		.name = #NAME ".cgi" , \
		.callback = cgi_page_ ## NAME, \
	},

#define CGI_DECL_END \
};

#ifdef __cplusplus
}
#endif

#endif

