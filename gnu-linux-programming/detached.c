#include <pthread.h>
#include <stdio.h>

void *print_hello(void *argu)
{
   while (1) {
      printf("Hello,\n");
      sleep(1);
   }
}

void *print_world(void *argu)
{
   while (1) {
      printf("World!\n");
      sleep(1);
   }
}

int main()
{
   pthread_attr_t attr;
   pthread_t thread_id1, thread_id2;

   /* Create detached threads. */
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

   pthread_create(&thread_id1, &attr, &print_hello, NULL);
   pthread_create(&thread_id2, &attr, &print_world, NULL);

   return 0;
}
