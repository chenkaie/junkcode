#include "misc.h"
#include <assert.h>

#ifndef NDEBUG
void DBG(const char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	printf("\n");
}
#else
void DBG(const char *fmt, ...)
{
	/* make compiler happy */
	fmt = NULL;
}
#endif

int url_decode(const char *src, char *dst, int isEncoded)
{
	static char flag[128] = {
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
		-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	};
	int h, l;
	const char *cp = src;
	char *oldDst = dst;
	int ret = 0;

	while (*cp != '\0') {
		if (*cp == '%') {
			h = *(++cp);
			l = *(++cp);
			if (h > 0 && l > 0 &&
			    flag[h] >= 0 && flag[l] >= 0) {
				*dst = (flag[h] << 4 | flag[l]);
			}
			else {
				ret = -1;
				break;
			}
		}
		else if (*cp == '+' && 1 == isEncoded) {
			*dst = ' ';
		}
		else {
			*dst = *cp;
		}
		++cp;
		++dst;
	}
	*dst = '\0';
	return ('\0' == *cp && ret == 0) ?
	       (dst - oldDst) : -1;
}
