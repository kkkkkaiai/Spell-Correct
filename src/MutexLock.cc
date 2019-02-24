 ///
 /// @file    MutexLock.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-24 05:52:51
 ///
 
#include "MutexLock.h"

#include <iostream>
using std::cout;
using std::endl;

namespace sc
{

MutexLock::MutexLock()
: _isLocking(false)
{
	if(pthread_mutex_init(&_mutex, NULL))
		cout << "error: create mutex failed!" << endl;
}

MutexLock::~MutexLock()
{
	if(pthread_mutex_destroy(&_mutex))
		cout << "error: mutex destroy failed!" << endl;
}

void MutexLock::lock()
{
	pthread_mutex_lock(&_mutex);
	_isLocking = true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLocking = false;
}

pthread_mutex_t * MutexLock::getMutexLockPtr()
{
	return &_mutex;
}

}


