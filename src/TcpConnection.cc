 ///
 /// @file    TcpConnection.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-24 04:09:19
 ///
 
#include "TcpConnection.h"
#include "EventLoop.h"
#include <string.h>
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;


namespace sc
{

TcpConnection::TcpConnection(int sockfd, EventLoop * loop)
: _sockfd(sockfd)
, _sockIO(sockfd)
, _localAddr(Socket::getLocalAddr(sockfd))
, _peerAddr(Socket::getPeerAddr(sockfd))
, _isShutdownWrite(false)
, _loop(loop)
{
	_sockfd.nonblock();
}

TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite){
		_isShutdownWrite = true;
	}
	cout << "~TcpConnection" << endl;
}

string TcpConnection::receive()
{
	char buf[65536];
	memset(buf, 0, sizeof(buf));
	size_t ret = _sockIO.readline(buf, sizeof(buf));
	if(ret == 0)
		return string();
	else
		return string(buf);
}

void TcpConnection::send(const string & msg)
{
	_sockIO.writen(msg.c_str(), msg.size());
	string logwarn = "Message sent through socket: " + std::to_string(_sockIO.getFd());
	LogWarn(logwarn);
	cout << "sockfd = " << _sockIO.getFd() << endl;
}

void TcpConnection::shutDown()
{
	if(!_isShutdownWrite)
		_sockfd.shutdownWrite();
	_isShutdownWrite = true;
}

string TcpConnection::toString()
{
	char str[100];
	//格式化输出字符
	snprintf(str, sizeof(str), "%s:%d -> %s:%d",
			 _localAddr.ip().c_str(),
			 _localAddr.port(),
			 _peerAddr.ip().c_str(),
			 _peerAddr.port());
	return string(str);
}

void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	_onConnectionCB = cb;
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	_onMessageCB = cb;
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb)
{
	_onCloseCB = cb;
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnectionCB)
		_onConnectionCB(shared_from_this());
}

void TcpConnection::handleMessageCallback()
{
	if(_onMessageCB)
		_onMessageCB(shared_from_this());
}

void TcpConnection::handleCloseCallback()
{
	if(_onCloseCB)
		_onCloseCB(shared_from_this());
}

void TcpConnection::sendInLoop(const string & msg)
{
	_loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
}


}
