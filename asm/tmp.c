#include <stdio.h>
int tmp;
int main(void)
{
    int i;
    printf("tmp is originally %d\n",tmp);
    for(i=0;i<20;i++)
    {
        asm (
                "cmpl $10,%ebx\n"
                "jne dont\n"
                "movl %ebx,tmp\n"
                "dont:\n"
            );
        printf("%d\n",i);
        printf("\nnow tmp is %d\n",tmp);
    }
    return 0;
}
