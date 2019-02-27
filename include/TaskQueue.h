 ///
 /// @file    TaskQueue.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-26 23:37:38
 ///
 
#pragma once
#include "MutexLock.h"
#include "Condition.h"
 
#include <queue>
using namespace sc;

class Task;

class TaskQueue
{
public:
	TaskQueue(size_t queSize)
	: _queSize(queSize)
	, _mutex()
	, _notFull(_mutex)
	, _notEmpty(_mutex)
	, _flag(true)
	{}

	void push(Task*);
	Task * pop();

	bool empty() const
	{	return _que.size() == 0; }

	bool full() const
	{	return _que.size() == _queSize; }

	void wakeup() {
		_flag = false;
		_notEmpty.notifyAll();
	}

private:
	size_t _queSize;
	std::queue<Task *> _que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	bool _flag;
};
