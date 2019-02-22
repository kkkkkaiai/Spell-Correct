 ///
 /// @file    InetAddress.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-20 04:06:46
 ///
 
#include "InetAddress.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


namespace sc
{

InetAddress::InetAddress(short port)
{
	::memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const char *pIp, short port)
{
	::memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(pIp);
	//inet_addr convert the Internet host address for dotted-decimal into binary data
}

const struct sockaddr_in * InetAddress::getSockAddrPtr() const
{
	return &_addr;
}

std::string InetAddress::ip() const
{
	return std::string(inet_ntoa(_addr.sin_addr));
	//inet_ntoa convert host adress to IPv4 dotted-decimal notation
}

unsigned short InetAddress::port() const		
{
	return ntohs(_addr.sin_port);
	//ntohs convert the port from network byte order to host byte order
	//from big-endian to littel-endian(normally condition)
}

}

