// ---------------------------------------------
// 1. read uninitialized memory
// 2. access out of bound
// ---------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define EXAMPLE
void OutOfBoundTest(void)
{
    char     *pchTest;
    char      achTest[228];
    size_t    stSize = (size_t)128;
    int         i;


    stSize += 100;
    pchTest = (char *)malloc(stSize);

    //memset(achTest, 0, sizeof(achTest) - 10);
    if(pchTest == NULL)
    {
        return;
    }
    // read uninitialized memory
    i = pchTest[0];

    // access out of bound 230 > (128 + 100)
    for(; i < 230; i++)
    {
        // achTest is uninitialized
        pchTest[i] = achTest[i];
    }

    free(pchTest);
}

int main (void)
{
    OutOfBoundTest()
        return EXIT_SUCCESS;
}

