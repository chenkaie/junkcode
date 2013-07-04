#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>

struct job_s
{
   int status;
   struct job_s *next;
};

struct job_s *job;

/* Critical section protection. */
pthread_mutex_t job_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Semaphore variable. */
sem_t job_semaphore;

void *add_job()
{
   struct job_s *new_job;
   char inp[32];
   int count;

   while (1) {
      printf("\n------Input a job------\n");
      printf("Job status: ");
      scanf("%s", inp);

      new_job = (struct job_s *)malloc(sizeof(struct job_s));
      new_job->status = atoi(inp);

      if (new_job->status == 0) 
         return NULL;

      /* Critical section. */
      sem_wait(&job_semaphore);
      pthread_mutex_lock(&job_mutex);

      new_job->next = job;
      job = new_job;

      pthread_mutex_unlock(&job_mutex);
      sem_post(&job_semaphore);
   }
}

void *remove_job()
{
   struct job_s *this_job;
   int count;

   while (1) {
      count = 0;
      sleep(5);

      sem_wait(&job_semaphore);
      pthread_mutex_lock(&job_mutex);

      for (this_job = job; this_job != NULL;  this_job = this_job->next)
         if (this_job->status == 0) 
            count++;
      
      pthread_mutex_unlock(&job_mutex);
      sem_post(&job_semaphore);

      printf("\n%d job(s) done.\n", count);
   }
}

void *process_job()
{
   struct job_s *this_job;

   while (1) {
      sleep(5);

      sem_wait(&job_semaphore);
      pthread_mutex_lock(&job_mutex);

      for (this_job = job; this_job != NULL;  this_job = this_job->next)
         if (this_job->status > 0) 
            this_job->status--;
      
      pthread_mutex_unlock(&job_mutex);
      sem_post(&job_semaphore);
   }
}

int main()
{
   pthread_t thread_id1, thread_id2, thread_id3;

   job = NULL;
   sem_init(&job_semaphore, 0, 0);

   pthread_create(&thread_id1, NULL, &add_job, NULL);
   pthread_create(&thread_id2, NULL, &remove_job, NULL);
   pthread_create(&thread_id3, NULL, &process_job, NULL);

   /* Post operation. */
   sem_post(&job_semaphore);

   /* Wait for add_job() */
   pthread_join(thread_id1, NULL);

   return 0;
}
