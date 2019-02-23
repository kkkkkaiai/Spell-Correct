 ///
 /// @file    Socket.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-20 03:51:33
 ///
 
#ifndef __SC_SOCKET_H__
#define __SC_SOCKET_H__

#include "Nocopyable.h"

namespace sc
{

class InetAddress;

class Socket
: Nocopyable
{
public:
	Socket(int sockfd);
	Socket();
	~Socket();

	void shutdownWrite();
	int fd() const { return _sockfd; }

	void nonblock();

	static InetAddress getLockAddr(int sockfd);
	static InetAddress getPeerAddr(int sockfd);
private:
	int _sockfd;
};

}
#endif
