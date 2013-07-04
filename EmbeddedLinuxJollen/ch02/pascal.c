#include <stdio.h>

main()
{
   int i, j;
   int c, c0, c1;

   c0 = 0;
   c1 = 1;

   for (i = 0; i < 5; i++) {
      for (j = 0; j < i; j++) {
         c = c0+c1;
         printf("%3d", c);
         c0 = c1;
         c1 = c;
      }
      printf("\n");
   }
}
