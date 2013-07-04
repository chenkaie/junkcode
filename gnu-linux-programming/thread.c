#include <pthread.h>
#include <stdio.h>

void *print_hello(void *argu)
{
   while (1) {
      printf("Hello,\n");
      sleep(1);
   }
   return NULL;
}

void *print_world(void *argu)
{
   while (1) {
      printf("World!\n");
      sleep(1);
   }
   return NULL;
}

int main()
{
   pthread_t thread_id1, thread_id2;

   pthread_create(&thread_id1, NULL, &print_hello, NULL);
   pthread_create(&thread_id2, NULL, &print_world, NULL);

   while (1) {
      printf("-------------------------\n");
      sleep(1);
   }
   return 0;
}
