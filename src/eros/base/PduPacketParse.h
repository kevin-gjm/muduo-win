//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#ifndef CALM_EROS_PDUPACKETPARSE_H_
#define CALM_EROS_PDUPACKETPARSE_H_
#include "google/protobuf/message_lite.h"
#include "Callbacks.h"
#include "../eros/base/PBHeader.h"
#include <string>
namespace calm
{
	namespace eros
	{
		class PduPacketParse
		{
		public:
			/**
			* receive pdu
			*/
			virtual void onPacket(PBHeader& header, std::string& pBody) = 0;
			/**
			* send pdu
			*/
			//virtual void sendPacket(CImPdu* pdu) {};
			void sendPacket(calm::net::TcpConnectionPtr& conn, uint16_t moduleId, google::protobuf::MessageLite* pbBody);
			void sendPacket(calm::net::TcpConnectionPtr& conn, uint16_t moduleId, uint16_t cmdId, google::protobuf::MessageLite* pbBody);
			void sendPacket(calm::net::TcpConnectionPtr& conn, uint16_t moduleId, uint16_t cmdId, uint16_t reserved, google::protobuf::MessageLite* pbBody);

			PduPacketParse* getModule(uint16_t moduleId);
		private:
			void _sendPacket(calm::net::TcpConnectionPtr& conn, google::protobuf::MessageLite* pbBody);

			PBHeader header_;
		};
	}// end namespace eros
}// end namespace calm
#endif //CALM_EROS_PDUPACKETPARSE_H_