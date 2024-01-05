#include <stdio.h>
#include <assert.h>
#include <pthread.h>

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;


void* child()
{
	printf("Child\n");
	pthread_mutex_lock(&m);
	done = 1;
	pthread_cond_signal(&c);
	pthread_mutex_unlock(&m);
}

void thr_join()
{
	pthread_mutex_lock(&m);
	while (done == 0)					// if the job is not done yet
		pthread_cond_wait(&c, &m);		// wait until it is
	pthread_mutex_unlock(&m);
}

int main()
{
	printf("Begin main\n");
	pthread_t p1;
	int r = pthread_create(&p1, NULL, child, NULL);
	assert(r == 0);
	thr_join();
	printf("End main\n");
	return 0;
}	