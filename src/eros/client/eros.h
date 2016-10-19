//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#ifndef CALM_EROS_CLIENT_H_
#define CALM_EROS_CLIENT_H_
#include "EventLoop.h"
#include "logging.h"
#include "TcpClient.h"
#include "InetAddress.h"
#include "uncopyable.h"

#include <functional>


using namespace calm;
using namespace calm::net;

class Eros:calm::uncopyable
{
public:
	Eros(EventLoop* loop, const InetAddress& serverAddr);
	void connect();
private:
	EventLoop* loop_;
	TcpClient client_;
	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn, Buffer* buff, Timestamp receiveTime);
};// end class Eros

#endif //CALM_EROS_CLIENT_H_ 