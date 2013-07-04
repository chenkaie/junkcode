#include <stdio.h>
int main()
{
	puts("Hello");
	__asm__ __volatile__("int3");
	puts("World");
	return 0;
}
