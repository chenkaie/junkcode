#include <stdio.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 

int main(int argc, char *argv[])
{
   int i;
   int seg_id;
   char *shared_memory;

   /* get shmid */
   seg_id = atoi(argv[1]);

   /* shared memory: attach */
   shared_memory = (char *)shmat(seg_id, 0, 0);
   
   /* write to shared memory */
   for (i = 0; ;i++, i %= 10) {
      sprintf(shared_memory, "%d%d%d%d%d%d%d%d", i,i,i,i,i,i,i,i);
   }

   exit(0);
}
