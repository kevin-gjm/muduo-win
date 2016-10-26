#pragma comment(lib,"libprotobuf.lib") 
#include "IM.Other.pb.h"

#include "eros_server.h"
#include "../eros/base/PBHeader.h"
#include "../eros/base/PduPacketParse.h"


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
	
	//if (buf->readableBytes() >= calm::eros::HEADER_LENGTH)
	//{
	//	header.unSerialize(buf);
	//}
	//LOG_INFO << header.getLength();
	//LOG_INFO << header.getFlag();
	//LOG_INFO << header.getModuleId();
	//LOG_INFO << header.getCommandId();
	//LOG_INFO << header.getSeqNumber();
	//LOG_INFO << header.getReserved();
	if (buf->readableBytes() < 4)
		return;
	uint32_t length = buf->peekInt32();
	if (buf->readableBytes() < length)
		return;
	calm::eros::PBHeader header;
	header.unSerialize(buf); // get and retrieve the header size
	calm::eros::PduPacketParse * Parse = calm::eros::PduPacketParse::getModule(header.getModuleId());
	Parse->onPacket(header, buf->retrieveAsString(length - calm::eros::HEADER_LENGTH));
}