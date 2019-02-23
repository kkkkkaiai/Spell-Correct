 ///
 /// @file    Condition.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 05:07:41
 ///
 
#pragma once

#include "Nocopyable.h"
#include "MutexLock.h"

#include <pthread.h>

namespace sc
{

class Condition
: Nocopyable
{
	public:
	Condition(MutexLock & mutex)
	: _mutex(mutex)
	{ pthread_cond_init(&_cond, NULL); }

	~Condition()
	{ pthread_cond_destroy(&_cond); }

	void wait()
	{ pthread_cond_wait(&_cond, _mutex.getMutexLockPtr()); }

	void notify()
	{ pthread_cond_signal(&_cond); }

	void notifyAll()
	{ pthread_cond_broadcast(&_cond); }

private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};

}
