#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

//FILE *fp;

void test(void *ptr)
{
    //	FILE *fp;
    printf("[1]Thread id: %d\n", (long)syscall(SYS_gettid));

    //fp = fopen("/mnt/ramdisk/video.txt", "r");
    //(FILE*)ptr = fopen("/home/elia/keke.keke", "r");
    FILE *fp;

    fp = (FILE*) ptr;

    printf("[1]locking file.\n");
    flockfile(fp);

    printf("[1]press any key to unlock the file.\n");
    
    fprintf(fp,"[1] press any key to unlock the file.\n");
    getchar();

    funlockfile(fp);

    printf("[1]unlocked file.\n");

    flockfile(fp);

    printf("[1]press any key to unlock the file.\n");
    
    fprintf(fp,"[1] press any key to unlock the file.\n");
    getchar();

    funlockfile(fp);
    pthread_exit("[1] exit");
    //	return 0;
}

void test2(void *ptr)
{
    //	FILE *fp;
    printf("[2]Thread id: %d\n", (long)syscall(SYS_gettid));

    //fp = fopen("/mnt/ramdisk/video.txt", "r");
    //(FILE*)ptr = fopen("/home/elia/keke.keke", "r");
    FILE *fp;

    fp = (FILE*) ptr;

    printf("[2]locking file.\n");
    flockfile(fp);

    printf("[2]press any key to unlock the file.\n");

    fprintf(fp,"[2] press any key to unlock the file.\n");

    getchar();

    funlockfile(fp);

    printf("[2]unlocked file.\n");
    pthread_exit("[2] exit");
}


int main(void)
{
    pthread_t thread1, thread2;
    FILE *fp;

    fp = fopen("flockfile.txt", "a+");
    fprintf(fp,"Start write...\n");
    pthread_create( &thread1, NULL,
            (void*)&test, (void*)fp);

    pthread_create(&thread2, NULL,
            (void*)&test2, (void*)fp);

    printf("main thread: %d\n", (long)syscall(SYS_gettid));
    /*
    for (;;){
        //printf("main thread: %u\n", (unsigned int)pthread_self());
        printf("main thread: %d\n", (long)syscall(SYS_gettid));
        sleep(1);
        //sleep(1000);
    }*/
    system("date");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    system("date");

    fclose(fp);

    return 0;
}

