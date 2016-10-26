#include "PduPacketParse.h"
#include "TcpConnection.h"

using namespace calm;
using namespace calm::net;
using namespace calm::eros;


void PduPacketParse::_sendPacket(const calm::net::TcpConnectionPtr& conn,PBHeader& header, google::protobuf::MessageLite* pbBody)
{
	uint32_t length = calm::eros::HEADER_LENGTH + pbBody->ByteSize();
	header.setLength(length);
	std::vector<uint8_t> data;
	data.resize(length);
	memset(&data[0], 0, length);
	memcpy(&data[0], header.getSerializeBuffer(), calm::eros::HEADER_LENGTH);
	if (!pbBody->SerializeToArray(&data[0] + calm::eros::HEADER_LENGTH, pbBody->ByteSize()))
	{
		//LOG__(ERR, _T("pbBody SerializeToArray failed"));
		return;
	}
	conn->send(&data[0], length);
}
void PduPacketParse::sendPacket(const calm::net::TcpConnectionPtr& conn, uint16_t moduleId, google::protobuf::MessageLite* pbBody)
{
	PBHeader header;
	header.clear();
	header.setModuleId(moduleId);
	_sendPacket(conn, header, pbBody);
}
void PduPacketParse::sendPacket(const calm::net::TcpConnectionPtr& conn, uint16_t moduleId, uint16_t cmdId, google::protobuf::MessageLite* pbBody)
{
	PBHeader header;
	header.clear();
	header.setModuleId(moduleId);
	header.setCommandId(cmdId);
	_sendPacket(conn, header, pbBody);
}
void PduPacketParse::sendPacket(const calm::net::TcpConnectionPtr& conn, uint16_t moduleId, uint16_t cmdId, uint16_t reserved, google::protobuf::MessageLite* pbBody)
{
	PBHeader header;
	header.clear();
	header.setModuleId(moduleId);
	header.setCommandId(cmdId);
	header.setReserved(reserved);
	_sendPacket(conn, header, pbBody);
}