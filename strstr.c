#include<string.h>
#include <stdio.h>

main()
{
    char kent[16] = "";
    char * s="aaa&method=get&name=ccc&test=aaa";
    char *a, *b, *p, *q;
    printf("%d, %02x\n",('\0' == kent[0]), kent[0]);
    printf("%d, %02x\n",('\0' == ""), '\0');
    printf("%d, %02x\n",(kent[0] == ""), "");
    a =strchr(s,'&');
    b =strchr(s,'=');

    p= strstr(s,"name=");
    q= strstr(p,"&");
    printf("%c, %s\n",p[0], q);
}
