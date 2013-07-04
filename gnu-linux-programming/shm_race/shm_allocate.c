#include <stdio.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 

int main(int argc, char *argv[])
{
   int seg_id;
   int seg_size = 0x4000;
   char *shared_memory;

   /* shared memory: allocate */
   seg_id = shmget(IPC_PRIVATE, seg_size, 
                   IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
   printf("Shared Memory Segment ID: %d\n", seg_id);

   /* shared memory: attach */
   shared_memory = (char *)shmat(seg_id, 0, 0);
   
   /* write to shared memory */
   sprintf(shared_memory, argv[1]);

   /* shared memory: detach */
   shmdt(shared_memory);

   exit(0);
}
