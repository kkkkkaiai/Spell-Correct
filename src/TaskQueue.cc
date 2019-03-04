 ///
 /// @file    TaskQueue.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-04 01:19:54
 ///
 
#include "TaskQueue.h"

using namespace sc;

void TaskQueue::push(Task * t)
{
	MutexLockGuard autoLock(_mutex);

	while(full())
	{
		_notFull.wait();
	}

	_que.push(t);
	_notEmpty.notify();
}

Task* TaskQueue::pop()
{
	MutexLockGuard autoLock(_mutex);
	while(_flag && empty())
	{
		_notEmpty.wait();
	}

	if(_flag)
	{
		Task *t = _que.front();
		_que.pop();
		_notFull.notify();
		return t;
	} else
		return NULL;
}


