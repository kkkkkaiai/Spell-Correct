 ///
 /// @file    BO_Thread.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-26 22:01:28
 ///
 

#include "BO_Thread.h"
#include <iostream>

using std::cout;
using std::endl;
using namespace sc;

BoThread::BoThread(boThreadCallback &&cb)
: _pthid(0)
, _isRunning(false)
, _cb(std::move(cb))
{
	cout << "BoThread(cb)" << endl;
}

void BoThread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);
	_isRunning = true;
}

void * BoThread::threadFunc(void * arg)
{
	BoThread * pthread = static_cast<BoThread*>(arg);
	if(pthread)
		pthread->_cb();
	return NULL;
}

void BoThread::join()
{
	pthread_join(_pthid, NULL);
	_isRunning = false;
}

BoThread::~BoThread()
{
	if(_isRunning)
	{
		pthread_detach(_pthid);
		_isRunning = false;
	}
	cout << "~BoThread()" << endl;
}
