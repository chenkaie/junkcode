#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *my_lower(void *argu)
{
   char x;

   x = *((char *)argu);
   x |= 0x20;

   return (void *)x;
}

int main()
{
   char x = 'R';
   pthread_t thread_id;

   pthread_create(&thread_id, NULL, &my_lower, &x);
   pthread_join(thread_id, (void *)&x);

   printf("Return Value: %c\n", x);
   return 0;
}
