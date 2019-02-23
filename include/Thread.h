#pragma once

#include "Nocopyable.h"
#include "Mylog.h"

#include <pthread.h>
#include <string>

using std::string;

namespace sc
{

class Thread
: Nocopyable
{
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();

	bool isRunning() const { return _isRunning; };

private:
	virtual void run() = 0;
	static void * threadFunc(void *);

private:
	pthread_t _pthid;
	bool _isRunning;
};

}
