#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
	long mtype;     /* message type, must be > 0 */
	int a,b;	/* data */		 
};

int main(void){
	int qid;
	key_t key=0x12345;
	struct msgbuf buf;

	qid=msgget(key,0);
    printf("[%s] qid = %d\n", __func__, qid);
	
	msgrcv(qid,&buf,sizeof(buf)-sizeof(long),9,0);
	printf("msg type:%d a=%d b=%d\n",buf.mtype,buf.a,buf.b);

	msgrcv(qid,&buf,sizeof(buf)-sizeof(long),0,0);
	printf("msg type:%d a=%d b=%d\n",buf.mtype,buf.a,buf.b);
}
