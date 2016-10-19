//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#pragma comment(lib,"libprotobuf.lib") 
#include "IM.Other.pb.h"
#include "eros.h"

Eros::Eros(EventLoop* loop, const InetAddress& serverAddr)
	:loop_(loop),
	client_(loop, serverAddr, "Eros")
{
	client_.setConnectionCallback(std::bind(&Eros::onConnection, this, std::placeholders::_1));
	client_.setMessageCallback(std::bind(&Eros::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}
void Eros::connect() { client_.connect(); }
void Eros::onConnection(const TcpConnectionPtr& conn)
{
	IM::BaseDefine::PBHeader header;
	header.set_version(1);
	header.set_flag(1);
	header.set_moduleid(IM::BaseDefine::ServiceID::SID_OTHER);
	header.set_commandid(IM::BaseDefine::OtherCmdID::CID_OTHER_HEARTBEAT);
	header.set_seqnumber(1);
	header.set_reserved(0);
	header.set_length(header.ByteSize());
	LOG_INFO << header.length();
	LOG_INFO << header.version();
	LOG_INFO << header.flag();
	LOG_INFO << header.moduleid();
	LOG_INFO << header.commandid();
	LOG_INFO << header.seqnumber();
	LOG_INFO << header.reserved();

	conn->send(header.SerializeAsString());
	LOG_INFO <<"SerializeAsString:"<< header.SerializeAsString();
}
void Eros::onMessage(const TcpConnectionPtr& conn, Buffer* buff, Timestamp receiveTime)
{
	LOG_INFO << buff->retrieveAllAsString() << " time:" << receiveTime.toFormattedString();
	//conn->send("world");
	std::this_thread::sleep_for(std::chrono::seconds(3));
}