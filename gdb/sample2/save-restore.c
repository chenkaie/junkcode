#include <stdio.h>

char * str =
#if 1
	"1234567890";
#else
	"0987654321";
#endif

int main()
{
	puts(str);
	return 0;
}
