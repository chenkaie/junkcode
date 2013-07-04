#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	int qid;
	key_t key=0x12345;

	qid=msgget(key,IPC_CREAT|0666);
	printf("queue id:%d\n",qid);
}
