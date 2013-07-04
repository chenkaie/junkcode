#include "thread_tool.h"
#include <stdio.h>
#include <pthread.h>

void thread_sleep(size_t s)
{
    fprintf(stderr, "thread#%d: sleep for %d seconds...\n",
            pthread_self(), s);
    struct timespec ts = {0};
    ts.tv_sec = s;
    nanosleep(&ts, 0);
}
