#ifndef CALM_NET_SOCKETSOPS_H_
#define CALM_NET_SOCKETSOPS_H_

#include <stdint.h>
#include <stdio.h>

#ifdef _MSC_VER
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
// sockets
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#endif // _MSC_VER
namespace calm
{
	namespace net
	{
		namespace sockets
		{
			int createNoneblockOrDie(int family);
			int createOrDie(int family);
			int connect(int socketfd, const struct sockaddr* addr);
			void bindOrDie(int sockfd, const struct sockaddr* addr);
			void listenOrDie(int sockfd);
			
			int accept(int sockfd, struct sockaddr_in* addr);

			ssize_t read(int sockfd, void *buf, int count);
			ssize_t write(int sockfd, const void* buf, int count);

			void close(int sockfd);
			void shutdownWrite(int sockfd);
			void toIpPort(char* buf, size_t size,const struct sockaddr* addr);
			void toIp(char* buf, size_t size, const struct sockaddr* addr);

			void fromIpPort(const char* ip, uint16_t port, struct sockaddr_in* addr);

			int getSockerError(int sockfd);

			const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr) ;
			const struct sockaddr_in* sockaddr_in_cast(const struct sockaddr* addr) ;
			struct sockaddr* sockaddr_cast(struct sockaddr_in* addr);
			struct sockaddr_in* sockaddr_in_cast(struct sockaddr* addr);

			struct sockaddr_in getLocalAddr(int sockfd);
			struct sockaddr_in getPeerAddr(int sockfd);

			bool isSelfConnect(int sockfd);
		}// end namespace sockets
	}// end namespace net
}// end namespace calm

#endif //CALM_NET_SOCKETSOPS_H_