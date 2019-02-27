 ///
 /// @file    Acceptor.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-26 23:07:38
 ///
 
#include "Acceptor.h"
#include "SocketUtility.h"
#include "Mylog.h"


using namespace sc;

Acceptor::Acceptor(int listenfd, const InetAddress & addr)
: _listenSock(listenfd)
, _addr(addr)
{}

void Acceptor::ready()
{
	setReuseAddr(true);
	setReusePort(true);
	bind();
	listen();
}

int Acceptor::accept()
{
	int peerfd = ::accept(_listenSock.fd(), NULL, NULL);
	if(peerfd == -1)
	{
		perror("acceptr error");
	}
	return peerfd;
}

void Acceptor::setReuseAddr(bool flag)
{
	int on = (flag ? 1 : 0);
	if(::setsockopt(_listenSock.fd(),
					SOL_SOCKET,
					SO_REUSEADDR,
					&on,
					static_cast<socklen_t>(sizeof(on))) == -1)
	{
		LogError("setReuseAddr error");
		perror("setsockopt reuseaddr error");
		::close(_listenSock.fd());
		exit(EXIT_FAILURE);
	}
}

void Acceptor::setReusePort(bool flag)
{
#ifndef SO_REUSEPORT
	int on = (flag ? 1 : 0);
	if(::setsockopt(_listenSock.fd(),
					SOL_SOCKET,
					SO_REUSEPORT,
					&on,
					static_cast<socklen_t>(sizeof(on))) == -1)
	{
		LogError("setReusePort error");
		perror("setsockopt reuseport error");
		::close(_listenSock.fd());
		exit(EXIT_FAILURE);
	}
#endif
}

void Acceptor::bind()
{
	if(-1 == ::bind(_listenSock.fd(),
				   (const struct sockaddr*)_addr.getSockAddrPtr(),
				   sizeof(InetAddress)))
	{
		LogError("bind error");
		::close(_listenSock.fd());
		exit(EXIT_FAILURE);
	}
}

void Acceptor::listen()
{
	if(-1 == ::listen(_listenSock.fd(), 10))
	{
		LogError("listen Error");
		perror("listen error");
		::close(_listenSock.fd());
		exit(EXIT_FAILURE);
	}
}
