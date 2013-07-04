//Reference: http://en.wikipedia.org/wiki/Segmentation_fault
#include <stdio.h>
#include <unistd.h>

#define SEG 1 //0, 1, 2

int main(void)
{

#if SEG == 0
	puts("<memory protection of strings and constant data in a read-only segment of memory>\n");
	char *s = "hello world";
	*s = 'H';
#endif

#if SEG == 1
	puts("<null pointer dereference>\n");
	int *ptr = NULL;
	*ptr = 1;
#endif

#if SEG == 2
	puts("<stack overflow>");
	main();
#endif

}

