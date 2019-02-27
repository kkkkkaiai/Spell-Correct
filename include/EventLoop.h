 ///
 /// @file    EventLoop.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-24 03:06:38
 ///
 
#pragma once

#include "Nocopyable.h"
#include "TcpConnection.h"
#include "MutexLock.h"

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>
using std::vector;
using std::function;
using std::map;

namespace sc
{

class Acceptor;
class EventLoop
: Nocopyable
{
public:
	typedef TcpConnection::TcpConnectionCallback EpollCallback;
	typedef function<void()> Functor;

	EventLoop(Acceptor & acceptor);
	~EventLoop();

	void loop();
	void unloop();
	void runInLoop(const Functor &&);
	void doPendingFunctors();
	void wakeup();
	
	void setConnectionCallback(EpollCallback);
	void setMessageCallback(EpollCallback);
	void setCloseCallback(EpollCallback);

private:
	void waitEpollfd();
	void handleConnection();
	void handleMessage(int peerfd);
	void handleRead();

private:
	Acceptor & acceptor;
	MutexLock _mutex;

	int _epollfd;
	int _eventfd;
	int _listenfd;
	bool _isLooping;

	typedef map<int, TcpConnectionPtr> ConnectionMap;
	ConnectionMap _connMap;

	vector<Functor> _pendingFunctors;
	typedef vector<struct epoll_event> EventList;
	EventList _eventsList;

	EpollCallback _onConnectionCallback;
	EpollCallback _onMessageCallback;
	EpollCallback _onCloseCallback;
};

}
