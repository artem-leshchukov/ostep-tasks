#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct {
	int value;
	pthread_cond_t c;
	pthread_mutex_t m;
} zem_t;				// Zemaphore type

void Zem_Init(zem_t* z, int value)
{
	z->value = value;
	pthread_cond_init(&z->c, NULL);
	pthread_mutex_init(&z->m, NULL);
}

void Zem_Wait(zem_t* z)
{
	pthread_mutex_lock(&z->m);
	--z->value;
	while (z->value < 0)
		pthread_cond_wait(&z->c, &z->m);
	pthread_mutex_unlock(&z->m);
}

void Zem_Post(zem_t* z)
{
	pthread_mutex_lock(&z->m);
	++z->value;
	pthread_cond_signal(&z->c);
	pthread_mutex_unlock(&z->m);
}

int main()
{
	
	return 0;
}