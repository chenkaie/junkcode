#include <stdio.h>

int wib(int no1, int no2)
{
    int result, diff;
    diff = no1 - no2;
    result = no1 / diff;
    return result;
}

int main(int argc, char *argv[])
{
    int value, div, result, i, total;

    value = 10;
    div = 6;
    total = 0;

    for(i = 0; i < 10; i++)
    {
        result = wib(value, div);
        total += result;
        div++;
        value--;
    }

    printf("%d wibed by %d equals %d\n", value, div, total);
    return 0;
}
