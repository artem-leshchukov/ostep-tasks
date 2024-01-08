#include <semaphore.h>

typedef struct {
	sem_t lock;				// lock to deal with many readers (with int variable)
	sem_t writelock;		// lock for the accessability to write (if no readers, then we can acquire it)
	int readers;
} rwlock_t;

void rwlock_acquire_writelock(rwlock_t* rw)
{
	sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t* rw)
{
	sem_post(&rw->writelock);
}

void rwlock_acquire_readlock(rwlock_t* rw)
{
	sem_wait(&rw->lock);
	++rw->readers;
	if (rw->readers == 1)
		sem_wait(&rw->writelock);		// acquire writelock so that no writer would be able to write to data structure
	sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t* rw)
{
	sem_wait(&rw->lock);
	--rw->readers;
	if (rw->readers == 0)
		sem_post(&rw->writelock);		// now there is no readers left, so it's possible to change data structure for writer
	sem_post(&rw->lock);
}

int main()
{
	return 0;
}