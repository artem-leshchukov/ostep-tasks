#include <stdio.h>
#include <assert.h>
#include <pthread.h>

typedef struct {
	int flag;
} lock_t;

void init(lock_t* mutex)
{
	mutex->flag = 0;	// 0 - the lock is empty
}

void lock(lock_t* mutex)
{
	while (mutex->flag == 1)	// the lock is busy
		;						// actively wait until it gets free
	mutex->flag = 1;
}

void unlock(lock_t* mutex)
{
	mutex->flag = 0;
}

// ---------- ( Hardware primitives below )

int TestAndSet(int* old_ptr, int new)		// atomic operation (by being atomic we guarantee that lock is held by only one thread)
{											// returns an old value and sets a new one
	int old = *old_ptr;
	*old_ptr = new;
	return old;
}

void lock(lock_t* mutex)
{
	while (TestAndSet(&mutex->flag, 1) == 1)
		;
}

// ----------

int CompareAndSwap(int* ptr, int expected, int new)	// atomic operation as well
{
	int actual = *ptr;
	if (actual == expected)
		*ptr = new;
	return actual;
}

void lock(lock_t* mutex)
{
	while (CompareAndSwap(&mutex->flag, 0, 1) == 1)
		;
}

// ----------

int LoadLinked(int* ptr)
{
	return *ptr;
}

int StoreConditional(int* ptr, int value)
{
	if ( /* no changed were made in *ptr since the last LoadLinked() call */ )
	{
		*ptr = value;
		return 1;
	}
	return 0;
}

void lock(lock_t* mutex)
{
	while (1)
	{
		while (LoadLinked(&mutex->flag) == 1)	// wait until the lock frees
			;
			
		if (StoreConditional(&mutex->flag, 1) == 1)	// if value at &mutex->flag changed then some other thread got the lock, if not - we get it
			return;
	}
}

// ----------
