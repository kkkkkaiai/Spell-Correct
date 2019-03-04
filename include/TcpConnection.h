 ///
 /// @file    TcpConnection.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 07:49:19
 ///
 
#pragma once

#include "Nocopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>

using std::string;

namespace sc
{
class TcpConnection;
class EventLoop;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

class TcpConnection
: Nocopyable
, public std::enable_shared_from_this<TcpConnection>
{
	friend class QueryTask;
public:
	typedef std::function<void(const TcpConnectionPtr &)> TcpConnectionCallback;
	TcpConnection(int sockfd, EventLoop * loop);
	~TcpConnection();

	std::string receive();
	void send(const string & msg);
	void sendInLoop(const string & msg);
	void shutDown();

	string toString();

	void setConnectionCallback(TcpConnectionCallback cb);
	void setMessageCallback(TcpConnectionCallback cb);
	void setCloseCallback(TcpConnectionCallback cb);

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();
	int getSockfd() { return _sockIO.getFd(); }
	EventLoop* getLoop() { return _loop; }

private:
	Socket _sockfd;
	SocketIO _sockIO;
	const InetAddress _localAddr;
	const InetAddress _peerAddr;
	bool _isShutdownWrite;
	EventLoop * _loop;

	TcpConnectionCallback _onConnectionCB;
	TcpConnectionCallback _onMessageCB;
	TcpConnectionCallback _onCloseCB;
};

}
