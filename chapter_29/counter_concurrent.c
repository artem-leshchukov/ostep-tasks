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