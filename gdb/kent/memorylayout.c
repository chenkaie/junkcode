#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{
    char cmd[32];
    brk((void *)0x8051000);
    sprintf(cmd, "cat /proc/self/maps");
    system(cmd);
}
