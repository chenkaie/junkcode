#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define _XOPEN_SOURCE
int main()
{
	char str[8] = "";
	char *strCrypt;
	int iRet = -1;

//	strncpy(str, "$1$AD1", 6);
//	str[6] = 0;

//	strCrypt = crypt("", "");

	/*printf("%s\n", crypt("", "$1$abc"));*/

	//iRet = strcmp("111111", crypt("admin", "$1$"));
	//printf("%d\n", iRet);

	printf("%x\n", strcmp("", crypt("admin", "")) == 0);
	strcmp("", crypt("admin", ""));

		printf("shit\n");
	/*if (strCrypt != NULL)
	{
		printf("%s\n", strCrypt);
	}*/

	return 0;
}
