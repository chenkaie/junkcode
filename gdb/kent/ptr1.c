#include <stdio.h>
#include <stdlib.h>
#define MAX_TMP 1000
static char *my_str = "Hello World!";

inline test_printf(void)
{
    printf("[%s] test\n", __FUNCTION__);
}

dummy_function (void)
{
    unsigned char *ptr = 0x00;
    test_printf();
    fprintf(stderr, "[%s] %d\n", __FUNCTION__, MAX_TMP);
    *ptr = 0x00;
    fprintf(stderr, "[%s] %c\n", __FUNCTION__, ptr);
    fprintf(stderr, "[%s] >>><<< \n", __FUNCTION__);
}

int main (void)
{
    dummy_function ();

    return 0;
}
