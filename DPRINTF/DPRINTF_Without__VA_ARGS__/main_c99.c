#include "dprintf.h"
#include "thread_tool.h"
#include <pthread.h>

int g_enable = 1;
int g_data   = 3;

void* main_thread(void* param)
{
    ENTER_FUNCTION();
    thread_sleep(1);
    DPRINTF(g_enable, "g_data == %d", g_data);
    return 0;
}

void* other_thread(void* param)
{
    ENTER_FUNCTION();
    thread_sleep(2);
    DPRINTF(g_enable, "g_data == %d", g_data);
    return 0;
}

int main()
{
    pthread_t other_thr;
    pthread_create(&other_thr, NULL, other_thread, NULL);
    main_thread(0);
    pthread_join(other_thr, NULL);

    return 0;
}
