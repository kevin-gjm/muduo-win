//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
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
	Eros(EventLoop* loop,const InetAddress& serverAddr)
		:loop_(loop),
		client_(loop,serverAddr,"Eros")
	{
		client_.setConnectionCallback(std::bind(&Eros::onConnection, this, std::placeholders::_1));
		client_.setMessageCallback(std::bind(&Eros::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}
	void connect()
	{
		client_.connect();
	}
private:
	EventLoop* loop_;
	TcpClient client_;
	void onConnection(const TcpConnectionPtr& conn)
	{
		conn->send("hello");
	}
	void onMessage(const TcpConnectionPtr& conn, Buffer* buff, Timestamp receiveTime)
	{
		LOG_INFO << buff->allToStringPiece() << " time:" << receiveTime.toFormattedString();
		conn->send("world");
		buff->retrieveAll();
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}

};// end class Eros