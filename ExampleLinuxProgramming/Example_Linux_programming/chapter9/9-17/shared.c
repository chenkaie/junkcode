#include <sys/ipc.h>
#include <sys/shm.h>

int main(void){
	key_t key=0x12345;
	int mid;

	mid=shmget(key,1024,IPC_CREAT|0660);
}
