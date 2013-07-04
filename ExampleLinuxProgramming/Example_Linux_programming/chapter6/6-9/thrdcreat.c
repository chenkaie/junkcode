/*
 * thrdcreat.c - Illustrate creating a thread
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void task1(int *counter);
void task2(int *counter);
void cleanup(int counter1, int counter2);

int g1 = 0;
int g2 = 0;

int main(int argc, char *argv[])
{
	pthread_t thrd1, thrd2;
	int ret;

	/* Create the first thread */
	ret = pthread_create(&thrd1, NULL, (void *)task1, (void *)&g1);
	if(ret) {
		perror("pthread_create: task1");
		exit(EXIT_FAILURE);
	}
	/* Create the second thread */
	ret = pthread_create(&thrd2, NULL, (void *)task2, (void *)&g2);
	if(ret) {
		perror("pthread_create: task2");
		exit(EXIT_FAILURE);
	}

	pthread_join(thrd2, NULL);
	pthread_join(thrd1, NULL);
	
	cleanup(g1, g2);

	exit(EXIT_SUCCESS);
}

void task1(int *counter)
{
	while(*counter < 5) {
		printf("task1 count: %d\n", *counter);
		(*counter)++;
		sleep(1);
	}
}

void task2(int *counter)
{
	while(*counter < 5) {
		printf("task2 count: %d\n", *counter);
		(*counter)++;
	}
}

void cleanup(int counter1, int counter2)
{
	printf("total iterations: %d\n", counter1 + counter2);
}
