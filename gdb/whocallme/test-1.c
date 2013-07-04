#include <stdio.h>
void test()
{
	unsigned int *stack;
	asm ("movl %%ebp, %0\n"
	     : "=g"(stack));
	printf("Return address = 0x%x\n", *(stack+1));
}

int main()
{
	test();
}
