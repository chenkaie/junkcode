#include <stdio.h>
#include <string.h>
//#include <sys/file.h>
#include <unistd.h>
 #include <sys/types.h>
       #include <sys/stat.h>
#include <errno.h>

char line1[]  = "aaaaaaaaaa\n";
char line21[] = "ababababab\n";
char line22[] = "bbbbbbbbbb\n";
char line3[]  = "cccccccccc\n";

/* char buffer[1000]; */

int main(int argc, char *argv[])
{
        FILE    *f;
        int     len = strlen(line1);

        f = fopen("tst.out", "rb+");    /* step 1 */
        /* 
        ** setvbuf(f, buffer, _IOFBF, 129);
        **            - or -
        ** setvbuf(f, NULL, _IONBF, 0);
        */
    #if 0
    int  iSize, iValue = 0;
    int  iFileNo;
    iFileNo = fileno(fptr);
    iValue = flock(iFileNo, LOCK_SH); // work
    printf("after lock file, %d\n", iValue);
    printf("before flockfile 1 : fileno = %d\n", iFileNo);
    #endif

    printf("before flockfile 1\n");
    flockfile(f);
    printf("after flockfile 1\n");

        fwrite(line1, 1, len, f);
        fwrite(line21, 1, len, f);      /* step 2 */
        fflush(f);                      /* step 3 */
        fseek(f, 1*len, SEEK_SET);      /* step 4 */
        fflush(f);                      /* step 5 */
        sleep(3);
        fwrite(line22, 1, len, f);
        fwrite(line3, 1, len, f);       /* step 6 */
        fclose(f);
    printf("before funlockfile 1\n");
    funlockfile(f);
    printf("after funlockfile 1\n");
        return(0);                      /* step 7 */
}
