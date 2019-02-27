 ///
 /// @file    Timer.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-27 00:45:58
 ///
 
#include "Timer.h"
#include "Mylog.h"
#include "EventLoop.h"

#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <sys/timerfd.h>

#include <iostream>
using namespace std;

namespace sc
{

Timer::Timer(int initialTime, int intervalTime, TimerCallback && cb)
: _fd(createTimerFd())
, _initialTime(initialTime)
, _intervalTime(intervalTime)
, _cb(std::move(cb))
, _isStarted(false)
{}

void Timer::start()
{
	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	setTimerfd(_initialTime, _intervalTime);

	_isStarted = true;
	while(_isStarted){
		int nready = ::poll(&pfd, 1, 5000);
		if(nready == -1 && errno == EINTR){
			continue;
		} else if (nready == -1){
			LogError("timer poll error");
			perror(">>> poll error");
			exit(EXIT_FAILURE);
		} else if(nready == 0){
			//timeout
		} else {
			if(pfd.revents & POLLIN) {
				handleRead();				
				if(_cb)
					_cb();
			}
		}
	}
}

void Timer::stop()
{
	setTimerfd(0, 0);
	if(_isStarted)
		_isStarted = false;
}

Timer::~Timer()
{
	if(_isStarted)
		stop();
}


int Timer::createTimerFd()
{
	int fd = ::timerfd_create(CLOCK_REALTIME,0);
	if(fd == -1) {
		perror(">> timerfd_create error");
	}
	return fd;
}


void Timer::setTimerfd(int initialTime, int intervalTime)
{
	struct itimerspec value;
	value.it_value.tv_sec = initialTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = intervalTime;
	value.it_interval.tv_nsec = 0;
	int ret = ::timerfd_settime(_fd, 0, &value, NULL);
	if(ret == -1) {
		perror(">>> timerfd_settime error");
	}
}

void Timer::handleRead()
{
	uint64_t num;
	int ret = ::read(_fd, &num, sizeof(uint64_t));
	if(ret != sizeof(uint64_t)) {
		perror(">>> read error");
	}
}


}
