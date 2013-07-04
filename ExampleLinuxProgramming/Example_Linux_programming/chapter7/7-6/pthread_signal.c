#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void signal_handler(int arg){
	printf("process %d catch signal:%d\n",getpid(),arg);
}

void * thread1(void *arg){
	sigset_t newmask,oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	sigaddset(&newmask,SIGQUIT);
	pthread_sigmask(SIG_SETMASK,&newmask,&oldmask);

	int fd=open("/1",O_RDONLY);
	int totalReadSize=0;
	int readSize;
	int count=0;
	char buf[1024];
	
	while((readSize=read(fd,buf,sizeof(buf)))!=0){
		totalReadSize+=readSize;
		count++;
		if(count==10240){
			printf("totalReadSize=%d\n",totalReadSize);
			count=0;
		}
	}
	printf("totalReadSize=%d\n",totalReadSize);
	close(fd);
	//pthread_sigmask(SIG_SETMASK,&oldmask,NULL);
}

void * thread2(void *arg){
	sigset_t newmask,oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	pthread_sigmask(SIG_SETMASK,&newmask,&oldmask);

	int i;
	for(i=0;i<15;i++){
		printf("sleep: %d\n",i);
		sleep(1);
	}
}

int main(){
	struct sigaction sig;
	pthread_t t1,t2;
	
	sig.sa_handler=signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags=0;
	
	pthread_create(&t1,NULL,thread1,NULL);
	pthread_create(&t2,NULL,thread2,NULL);
	
	sigaction(SIGINT,&sig,NULL);
	sigaction(SIGQUIT,&sig,NULL);
	
	pthread_join(t2,NULL);
	pthread_join(t1,NULL);
}
