#include <stdio.h>

int x = 10;
int y = 20;
int z = 30;

extern int __data_start;

int main(void)
{
	int *ds = &__data_start;

	printf("%p\n", ds);
	printf("now x = %d\n", x);

	ds+=3;
	*ds = 100;
	printf("now x = %d\n", x);
}
