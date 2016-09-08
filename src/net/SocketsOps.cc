#include <SocketsOps.h>
#include <logging.h>
#include <types.h>
#include <Endian.h>

#include <errno.h>
#include <stdio.h>

#pragma comment( lib, "ws2_32.lib"  )  // for select 
#pragma comment(lib,"ws2_32")
#include <WinSock2.h>

#ifdef _WIN32
#define snprintf	sprintf_s
#endif

using namespace calm;
using namespace calm::net;


namespace
{
	typedef struct sockaddr SA;

	void setNonBlock(int sockfd)
	{
#ifdef _MSC_VER
		u_long nonblock = 1;
		int ret = ioctlsocket(sockfd, FIONBIO, &nonblock);
#else
		int ret = fcntl(fd, F_SETFL, O_NONBLOCK | fcntl(fd, F_GETFL));
#endif
		if (ret == SOCKET_ERROR)
		{
			LOG_ERROR << "set no block error";
		}
	}
	void setNonDelay(int sockfd)
	{
		BOOL nodelay = TRUE;
		int ret = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay));
		if (ret == SOCKET_ERROR)
		{
			LOG_ERROR << "set no delay error";
		}
	}
} // end anonymous namespace

const  struct sockaddr* sockets::sockaddr_cast(const struct sockaddr_in * addr)
{
	return static_cast<const struct sockaddr*>(implicit_cast<const void*>(addr));
}

const struct sockaddr_in* sockets::sockaddr_in_cast(const struct sockaddr * addr)
{
	return static_cast<const struct sockaddr_in*>(implicit_cast<const void*>(addr));
}
struct sockaddr* sockets::sockaddr_cast(struct sockaddr_in * addr)
{
	return static_cast<struct sockaddr*>(implicit_cast<void*>(addr));
}

struct sockaddr_in* sockets::sockaddr_in_cast(struct sockaddr * addr)
{
	return static_cast<struct sockaddr_in*>(implicit_cast<void*>(addr));
}


int sockets::createNoneblockOrDie(int family)
{
	int sockfd = socket(family, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		LOG_SYSFATAL << "sockets::createNoneblockOrDie";
	}
	setNonBlock(sockfd);
	return sockfd;
}

void sockets::bindOrDie(int sockfd, const  sockaddr * addr)
{
	int ret = ::bind(sockfd, addr, sizeof(struct sockaddr));
	if (ret < 0)
	{
		LOG_SYSFATAL << "sockets::bindOrDie";
	}
}
void sockets::listenOrDie(int sockfd)
{
	int ret = listen(sockfd, SOMAXCONN);
	if (ret < 0)
	{
		LOG_SYSFATAL << "sockets::listenOrDie";
	}
}

int sockets::accept(int sockfd, struct sockaddr_in* addr)
{
	socklen_t addrlen = static_cast<socklen_t>(sizeof(*addr));
	int connfd =::accept(sockfd,sockaddr_cast(addr),&addrlen);
	setNonBlock(connfd);
	if (connfd == INVALID_SOCKET)
	{
		errno = WSAGetLastError();
		LOG_FATAL << "error sockets::accept";
	}
	return connfd;
}

int sockets::connect(int socketfd, const struct sockaddr* addr)
{
	return ::connect(socketfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr)));
}

ssize_t sockets::read(int sockfd, void *buf, int count)
{
	return recv(sockfd, static_cast<char*>(buf),count,0);
}

ssize_t sockets::write(int sockfd, const void* buf, int count)
{
	return send(sockfd,static_cast<const char*>(buf), count,0);
}

void sockets::close(int sockfd)
{
	if (::closesocket(sockfd) < 0)
	{
		LOG_SYSERR << "sockets::close";
	}
}

void sockets::shutdownWrite(int sockfd)
{
	if (::shutdown(sockfd, SD_SEND) < 0)
	{
		LOG_SYSERR << "sockets::shutdownWrite";
	}
}
void sockets::toIp(char* buf, size_t size,struct sockaddr* addr)
{
	if (addr->sa_family == AF_INET)
	{
		struct sockaddr_in * addr4 = sockaddr_in_cast(addr);
		::inet_ntop(AF_INET, &addr4->sin_addr, buf, static_cast<socklen_t>(size));
	}
}
void sockets::toIpPort(char* buf, size_t size, struct sockaddr* addr)
{
	toIp(buf, size, addr);
	size_t end = strlen(buf);
	struct sockaddr_in* addr4 = sockaddr_in_cast(addr);
	uint16_t port = sockets::networkToHost16(addr4->sin_port);
	snprintf(buf + end, size - end, ":%u", port);
}

void sockets::fromIpPort(const char* ip, uint16_t port, struct sockaddr_in* addr)
{
	addr->sin_family = AF_INET;
	addr->sin_port = hostToNetwork16(port);
	if (::inet_pton(AF_INET, ip, &addr->sin_addr) <= 0)
	{
		LOG_SYSERR << "sockets::fromIpPort";
	}
}

int sockets::getSockerError(int sockfd)
{
	int optval;
	socklen_t optlen = static_cast<socklen_t>(sizeof(optval));
	if (::getsockopt(sockfd,SOL_SOCKET,SO_ERROR, (char*)&optval,&optlen) < 0)
	{
		return errno;
	}
	else
	{
		return optval;
	}
}
struct sockaddr_in sockets::getLocalAddr(int sockfd)
{
	struct sockaddr_in localaddr;
	memset(&localaddr, 0, sizeof(localaddr));
	socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);
	if(::getsockname(sockfd,sockaddr_cast(&localaddr),&addrlen) < 0)
	{
		LOG_SYSERR << "sockets::getLocalAddr";
	}
	return localaddr;
}
struct sockaddr_in sockets::getPeerAddr(int sockfd)
{
	struct sockaddr_in peeraddr;
	memset(&peeraddr, 0, sizeof(peeraddr));
	socklen_t addrlen = static_cast<socklen_t>(sizeof peeraddr);
	if (::getpeername(sockfd, sockaddr_cast(&peeraddr), &addrlen) < 0)
	{
		LOG_SYSERR << "sockets::getLocalAddr";
	}
	return peeraddr;
}

bool sockets::isSelfConnect(int sockfd)
{
	struct sockaddr_in localaddr = getLocalAddr(sockfd);
	struct sockaddr_in peeraddr = getPeerAddr(sockfd);
	return localaddr.sin_addr.s_addr == peeraddr.sin_addr.s_addr
		&& localaddr.sin_port == peeraddr.sin_port;
}

