 ///
 /// @file    BO_Thread.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 00:25:27
 ///

#pragma once
 
#include "Nocopyable.h"

#include <pthread.h>
#include <functional>
using std::function;

namespace sc
{

class BoThread
: Nocopyable
{
	using boThreadCallback = function<void()>;
public:
	BoThread(boThreadCallback && cb);
	~BoThread();

	void start();
	void join();

	bool isRunning() const { return _isRunning; }

private:
	static void * threadFunc(void *);

private:
	pthread_t _pthid;
	bool _isRunning;
	boThreadCallback _cb;
};

}
