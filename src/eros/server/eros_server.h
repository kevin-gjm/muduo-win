//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#ifndef CALM_EROS_SERVER_H_
#define CALM_EROS_SERVER_H_

#include "EventLoop.h"
#include "logging.h"
#include "TcpServer.h"
#include "InetAddress.h"
#include "uncopyable.h"

#include <functional>

using namespace calm;
using namespace calm::net;

class ErosServer:calm::uncopyable
{
public:
	ErosServer(EventLoop* loop,const InetAddress& listenAddr);
	void start() { server_.start(); }
private:
	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);
	TcpServer server_;
};// end class ErosServer

#endif //CALM_EROS_SERVER_H_