#pragma once

#include "TaskQueue.h"

#include <vector>
#include <memory>

using namespace std;

namespace wd
{

class Task
{
public:
	virtual
	void process() = 0;
	virtual ~Task() {};
};

class Thread;
class WorkThread;

class Threadpool
{
	friend WorkThread;
public:
	Threadpool(size_t threadNum, size_t queSize)
	: _threadNum(threadNum)
	, _queSize(queSize)
	, _taskQue(_queSize)
	, _isExit(false)
	{
		_thread.reserve(_threadNum);
	}

	~ThreadPoll();

	void start();
	void stop();
	void addTask(Task *);

private:
	void ThreadFunc();
	Task * getTask();
private:
	size_t _threadNum;
	size_t _queSize;
	vector<shared_ptr<Thread>> _threads;
	TaskQueue _taskQue;
	bool _isExit;
};

}