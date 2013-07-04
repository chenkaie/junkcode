#include <stdio.h>
#include <unistd.h> 
void main() {
    FILE *fp=fopen("asd","w");
#if 1    
    printf("ret =%d\n",ftrylockfile(fp));
    flockfile(fp);
    getchar();
    funlockfile(fp);
#endif    
    fclose(fp);
}
