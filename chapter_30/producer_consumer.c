#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#define MAX 1024

int buffer[MAX];
int tail_ptr = 0;
int head_ptr = 0;
int count = 0;

void put(int value)
{
	buffer[tail_ptr] = value;
	tail_ptr = (tail_ptr + 1) % MAX;
	++count;
}

int get()
{
	int tmp = buffer[head_ptr];
	head_ptr = (head_ptr + 1) % MAX;
	--count;
	return tmp;
}

// Case 1:
int loops;
pthread_cond_t fill, empty;
pthread_mutex_t m;

void* producer()
{
	for (int i = 0; i < loops; ++i)
	{
		pthread_mutex_lock(&m);
		while (count == MAX)
			pthread_cond_wait(&empty, &m);
		put(i);
		pthread_cond_signal(&fill);
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

void* consumer()
{
	int tmp;
	for (int i = 0; i < loops; ++i)
	{
		pthread_mutex_lock(&m);
		while (count == 0)
			pthread_cond_wait(&fill, &m);
		tmp = get();
		pthread_cond_signal(&empty);		// we wake up the thread but another thread does not begin to work (it's just ready to get started)
		pthread_mutex_unlock(&m);
		printf("%d\n", tmp);
	}
	return NULL;
}

int main()
{
	return 0;
}	