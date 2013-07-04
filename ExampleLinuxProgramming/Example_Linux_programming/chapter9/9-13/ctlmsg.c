#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	int qid;
	key_t key=0x12345;
	struct msqid_ds buf;

	qid=msgget(key,0);
	
	msgctl(qid,IPC_STAT,&buf);
	
	printf("uid:%d\n",buf.msg_perm.uid);
	printf("gid:%d\n",buf.msg_perm.gid);
	printf("cuid:%d\n",buf.msg_perm.cuid);
	printf("cgid:%d\n",buf.msg_perm.cgid);
	printf("mode:%o\n",buf.msg_perm.mode);
	printf("size:%d\n",buf.msg_qbytes);
}
