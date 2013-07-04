#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <error.h>
#include <unistd.h>

#define SHMKEY 9999
#define SEMKEY 9999

#define MAX_USER	64
#define MAX_USERID_LEN	16
#define MAX_PRIVATE_MSG	32
#define MAX_MSG_LEN 	128

typedef struct {
	char data[MAX_MSG_LEN];
}MSG;

typedef struct {
	pid_t pid;
	char userid[MAX_USERID_LEN];
	int msg_count;
	MSG msg[MAX_PRIVATE_MSG];
}USER;

typedef struct{
	USER user[MAX_USER];
}SHM;

SHM *shm;
int semid;
char *userid;
int self;

struct sembuf lock_op[2]={
	0,0,0,
	0,1,SEM_UNDO
};

struct sembuf unlock_op[1]={
	0,-1,IPC_NOWAIT
};

void lock(){
	semop(semid,lock_op,2);
}

void unlock(){
	semop(semid,unlock_op,1);
}

void signal_handler(int signo){
	int i;
	lock();
	printf("\n");
	//print private message
	for(i=0;i<shm->user[self].msg_count;i++){
	
		printf("%s\n",shm->user[self].msg[i].data);
	}
	fflush(stdout);
	shm->user[self].msg_count=0;
	unlock();
}

void error_exit(char *error_msg){
	printf("%s\n",error_msg);
	exit(-1);
}

int get_user_index(char *userid){
	int i;
	for(i=0;i<MAX_USER;i++){
		if(shm->user[i].pid>0 && strcmp(userid,shm->user[i].userid)==0) break;
	}
	if(i==MAX_USER) return(-1);
	return(i);
}

int list(int flag){
	int i,count;
	count=0;
	for(i=0;i<MAX_USER;i++){
		if(shm->user[i].pid>0){
			if(kill(shm->user[i].pid,0)<0){
				shm->user[i].pid=-1;
			}else{
				if(flag){
					count++;
					printf("[%d] %s\n",shm->user[i].pid,shm->user[i].userid);	
				}
			}
		}
	}
	return(count);
}

int login(char *userid){
	int i;
	lock();
	//kill dead process
	list(0);
	//check duplicate login
	if(get_user_index(userid)>=0){
		error_exit("already login\n");
	}
	//find empry slot 
	for(i=0;i<MAX_USER;i++){
		if(shm->user[i].pid<=0) break;
	}	
	if(i==MAX_USER) error_exit("too many users");
	self=i;
	shm->user[self].pid=getpid();
	strncpy(shm->user[self].userid,userid,MAX_USERID_LEN);
	shm->user[self].msg_count=0;
	unlock();
}

int write_private_msg(char *userid,char *msg){
	int index;
	lock();
	if((index=get_user_index(userid))<0){
		unlock();
		return(-1);
	}
	if(shm->user[index].msg_count<MAX_PRIVATE_MSG){
		snprintf(shm->user[index].msg[shm->user[index].msg_count++].data,MAX_MSG_LEN,"%s: %s",userid,msg);
	}
	unlock();
	kill(shm->user[index].pid,SIGUSR1);
}

int main(int argc,char *argv[]){
	struct sigaction sig;
	int shmid,i;
	char buf[256];

	if(argc!=2){
		error_exit("Usage: chat <name>");
	}
	userid=(char *)strndup(argv[1],MAX_USERID_LEN);

	if((shmid=shmget(SHMKEY,0,0))<0){
		if((shmid=shmget(SHMKEY,sizeof(SHM),IPC_CREAT|IPC_EXCL|0660))<0){
			error_exit("get share memory error");
		}
	}
	printf("shmid=%d\n",shmid);


	if((semid=semget(SEMKEY,1,0))<0){
		if((semid=semget(SEMKEY,1,IPC_CREAT|IPC_EXCL|0660))<0){
			error_exit("get semaphore error");
		}
	}
	printf("semid=%d\n",semid);

	//regisger signal handler
	sig.sa_handler=signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags=0;
	sigaction(SIGUSR1,&sig,0);
	
	//attach to shared memory
	shm=shmat(shmid,0,0);
	printf("login as %s\n",userid);
	login(userid);

	//process user input
	for(;;){
		printf("%s> ",userid);
		if(fgets(buf,sizeof(buf),stdin)==NULL){
			continue;
		}	
		if(strncmp(buf, "write",5)==0){
			char *ptr,*p1,*p2,*p3;
			p1=strtok_r(buf," ",&ptr);
			p2=strtok_r(NULL," ",&ptr);
			p3=strtok_r(NULL,"\n",&ptr);

			if(p3!=0){
				write_private_msg(p2,p3);
			}else{
				printf("argument error\n");
			}
			continue;
		}
		if(strncmp(buf, "list",4)==0){
			printf("USER LIST\n===================\n");
			printf("===================\ntotal users: %d\n",list(1));
			continue;
		}
		if(strncmp(buf, "quit",4)==0){
			printf("BYE BYE\n");
			exit(-1);
		}
		printf("unknown command\n");
	}
}

