//http://stackoverflow.com/questions/2500362/running-32-bit-assembly-code-on-a-64-bit-linux-64-bit-processor-explain-the
#include <asm/unistd.h>
#include <syscall.h>
#define STDOUT 1

    .data
hellostr:
    .ascii "hello wolrd\n" ;
helloend:

    .text
    .globl main

main:
    movl $(SYS_write) , %eax  //ssize_t write(int fd, const void *buf, size_t count);
    movl $(STDOUT) , %ebx
    movl $hellostr , %ecx
    movl $(helloend-hellostr) , %edx
    int $0x80

    movl $(SYS_exit), %eax //void _exit(int status);
    xorl %ebx, %ebx
    int $0x80

    ret
