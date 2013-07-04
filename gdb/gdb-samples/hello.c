#include <stdio.h>
#include <stdlib.h>

static char *my_str = "Hello World!";
int main()
{
    const char *buff;
    const char* path = getenv ("PATH");
    const char* home = getenv ("HOME");
    buff = getenv("MANPATH");
    printf("getenv : %s\n", buff);
	puts(my_str);
	return 0;
}
