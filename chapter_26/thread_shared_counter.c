#include <stdio.h>
#include <assert.h>
#include <pthread.h>

static volatile int counter = 0;

void* mythread(void* arg)
{
	printf("Thread %s begin.\n", (char*) arg);
	for (int i = 0; i < 1e7; ++i)
		++counter;
	printf("Thread %s end.\n", (char*) arg);
	return NULL;
}

int main()
{
	pthread_t p1, p2;
	int rc1 = pthread_create(&p1, NULL, mythread, "A");
	int rc2 = pthread_create(&p2, NULL, mythread, "B");
	assert(rc1 == 0);
	assert(rc2 == 0);
	
	rc1 = pthread_join(p1, NULL);
	rc2 = pthread_join(p2, NULL);
	assert(rc1 == 0);
	assert(rc2 == 0);
	
	printf("The counter - %d\n", counter);
	printf("main end\n");
	return 0;
}	