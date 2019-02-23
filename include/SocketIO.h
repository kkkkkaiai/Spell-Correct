 ///
 /// @file    SocketIO.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 01:34:11
 ///
 
#pragma once

#include <stdio.h>

namespace sc
{

class SocketIO
{
public:
	SocketIO(int sockfd);
	
	size_t readn(char * buf, size_t count);
	size_t writen(const char * buf, size_t count);
	size_t readline(char * buf, size_t max_len);
	int getFd() { return _sockfd; }

private:
	size_t recv_peek(char * buf, size_t count);
private:
	int _sockfd;
};

}
