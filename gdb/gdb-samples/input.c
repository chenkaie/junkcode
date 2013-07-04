#include <stdio.h>
#define nobug
static char buff [256];
static char* string;

int main ()
{
	printf ("Please input a string: ");
#ifdef bug
	gets (string);
	printf ("\nYour string is: %s\n", string);
#else
	gets (buff);
	printf ("\nYour string is: %s\n", buff);
#endif
	return 0;
}
