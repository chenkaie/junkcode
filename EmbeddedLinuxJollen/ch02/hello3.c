#include <stdio.h>

main()
{
#ifdef LINUX
   printf("Hello, LINUX!\n");
#endif
   printf("Hello, World.\n");
}
