#include <stdlib.h>

int main(void)
{
    int *ptr;

    ptr = (int *)malloc(128 * 1024 - 30);
    free(ptr);
    free(ptr);

    return 0;
}

