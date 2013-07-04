#include <stdio.h>
void main() {
    FILE *f=fopen("asd","w");
    printf("ftrylockfile = %d\n",ftrylockfile(f));
    flockfile(f);
    getchar();
    fprintf(f,"shitshishit");
    funlockfile(f);
    fclose(f);
}
