 ///
 /// @file    EventLoop.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-24 09:01:21
 ///
 
#include "EventLoop.h"
#include "SocketUtility.h"
#include "Acceptor.h"
#include "Mylog.h"

#include <assert.h>
#include <iostream>
using std::cout;
using std::endl;

namespace sc
{

EventLoop::EventLoop(Acceptor & acceptor)
: acceptor(acceptor)
, _epollfd(createEpollFd())
, _eventfd(createEventFd())
, _listenfd(acceptor.fd())
, _isLooping(false)
, _eventsList(1024)
{
	addEpollFdRead(_epollfd, _listenfd);
	addEpollFdRead(_epollfd, _eventfd);
}

EventLoop::~EventLoop()
{
	::close(_epollfd);
}

void EventLoop::loop()
{
	_isLooping = true;
	LogInfo("Loop start");
	while(_isLooping)
		waitEpollfd();
}

void EventLoop::unloop()
{
	if(_isLooping)
		_isLooping = false;
	LogInfo("Loop stop");
}

void EventLoop::setConnectionCallback(EpollCallback cb)
{
	_onConnectionCallback = cb;
}

void EventLoop::setMessageCallback(EpollCallback cb)
{
	_onMessageCallback = cb;
}

void EventLoop::setCloseCallback(EpollCallback cb)
{
	_onCloseCallback = cb;
}

void EventLoop::waitEpollfd()
{
	int nready;
	do
	{
		nready = ::epoll_wait(_epollfd,
							  &(*_eventsList.begin()),
							  _eventsList.size(),
							  5000);
	}while(nready == -1 && errno == EINTR);

	if(nready == -1)
	{
		perror("epoll_wait error");
		exit(EXIT_FAILURE);
	}
	else if(nready == 0)
	{ //Time out 
	}
	else
	{
		//Expansion
		if(nready == static_cast<int>(_eventsList.size()))
		{
			_eventsList.resize(_eventsList.size() * 2);
		}

		for(int idx = 0; idx != nready; ++idx)
		{
			if(_eventsList[idx].data.fd == _listenfd)
			{
				if(_eventsList[idx].events & EPOLLIN)
				{
					handleConnection();
				}
			}
			else if(_eventsList[idx].data.fd == _eventfd)
			{
				handleRead();
				//cout << "> do PendingFunctors()" << endl;
				doPendingFunctors();
			}
			else
			{
				if(_eventsList[idx].events & EPOLLIN)
				{
					handleMessage(_eventsList[idx].data.fd);
				}
			}
		}//end of for
	}//end of if
}

void EventLoop::handleConnection()
{
	int peerfd = acceptor.accept();
	addEpollFdRead(_epollfd, peerfd);

	TcpConnectionPtr conn(new TcpConnection(peerfd, this));
	conn->send("The connection has been established!");
	conn->setConnectionCallback(_onConnectionCallback);
	conn->setMessageCallback(_onMessageCallback);
	conn->setCloseCallback(_onCloseCallback);

	std::pair<ConnectionMap::iterator, bool> ret;
	ret = _connMap.insert(std::make_pair(peerfd, conn));
	assert(ret.second = true);
	(void)ret;

	conn->handleConnectionCallback();
}

void EventLoop::handleMessage(int peerfd)
{
	bool isClosed = isConnectionClosed(peerfd);
	ConnectionMap::iterator it = _connMap.find(peerfd);
	assert(it != _connMap.end());

	if(isClosed)
	{
		it->second->handleCloseCallback();
		delEpollFdRead(_epollfd, peerfd);
		_connMap.erase(it);
	}
	else
	{
		it->second->handleMessageCallback();
	}
}

void EventLoop::runInLoop(const Functor && cb)
{
	{
		MutexLockGuard mutex(_mutex);
		_pendingFunctors.push_back(std::move(cb));
	}
	wakeup();
}

void EventLoop::doPendingFunctors()
{
	std::vector<Functor> temp;

	{
		MutexLockGuard mutex(_mutex);
		temp.swap(_pendingFunctors);
		cout << "Functor size " << temp.size() << endl;
	}
	for(auto & Functor : temp)
	{
		Functor();
	}
	cout << "----------------end------------------" << endl;
}

void EventLoop::handleRead()
{
	uint64_t num;
	int ret = ::read(_eventfd, &num, sizeof(num));
	if(ret != sizeof(num))
	{
		LogError("handleRead error");
		perror("handleread error");
	}
}

void EventLoop::wakeup()
{
	uint64_t one = 1;
	int ret = ::write(_eventfd, &one, sizeof(one));
	if(ret != sizeof(one))
	{
		LogError("wakeup error");
		perror("write error");
	}
}

}
