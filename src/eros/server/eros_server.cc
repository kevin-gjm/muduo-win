#pragma comment(lib,"libprotobuf.lib") 
#include "IM.Other.pb.h"
#include "eros_server.h"

ErosServer::ErosServer(EventLoop* loop,const InetAddress& listenAddr)
	:server_(loop,listenAddr,"ErosServer")
{
	server_.setConnectionCallback(std::bind(&ErosServer::onConnection, this, std::placeholders::_1));
	server_.setMessageCallback(std::bind(&ErosServer::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
}

void ErosServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "new connection from local: " << conn->localAddress().toIpPort() << " peer: " << conn->peerAddress().toIpPort();
	//conn->send("hello client");
}
void ErosServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
	LOG_INFO << "time:" << time.toFormattedString();
	LOG_INFO<<" get msg:" << buf->allToStringPiece();
	IM::BaseDefine::PBHeader header;
	//if (buf->readableBytes() >= 28)
	{
		header.ParseFromString(buf->retrieveAllAsString());
	}
	LOG_INFO << header.length();
	LOG_INFO << header.version();
	LOG_INFO << header.flag();
	LOG_INFO << header.moduleid();
	LOG_INFO << header.commandid();
	LOG_INFO << header.seqnumber();
	LOG_INFO << header.reserved();
}