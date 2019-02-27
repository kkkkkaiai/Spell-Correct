 ///
 /// @file    Thread.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-26 23:28:52
 ///
 
#include "Thread.h"

using namespace sc;

Thread::Thread()
: _pthid(0)
, _isRunning(false)
{}

void Thread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
	Thread * pthread = static_cast<Thread*>(arg);
	if(pthread)
		pthread->run();

	return NULL;
}

void Thread::join()
{
	pthread_join(_pthid, NULL);
	_isRunning = false;
}

Thread::~Thread()
{
	if(_isRunning)
	{
		pthread_detach(_pthid);
		_isRunning = false;
	}
}
