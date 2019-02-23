 ///
 /// @file    TimerThread.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 05:39:57
 ///
 
#pragma once

#include "Timer.h"
#include "BO_Thread.h"

#include <functional>

namespace sc
{

class TimerThread
{
public:
	using TimerCallback = std::function<void()>;
	TimerThread(int, int, TimerCallback && cb);

	void start();
	void stop();

	~TimerThread();

private:
	Timer _timer;
	BoThread _subThread;
	bool _isStarted;
};

}
