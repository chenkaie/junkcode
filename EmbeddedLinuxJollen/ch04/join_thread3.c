#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *print_hello(void *argu)
{
   int i;

   printf("Hello,\n");
   
   return NULL;
}

void *print_world(void *argu)
{
   int i;
   int thread_id;

   thread_id = *((int *)argu);
   pthread_join(thread_id, NULL);

   printf("World!\n");

   return NULL;
}

int main()
{
   pthread_t thread_id1, thread_id2;
   char thread_argu1[256];
   char thread_argu2[256];

   pthread_create(&thread_id1, NULL, &print_hello, NULL);
   pthread_create(&thread_id2, NULL, &print_world, &thread_id1);
   pthread_join(thread_id2, NULL);

   printf("--End of The Program.--\n");

   return 0;
}
