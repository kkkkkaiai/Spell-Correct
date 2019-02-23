#pragma once

#include "Thread.h"
#include <iostream>
using  namespace std;

namespace sc
{

class Threadpool;

class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool & threadpool)
	: _threadpool(threadpool)
	{
		LogWarn("New WorkerThread was created.");
		cout << "WorkerThread()" << endl;
	}

	~WorkerThread() { cout << "~WorkerThread()" << endl; }

private:
	void run();
	Threadpool & _threadpool;
};


}
