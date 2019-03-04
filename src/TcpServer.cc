 ///
 /// @file    TcpServer.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-27 06:28:00
 ///
 
#include "TcpServer.h"
#include "SocketUtility.h"

#include <iostream>
using std::cout;
using std::endl;
using namespace sc;

TcpServer::TcpServer(const string & ip, unsigned short port)
: _acceptor(createSocketFd(), InetAddress(ip.data(), port))
, _poller(_acceptor)
{}

void TcpServer::start()
{
	_acceptor.ready();
	_poller.setConnectionCallback(_connectionCallback);
	_poller.setMessageCallback(_messageCallback);
	_poller.setCloseCallback(_closeCallback);
	_poller.loop();
}

void TcpServer::stop()
{
	_poller.unloop();
}

void TcpServer::setConnectionCallback(TcpServerCallback cb)
{	_connectionCallback = cb;	}

void TcpServer::setMessageCallback(TcpServerCallback cb)
{	_messageCallback = cb;	}

void TcpServer::setCloseCallback(TcpServerCallback cb)
{	_closeCallback = cb;	}

