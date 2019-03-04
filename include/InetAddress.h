 ///
 /// @file    InetAddress.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-20 03:59:39
 ///
 
#ifndef __SC_INETADDRESS_H__
#define __SC_INETADDRESS_H__

#include <netinet/in.h>
#include <string>

namespace sc
{

class InetAddress
{
public:
	InetAddress(short port);
	InetAddress(const char * pIp, short port);
	InetAddress(const struct sockaddr_in & addr);

	const struct sockaddr_in *getSockAddrPtr() const;
	std::string ip() const;
	unsigned short port() const;

private:
	struct sockaddr_in _addr;
};

}

#endif
