#include <stdio.h>
#include <unistd.h> 
#include <time.h>

int main() 
{
    FILE *fp=fopen("lockf.txt","a+");
    int ret = 0;
    while((ret = lockf(fileno(fp), F_TLOCK, 0)) < 0)
    {
        printf("lockf trylock ret = %d\n",ret);
        sleep(1);
    }
    printf("lock success\n");
    sleep(3);

    time_t now;
    struct tm *tms;
    time(&now);
    tms = localtime(&now);
    printf("%02d:%02d:%02d\n", tms->tm_hour, tms->tm_min, tms->tm_sec);   

    fprintf(fp,"Time : %02d:%02d:%02d\n", tms->tm_hour, tms->tm_min, tms->tm_sec);
    getchar();
    lockf(fileno(fp), F_ULOCK, 0);     
    fclose(fp);
    return 0;
}
