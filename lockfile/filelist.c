#include <stdio.h>
#include <string.h>
//#include <sys/file.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

char line1[]  = "1111111111\n";
char line21[] = "2121212121\n";
char line22[] = "2222222222\n";
char line3[]  = "1234567890\n";
/* char buffer[1000]; */

int main(int argc, char *argv[])
{
    FILE    *f;
    int     len = strlen(line1);

#if 1
    
    f = fopen("fwrite.txt", "w+");
    if(!f)
    {
        if(errno == ENOENT)
        {
            fprintf(stderr, "Open file %s failed: %s, errno = %d, EEXIST= %d,f = %d\n", "fwrite", strerror(errno), errno, ENOENT, f);
        }
    }
#else
    int fd;
    fd = open("fwrite.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    f = fdopen(fd,"r+");
    if(!f)
    {
        fprintf(stderr, "_Open file %s failed: %s, errno = %d, EEXIST= %d,f = %d\n", "fwrite", strerror(errno), errno, ENOENT, f);
    }
#endif
    
    fseek(f, -10, SEEK_END);      /* step 4 */
    printf("SEEK_END ftell = %d\n",ftell(f));
    char buf[16];
    memset(buf, 0 ,sizeof(buf));
    if( fgets(buf, 16, f) != NULL)
    {
        printf("fgets: %s\n",buf);
    }
    fseek(f, -10, SEEK_END);      /* step 4 */
    printf("SEEK_END ftell = %d\n",ftell(f));
    long lTotalSize = atol(buf) + 1199999;
    int paddingZero = 1; 
    printf("lTotalSize = %ld\n",lTotalSize);
    long tmpTotalSize = lTotalSize;
    while((tmpTotalSize /= 10) > 0)
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
    sprintf(tmpbuf,"%s%ld",tmpbuf,lTotalSize);
    printf("tmpbuf = %s\n",tmpbuf);
    //fprintf(f,"%s",buf);
    fputs(tmpbuf, f);
    //sleep(20);
    fclose(f);
}
