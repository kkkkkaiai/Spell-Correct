 ///
 /// @file    SocketUtility.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-20 05:17:17
 ///

#ifndef __SC_SOCKETUTILITY_H__
#define __SC_SOCKETUTILITY_H__

#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>



namespace sc
{

inline int createSocketFd()
{
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1){
		perror("socket create error!");
	}
	return fd;
}

inline void serNonblock(int fd)
{
	int flags = ::fcntl(fd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	::fcntl(fd, F_SETFL, flags);
}

inline int createEpollFd()
{
	int efd = ::epoll_create1(0);
	if(-1 == efd)
	{
		perror("epoll_create1 error!");
		exit(EXIT_FAILURE);
	}
	return efd;
}

inline int createEventFd()
{
	int eventfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	if(-1 == eventfd)
	{
		perror("eventfd create error");
	}
	return eventfd;
}

inline void addEpollFdRead(int efd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);
	if(-1 == ret)
	{
		perror("epoll_ctl add error!");
		exit(EXIT_FAILURE);
	}
}

inline void delEpollFdRead(int efd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	int ret = epoll_ctl(efd, EPOLL_CTL_DEL, fd, &ev);
	if(-1 == ret)
	{
		perror("epoll_ctl del error");
		exit(EXIT_FAILURE);
	}
}

inline size_t recvPeek(int sockfd, void * buf, size_t len)
{
	int nread;
	do
	{
		nread = ::recv(sockfd, buf, len, MSG_PEEK);
	}while(nread == -1 && errno == EINTR);//EINTR interrupted function call
	return nread;
}

//check the conn's condition is closed
inline bool isConnectionClosed(int sockfd)
{
	char buf[1024];
	int nread = recvPeek(sockfd, buf, sizeof(buf));
	if(-1 == nread)
	{
		perror("recvPeek -----");
		return true;
	}
	return (0 == nread);
}

}
#endif
