#include <stdio.h>
#include <assert.h>
#include <pthread.h>

void init()
{
	flag = 0;
}

void lock()
{
	while (TestAndSet(&flag, 1) == 1)
		yield();		// give up the CPU
}

void unlock()
{
	flag = 0;
}

// ----------	Threads sleeping and waking

typedef struct {
	int flag;
	int guard;
	queue_t* q;
} lock_t;

void lock_init(lock_t* m)
{
	m->flag = 0;
	m->guard = 0;
	queue_init(m->q);
}

void lock(lock_t* m)
{
	while (TestAndSet(&m->guard, 1) == 1)	// if the guard lock is held by some other thread
		;									// actively wait
		
	if (m->flag == 0)						// the lock is not busy
	{
		m->flag = 1;						// take it 
		m->guard = 0;						// set guard to 0 because we made all the things with the lock object
	}
	else
	{
		queue_add(m->q, gettid());
		m->guard = 0;
		park();
	}
}

void unlock(lock_t* m)
{
	while (TestAndSet(&m->guard, 1) == 1)
		;
	
	if (queue_empty(m->q))					// if there is no left awaiting threads
		m->flag = 0;
	else									// otherwise - awake the first of them
		unpark(queue_remove(m->q));
	
	m->guard = 0;
}

// ----------	Linux-like

void mutex_lock(int* mutex)
{
	if (atomic_bit_test_set(mutex, 31) == 0)	// if the 31st bit is 0 (lock is free) - set it to 1 (take the lock)
		return;
	
	atomic_increment(mutex);					// the number of awaiting threads increases
	while (1)
	{
		if (atomic_bit_test_set(mutex, 31) == 0)	// the lock is free
		{
			atomic_decrement(mutex);				// decrement the number of sleeping threads
			return;
		}
		
		int v = *mutex;								// check, maybe the mutex value changed
		if (v >= 0)
			continue;
		
		futex_wait(mutex, v);
	}
}

void mutex_unlock(int* mutex)
{
	if (atomic_add_zero(mutex, 0x8000'0000))	// if 0x8000_0000 + *mutex == 0, then there is no left sleeping threads
		return;
	futex_wake(mutex);
}
