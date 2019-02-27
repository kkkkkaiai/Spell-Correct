 ///
 /// @file    TimerThread.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-27 06:18:41
 ///
 
#include "TimerThread.h"
using namespace sc;

TimerThread::TimerThread(int initialTime, int intervalTime, TimerCallback && cb)
: _timer(initialTime, intervalTime, std::move(cb))
, _subThread(std::bind(&Timer::start, &_timer))
, _isStarted(false)
{}

void TimerThread::start()
{
	_subThread.start();
	_isStarted = true;
}

void TimerThread::stop()
{
	if(_isStarted) {
		_timer.stop();
		_subThread.join();
		_isStarted = false;
	}
}

TimerThread::~TimerThread()
{
	if(_isStarted)
		stop();
}
