 ///
 /// @file    TcpServer.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-24 03:47:43
 ///
 
#include "Acceptor.h"
#include "EventLoop.h"
#include "Mylog.h"

#include<string>

using std::string;

namespace sc
{

class TcpServer
{
public:
	using TcpServerCallback = EventLoop::EpollCallback;
	TcpServer(const string & ip, unsigned short port);
	TcpServer(unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback);
	void setMessageCallback(TcpServerCallback);
	void setCloseCallback(TcpServerCallback);


private:
	Acceptor _acceptor;
	EventLoop _poller;

	TcpServerCallback _connectionCallback;
	TcpServerCallback _messageCallback;
	TcpServerCallback _closeCallback;

};

}
