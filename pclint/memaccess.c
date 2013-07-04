// ---------------------------------------------
// 1. dereference NULL pointer
// 2. did not free allocated memory
// ---------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define EXAMPLE
void UsingPointer(char *pchData)
{
    *pchData = '0';
}

char NullDerefNoFreeTest(void)
{
    char * const pchTest = malloc(1);
#ifdef EXAMPLE
    // did not check whether pchTest is NULL
    *pchTest = 1;
#else
    if (pchTest != NULL) *pchTest = 1;
#endif
    
    UsingPointer(pchTest);

#ifdef EXAMPLE
    // did not free pchTest at end
    return *pchTest;
#endif
}

int main (int argc, char const* argv[])
{
    NullDerefNoFreeTest();
    return EXIT_SUCCESS;
}

