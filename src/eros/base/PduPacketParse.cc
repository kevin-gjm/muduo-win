#include "PduPacketParse.h"
#include "TcpConnection.h"

using namespace calm;
using namespace calm::net;
using namespace calm::eros;


void PduPacketParse::_sendPacket(calm::net::TcpConnectionPtr& conn, google::protobuf::MessageLite* pbBody)
{
	uint32_t length = calm::eros::HEADER_LENGTH + pbBody->ByteSize();
	header_.setLength(length);
	std::vector<uint8_t> data;
	data.resize(length);
	memset(&data[0], 0, length);
	memcpy(&data[0], header_.getSerializeBuffer(), calm::eros::HEADER_LENGTH);
	if (!pbBody->SerializeToArray(&data[0] + calm::eros::HEADER_LENGTH, pbBody->ByteSize()))
	{
		//LOG__(ERR, _T("pbBody SerializeToArray failed"));
		return;
	}
	conn->send(&data[0], length);
}
void PduPacketParse::sendPacket(calm::net::TcpConnectionPtr& conn, uint16_t moduleId, google::protobuf::MessageLite* pbBody)
{
	header_.clear();
	header_.setModuleId(moduleId);
	_sendPacket(conn, pbBody);
}
void PduPacketParse::sendPacket(calm::net::TcpConnectionPtr& conn, uint16_t moduleId, uint16_t cmdId, google::protobuf::MessageLite* pbBody)
{
	header_.clear();
	header_.setModuleId(moduleId);
	header_.setCommandId(cmdId);
	_sendPacket(conn, pbBody);
}
void PduPacketParse::sendPacket(calm::net::TcpConnectionPtr& conn, uint16_t moduleId, uint16_t cmdId, uint16_t reserved, google::protobuf::MessageLite* pbBody)
{
	header_.clear();
	header_.setModuleId(moduleId);
	header_.setCommandId(cmdId);
	header_.setReserved(reserved);
	_sendPacket(conn, pbBody);
}