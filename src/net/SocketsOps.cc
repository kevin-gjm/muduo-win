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
			//LOG__(NET, _T("_SetNonblock failed, err_code=%d"), _GetErrorCode());
		}
	}
} //



