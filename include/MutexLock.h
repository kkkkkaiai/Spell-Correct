 ///
 /// @file    MutexLock.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-20 03:33:01
 ///
 
#ifndef __SC_MUTEXLOCK_H__
#define __SC_MUTEXLOCK_H__

#include "Nocopyable.cc"
#include <pthread.h>

namespace sc
{

class MutexLock
: Nocopyable
{
public:
	MutexLock();
	~MutexLock();
	void lock();
	void unlock();

	bool isLocking() const;
	pthread_mutex_t * getMutexLockPtr();

private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};

class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}

private:
	MutexLock & _mutex;
};

}
#endif
