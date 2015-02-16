#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_1 = PTHREAD_COND_INITIALIZER;

char tmp[100];

static void cleanup_handler(void *arg)
{
    char* ptr = (char*)arg;
    pthread_mutex_unlock(&mtx);
}

static void cleanup_handler_1(void *arg)
{
    char* ptr = (char*)arg;
    
    pthread_mutex_unlock(&mtx);
}

static void *thread_func(void *arg)
{
    pthread_cleanup_push(cleanup_handler, tmp);
   
    pthread_mutex_lock(&mtx);           
    
    pthread_cond_wait(&cond, &mtx);
                           
    pthread_mutex_unlock(&mtx);             

    pthread_cleanup_pop(0);

    return NULL;
}

static void *thread_func_1(void *arg)
{
    pthread_cleanup_push(cleanup_handler_1, tmp);
   
    printf("B: START\n");
    pthread_mutex_lock(&mtx);           
    
    pthread_cond_wait(&cond_1, &mtx);  //你會發現有cond_1 ,mtx ,在wait時 , 會將mtx release ,意味其他的thread可以做pthread_mutex_lock                                  

    pthread_mutex_unlock(&mtx);             

    pthread_cleanup_pop(0);
    
    return NULL;
}

int main(void)
{
    int i;
    pthread_t tid;
    pthread_t tid_1;
    
    pthread_create(&tid , NULL, thread_func  , NULL);
    pthread_create(&tid_1, NULL, thread_func_1, NULL);      

    pthread_mutex_lock(&mtx);
    pthread_mutex_unlock(&mtx);
    
    pthread_cond_signal(&cond);
    pthread_cancel(tid);
    pthread_cancel(tid_1);
    pthread_join(tid, NULL);
    return 0;
}
