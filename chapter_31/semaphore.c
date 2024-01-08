#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

sem_t s;

// As locks

sem_init(&s, 0, 1);		// 1 - the value that semaphore stores

sem_wait(&s);
/* critical section */
sem_post(&s);

// For ordering an execution flow

void* child(void* arg)
{
	printf("Child\n");
	sem_post(&s);
	return NULL;
}

int main()
{
	sem_init(&s, 0, 0);
	printf("Begin main\n");
	
	pthread_t p;
	int r = pthread_create(&p, NULL, child, NULL);
	assert(r == 0);
	sem_wait(&s);
	
	printf("End main\n");
	return 0;
}