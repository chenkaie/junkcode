#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main(void){
	int sid;
	FILE *fp;
	fp=fopen("/tmp/sid.tmp","w");

	sid=semget(IPC_PRIVATE,1,0660);
	printf("semaphore id:%d\n",sid);
	
	fprintf(fp,"%d",sid);
}
