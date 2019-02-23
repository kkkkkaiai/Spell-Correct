 ///
 /// @file    Acceptor.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 07:30:30
 ///
 
#pragma once

#include "Socket.h"
#include "InetAddress.h"

namespace sc
{

class Acceptor
{
public:
	Acceptor(int listenfd, const InetAddress & addr);

	void ready();
	int accept();

	int fd() const { return _listenSock.fd(); }

private:
	void setReuseAddr(bool on);
	void setReusePort(bool on);
	void bind();
	void listen();

private:
	Socket _listenSock;
	InetAddress _addr;
};

}
