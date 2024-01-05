#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Utils functions

void Pthread_mutex_init(pthread_mutex_t* lock, void* flags)
{
	int r = pthread_mutex_init(lock, flags);
	assert(r == 0);
}

void Pthread_mutex_lock(pthread_mutex_t* lock)
{
	int r = pthread_mutex_lock(lock);
	assert(r == 0);
}

void Pthread_mutex_unlock(pthread_mutex_t* lock)
{
	int r = pthread_mutex_unlock(lock);
	assert(r == 0);
}

// Main logic

typedef struct {
	int value;
	pthread_mutex_t lock;
} counter_t;

void init(counter_t* c)
{
	c->value = 0;
	Pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t* c)
{
	Pthread_mutex_lock(&c->lock);
	++c->value;
	Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t* c)
{
	Pthread_mutex_lock(&c->lock);
	--c->value;
	Pthread_mutex_unlock(&c->lock);
}

int getValue(counter_t* c)
{
	Pthread_mutex_lock(&c->lock);
	int value = c->value;
	Pthread_mutex_unlock(&c->lock);
	return value;
}

int main()
{
	counter_t* c = malloc(sizeof(counter_t));
	init(c);
	
	increment(c);
	increment(c);
	printf("value - %d\n", getValue(c));
	
	decrement(c);
	printf("value - %d\n", getValue(c));
	
	free(c);
	return 0;
}

// Approximate Counter (a Scalable(!) one)
typedef struct {
	int global;							// global counter value
	pthread_mutex_t glock;				// a lock for global counter
	int local[NUMCPU];					// local counter values (one per CPU)
	pthread_mutex_t llock[NUMCPU];		// locks for local counters (one per CPU)
	int threshold;						// update frequency
} counter_t;

void init(counter_t* c, int threshold)
{
	c->threshold = threshold;
	
	c->global = 0;
	pthread_mutex_init(&c->glock, NULL);
	for (int i = 0; i < NUMCPU; ++i)
	{
		c->local[i] = 0;
		pthread_mutex_init(&c->llock[i], NULL);
	}
}

void update(counter_t* c, int threadID, int value)
{
	int cpu = threadID % NUMCPU;
	pthread_mutex_lock(&c->llock[cpu], NULL);
	c->local[cpu] += value;							// add to deal with local counter
	if (c->local[cpu] >= c->threshold)				// if local counter has reached the threshold value
	{												// move this value to the global one
		pthread_mutex_lock(&c->glock, NULL);
		c->global += c->local[cpu];
		pthread_mutex_unlock(&c->glock);
		c->local[cpu] = 0;
	}
	pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t* c)								// get the value from global counter (it may be inaccurate)
{
	pthread_mutex_lock(&c->glock, NULL);
	int val = c->global;
	pthread_mutex_unlock(&c->glock);
	return val;
}

