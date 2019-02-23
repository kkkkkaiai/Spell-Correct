 ///
 /// @file    SocketIO.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 01:39:46
 ///
 
#include "SocketIO.h"
#include "SocketUtility.h"

namespace sc
{

SocketIO::SocketIO(int sockfd)
: _sockfd(sockfd)
{}

size_t SocketIO::readn(char * buf, size_t count)
{
	size_t nleft = count;
	char * tempbuf = buf;
	while(nleft > 0)
	{
		int nread = ::read(_sockfd, tempbuf, nleft);
		if(-1 == nread)
		{
			if(errno == EINTR)//忽略中断信号
				continue;
			return EXIT_FAILURE;
		}
		else if(0 == nread)//EOF
		{
			break;
		}
		tempbuf += nread;
		nleft -= nread;
	}
	return count - nleft;
}

size_t SocketIO::writen(const char * buf, size_t count)
{
	size_t nleft = count;
	const char * tempbuf = buf;
	while(nleft > 0)
	{
		int nwrite = ::write(_sockfd, tempbuf, nleft);
		if(nwrite == -1)
		{
			if(errno == EINTR)
				continue;
			return EXIT_FAILURE;
		}
		nleft -= nwrite;
		tempbuf += nwrite;
	}
	return (count - nleft);
}

size_t SocketIO::recv_peek(char * buf, size_t count)
{
	int nread;
	do
	{
		nread = ::recv(_sockfd, buf, count, MSG_PEEK);
	}while(nread == -1 && errno == EINTR);
	return nread;
}

size_t SocketIO::readline(char *buf, size_t maxlen)
{
	size_t nleft = maxlen -1;
	char * tempbuf = buf;
	size_t total = 0;
	while(nleft > 0)
	{
		int nread = recv_peek(tempbuf, nleft);
		if(nread <= 0)
			return nread;

		for(int idx = 0; idx != nread; ++idx)
		{
			if(tempbuf[idx] == '\n')
			{
				size_t size = idx + 1;
				if(readn(tempbuf, size) != size)
					return EXIT_FAILURE;
				tempbuf += size;
				total += size;
				*tempbuf = 0;
				return total;
			}
		}
		if(readn(tempbuf, nread) != (size_t)nread)
			return EXIT_FAILURE;
		tempbuf += nread;
		nleft -= nread;
		total += nread;
	}
	*tempbuf = 0;
	return maxlen - 1;
}

}
