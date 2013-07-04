#include "libeserv/http.h"

int main()
{
	char buf[16];

	ex_init();

	while (scanf("%16s", buf) > 0) {
		if (strncmp("quit", buf, 4) == 0)
			break;
		ex_sleep(200);
	}

	ex_uninit();

	return 0;
}
