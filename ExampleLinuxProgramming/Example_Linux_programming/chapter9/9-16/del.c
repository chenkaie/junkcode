#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main(void){
	int sid;
	FILE *fp;
	fp=fopen("/tmp/sid.tmp","r");
	fscanf(fp,"%d",&sid);

	printf("semaphore id:%d\n",sid);
	
	semctl(sid,0,IPC_RMID);
}
