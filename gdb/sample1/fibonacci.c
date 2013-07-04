#include <stdio.h>

int fib(int n) 
{
	/* Ending condition of recursive */
	if (n == 0) {
		return 0;
	}
	/* Ending condition of recursive */
	else if (n == 1) {
		return 1;
	}
	else {
		return fib(n - 1) + fib(n - 2);
	}
}

int main() 
{
	printf("%d\n", fib(5));
	return 0;
}

