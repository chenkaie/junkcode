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
   
   /* read shared memory */
   for (;;) {
      printf("Message of Shared Memory: %s\n", shared_memory);
      sleep(1);
   }

   /* shared memory: detach */
   shmdt(shared_memory);

   exit(0);
}
