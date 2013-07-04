#include <stdio.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 

int main(int argc, char *argv[])
{
   int seg_id;
   char *shared_memory;

   /* get shmid */
   seg_id = atoi(argv[1]);

   /* shared memory: attach */
   shared_memory = (char *)shmat(seg_id, 0, 0);
   
   /* write to shared memory */
   printf("Message of Shared Memory: %s\n", shared_memory);

   /* shared memory: detach */
   shmdt(shared_memory);

   /* Deallocate shared memory */
   shmctl(seg_id, IPC_RMID, 0);

   exit(0);
}
