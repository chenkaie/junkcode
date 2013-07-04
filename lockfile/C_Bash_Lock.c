#include <stdio.h>
#include <string.h>
//#include <sys/file.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

//Touch and Remove "./touch_file" by yourself to run this program
int main(int argc, char *argv[])
{
    FILE    *f;
    
    f = fopen("./touch_file", "r");
    while(f)
    {
        printf("file exist f= %d\n",f);
        fclose(f);
        sleep(1);
        f = fopen("./touch_file", "r");
    }
    return 0;
}
