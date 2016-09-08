#ifndef CALM_NET_INETADDRESS_H_
#define CALM_NET_INETADDRESS_H_
#include "copyable.h"
#include "stringpiece.h"
#include "SocketsOps.h"

namespace calm
{
	namespace net
	{
		class InetAddress :public calm::copyable
		{
		public:
			// mostly used in tcp server listening
			explicit InetAddress(uint16_t port = 0, bool loopbackOnly = false);
			InetAddress(StringArg ip, uint16_t port);
			explicit InetAddress(const struct sockaddr_in& addr)
				:addr_(addr)
			{}
			void setSockAddrIn(const struct sockaddr_in& addr) { addr_ = addr; }
			ADDRESS_FAMILY family()const { return addr_.sin_family; }
			string toIp() const;
			string toIpPort() const;
			uint16_t toPort() const;
			const struct sockaddr* getSockaddr() const  { return sockets::sockaddr_cast(&addr_); }

			uint32_t ipNetEndian() const;
			uint16_t portNetEndian() const { return addr_.sin_port; };
		private:
			struct sockaddr_in addr_;
		};
	}//end namespace net
}// end namespace calm

#endif //CALM_NET_INETADDRESS_H_