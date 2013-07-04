#include <stdio.h>
#include <stdlib.h>

int newSize = 0;
int delSize = 0;
#define new(TYPE, n) malloc(n*sizeof(TYPE)); newSize+=n*sizeof(TYPE)
#define del(ptr, TYPE, n) free(ptr); delSize+=n*sizeof(TYPE)
#define mcheck() printf("Memory:newSize=%d delSize=%d leakSize=%d\n", \
		newSize, delSize, newSize-delSize);

int main() 
{
	int *ip = new(int, 10);
	char *cp = new(char, 5);
	del(ip, int, 10);
	mcheck();
}
