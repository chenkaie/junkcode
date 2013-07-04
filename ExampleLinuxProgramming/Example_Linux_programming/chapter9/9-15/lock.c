#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <signal.h>

int sid;
struct sembuf lockop[2]={
	0, 0, 0,
	0, 1, SEM_UNDO
};
struct sembuf unlockop[1]={
	0, -1, IPC_NOWAIT
};

void unlock(int arg){
	printf("unlock\n");
	semop(sid,unlockop,1);
}

int main(void){
	FILE *fp;
	signal(SIGUSR1,unlock);

	fp=fopen("/tmp/sid.tmp","r");
	fscanf(fp,"%d",&sid);
	printf("semaphore id:%d\n",sid);
	
	semop(sid,lockop,2);
	printf("get lock\n");
	for(;;) sleep(60);
}
