 ///
 /// @file    Timer.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 00:34:22
 ///
 
#pragma once

#include <functional>
using std::function;

namespace sc
{

class Timer
{

public:
	using TimerCallback = std::function<void()>;

	Timer(int initialTime, int intervalTime, TimerCallback && cb);
	~Timer();

	void start();
	void stop();

private:
	int createTimerFd();
	void setTimerfd(int initialTime, int intervalTime);
	void handleRead();

private:
	int _fd;
	int _initialTime;
	int _intervalTime;
	TimerCallback _cb;
	bool _isStarted;
};

}
