#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 1024

int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value)
{
	buffer[fill] = value;
	fill = (fill + 1) % MAX;
}

int get()
{
	int tmp = buffer[use];
	use = (use + 1) % MAX;
	return tmp;
}

sem_t full, empty, mutex;

void* producer(void* arg)
{
	for (int i = 0; i < loops; ++i)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		put(i);
		sem_post(&mutex);
		sem_post(&full);
	}
}

void* consumer(void* arg)
{
	int tmp = 0;
	while (tmp != -1)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		tmp = get();
		sem_post(&mutex);
		sem_post(&empty);
		printf("%d\n", tmp);
	}
}

int main()
{
	
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, MAX);
	sem_init(&mutex, 0, 1);
	
	return 0;
}	