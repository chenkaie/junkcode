#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *thread_function(void *arg)
{
    printf("Hello World from %d!\n", arg);
    sleep(10);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int i;

    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, thread_function, (void *)i);

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
