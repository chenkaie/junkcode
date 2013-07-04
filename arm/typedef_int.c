#include <stdio.h>
int test (short *data);

int test (short *data)
{
    unsigned int     idx;
    int                    sum = 0;
    for (idx = 0; idx < 64; idx++) {
        sum += *(data++);
    }
    return sum;
}

int main(int argc, const char *argv[])
{
    /*unsigned int buff[32];
    buff[0] = 0xFF;
    buff[1] = 0x04;
    buff[2] = 0x01;

    fprintf(stderr, "[%s] buf + %d\n", __FUNCTION__, buff[0]);
    fprintf(stderr, "[%s] buf + %d\n", __FUNCTION__, buff[1]);
    fprintf(stderr, "[%s] buf + %d\n", __FUNCTION__, buff[2]);*/

    short x = 1;
    test(&x); 
    return 0;
}

