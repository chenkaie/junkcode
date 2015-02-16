
/*
 *  Pthreads version of example from MSDN on using conditional variables.
 *  A better way would be to have separate queue class that acts as a monitor.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

#define BUFFER_SIZE 10
#define PRODUCER_SLEEP_TIME_MS 500
#define CONSUMER_SLEEP_TIME_MS 2000

long Buffer[BUFFER_SIZE];
long LastItemProduced;
unsigned long QueueSize;
unsigned long QueueStartOffset;

unsigned long TotalItemsProduced;
unsigned long TotalItemsConsumed;

pthread_cond_t BufferNotEmpty;
pthread_cond_t BufferNotFull;
pthread_mutex_t   BufferLock;

int StopRequested;


void *ProducerThreadProc (void * p)
{
    unsigned long ProducerId = (unsigned long)(unsigned long *)p;

    printf ("Producer %lu starting\n", ProducerId);
    while (TRUE)
    {
        // Produce a new item.

		// sleep in microseconds
        usleep (rand() % PRODUCER_SLEEP_TIME_MS * 1000);

        pthread_mutex_lock (&BufferLock);
        unsigned long Item = LastItemProduced++;
        while (QueueSize == BUFFER_SIZE && StopRequested == FALSE) {
            // Buffer is full - wait so consumers can get items.
            pthread_cond_wait (&BufferNotFull, &BufferLock);
        }
        if (StopRequested == TRUE) {
            pthread_mutex_unlock (&BufferLock);
            break;
        }
        // Insert the item at the end of the queue and increment size.
        Buffer[(QueueStartOffset + QueueSize) % BUFFER_SIZE] = Item;
        QueueSize++;
        TotalItemsProduced++;
        printf ("Producer %lu: item %2ld, queue size %2lu\n", ProducerId, Item, QueueSize);
        pthread_mutex_unlock (&BufferLock);

        // If a consumer is waiting, wake it.
        pthread_cond_signal (&BufferNotEmpty);
    }
    printf ("Producer %lu exiting\n", ProducerId);
    return 0;
}

void *ConsumerThreadProc (void * p)
{
    unsigned long ConsumerId = (unsigned long)(unsigned long *)p;

    printf ("Consumer %lu starting\n", ConsumerId);
    while (TRUE)
    {
        pthread_mutex_lock (&BufferLock);

        while (QueueSize == 0 && StopRequested == FALSE)
        {
            // Buffer is empty - sleep so producers can create items.
            pthread_cond_wait(&BufferNotEmpty, &BufferLock);
        }

        if (StopRequested == TRUE && QueueSize == 0)
        {
            pthread_mutex_unlock (&BufferLock);
            break;
        }

        // Consume the first available item.

        long Item = Buffer[QueueStartOffset];

        QueueSize--;
        QueueStartOffset++;
        TotalItemsConsumed++;

        if (QueueStartOffset == BUFFER_SIZE)
        {
            QueueStartOffset = 0;
        }

        printf ("Consumer %lu: item %2ld, queue size %2lu\n", ConsumerId, Item, QueueSize);

        pthread_mutex_unlock (&BufferLock);

        // If a producer is waiting, wake it.

        pthread_cond_signal (&BufferNotFull);

        // Simulate processing of the item. Argument in microseconds

        usleep (rand() % CONSUMER_SLEEP_TIME_MS * 1000);
    }

    printf ("Consumer %lu exiting\n", ConsumerId);
    return 0;
}

int main (int argc, char* argv[])
{
	pthread_t hProducer1, hConsumer1, hConsumer2;
    pthread_cond_init (&BufferNotEmpty, NULL);
    pthread_cond_init (&BufferNotFull, NULL);

    pthread_mutex_init (&BufferLock, NULL);


    pthread_create (&hProducer1, NULL, ProducerThreadProc, (void *)1);
    pthread_create (&hConsumer1, NULL, ConsumerThreadProc, (void *)1);
    pthread_create (&hConsumer2, NULL, ConsumerThreadProc, (void *)2);

	puts("\n");
    puts ("Press enter to stop...");
	puts("\n");
    getchar();

    pthread_mutex_lock (&BufferLock);
    StopRequested = TRUE;
    pthread_mutex_unlock (&BufferLock);

    pthread_cond_broadcast (&BufferNotFull);
    pthread_cond_broadcast (&BufferNotEmpty);

    pthread_join (hProducer1, NULL);
    pthread_join (hConsumer1, NULL);
    pthread_join (hConsumer2, NULL);

    printf ("TotalItemsProduced: %lu, TotalItemsConsumed: %lu\n", TotalItemsProduced, TotalItemsConsumed);
	exit(0);
}

