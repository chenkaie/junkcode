#include <stdio.h>
#include <string.h>
//#include <sys/file.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

char line1[]  = "1111111111\n";
char line21[] = "2121212121\n";
char line22[] = "2222222222\n";
char line3[]  = "1234567890\n";
/* char buffer[1000]; */

int main(int argc, char *argv[])
{
    FILE    *f;
    int     len = strlen(line1);

    f = fopen("fwrite.txt", "r+");    /* step 1 */
    /* 
     ** setvbuf(f, buffer, _IOFBF, 129);
     **            - or -
     ** setvbuf(f, NULL, _IONBF, 0);
     */

    //fwrite(line1, 1, len, f);
    //fwrite(line21, 1, len, f);      /* step 2 */
    //fflush(f);                      /* step 3 */
    //fseek(f, 0L, SEEK_SET);      /* step 4 */
    
    
    fseek(f, -11, SEEK_END);      /* step 4 */
    printf("SEEK_END ftell = %d\n",ftell(f));
    char buf[16];
    memset(buf, 0 ,sizeof(buf));
    if( fgets(buf, 16, f) != NULL)
    {
        printf("fgets: %s",buf);
    }
    fseek(f, -11, SEEK_END);      /* step 4 */
    printf("SEEK_END ftell = %d\n",ftell(f));
    long lTotalSize = atol(buf) + 99999;
    int paddingZero = 1; 
    printf("lTotalSize = %ld\n",lTotalSize);
    while((lTotalSize /= 10) > 0)
    {
        paddingZero++;
    }
    char tmpbuf[11];
    memset(tmpbuf, 0 ,sizeof(tmpbuf));
    int i = 0;
    for(i = 0; i < 10-paddingZero ; i++)
    {
        strcat(tmpbuf,"0");
    }
    printf("paddingZero = %d, buf = %s,tmpbuf = %s\n",paddingZero, buf, tmpbuf);
    strcat(tmpbuf, buf);
    tmpbuf[11] = '\0';
    printf("%s\n", tmpbuf);
    //fprintf(f,"%s",buf);
    //fputs(buf, f);
    fclose(f);
}
