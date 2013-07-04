#include "cgi.h"

/* FIXME : flexible inclusion of customized CGI */
#include "../cgi_custom.h"

extern cgi_page cgi_pages[];

void cgi_init()
{
	size_t i;
	for (i = 0; i < sizeof(cgi_pages) / sizeof(cgi_page); i++)
		cgi_page_add(cgi_pages[i].name,
		             cgi_pages[i].callback);
}

void cgi_uninit()
{
}

int cgi_handler(ExHttp *pHttp, void *handle)
{
	int (*pf)(ExHttp *) = handle;

	return pf(pHttp);
}

int errorLog(ExHttp *pHttp, const char *mess)
{
	assert(pHttp);
	if (pHttp)
		printf("%s\n", mess);
	return 0;
}

