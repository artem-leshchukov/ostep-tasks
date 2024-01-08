#include <stdio.h>
#include <semaphore.h>

sem_t forks[5];

int left(int p) { return p; }
int right(int p) { return (p + 1) % 5; }

void getforks()
{
	if (p == 4)
	{
		sem_wait(forks[right(p)]);		// here we take firstly right and then left forks (to fix the problem of deadlock)
		sem_wait(forks[left(p)]);
	}
	else
	{
		sem_wait(forks[left(p)]);		// all other philosophers get forks as usual
		sem_wait(forks[right(p)]);
	}
}

void putforks()
{
	sem_post(forks[left(p)]);
	sem_post(forks[right(p)]);
}

int main()
{
	// rough main logic 
	
	while (1)
	{
		think();
		getforks();
		eat();
		putforks();
	}
	
	return 0;
}