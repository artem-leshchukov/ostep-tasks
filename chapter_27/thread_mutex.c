#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>


static volatile int counter = 0;

static pthread_mutex_t lock;

void* mythread(void* arg)
{
	int rc = pthread_mutex_lock(&lock);
	assert(rc == 0);
	
	printf("Thread %s begin.\n", (char*) arg);
	for (int i = 0; i < 100; ++i)
		++counter;
	printf("Thread %s end.\n", (char*) arg);
	
	rc = pthread_mutex_unlock(&lock);
	assert(rc == 0); 
	
	return NULL;
}

int main()
{	
	int rc = pthread_mutex_init(&lock, NULL);
	assert(rc == 0);

	pthread_t p1, p2;
	int rc1 = pthread_create(&p1, NULL, mythread, "A");
	int rc2 = pthread_create(&p2, NULL, mythread, "B");
	assert(rc1 == 0);
	assert(rc2 == 0);

	rc1 = pthread_join(p1, NULL);
	rc2 = pthread_join(p2, NULL);
	assert(rc1 == 0);
	assert(rc2 == 0);
	
	printf("counter - %d\n", counter);
	printf("main end\n");
	return 0;
}	