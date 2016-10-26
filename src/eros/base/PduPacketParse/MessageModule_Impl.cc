#include "IM.Message.pb.h"
#include "logging.h"
#include "../eros/base/PBHeader.h"
#include "MessageModule_Impl.h"


using namespace calm;
using namespace calm::eros;

namespace calm
{
	namespace eros
	{
		PduPacketParse* getMessageModule()
		{
			static MessageMoudle_Impl module;
			return &module;
		}
	}
}

void MessageMoudle_Impl::onPacket(PBHeader& header, std::string& pBody)
{
	switch (header.getCommandId())
	{
	case IM::BaseDefine::MessageCmdID::CID_MSG_DATA :
		_messageData(pBody);
		break;
	default:
		return;
	}
}

void MessageMoudle_Impl::_messageData(std::string& pbBody)
{
	IM::Message::IMMsgData imMsgData;
	if (!imMsgData.ParseFromString(pbBody))
	{
		LOG_ERROR << "ParseFromString failed : " << pbBody;
		return;
	}
	LOG_INFO <<(int32_t) imMsgData.from_user_id();
	LOG_INFO <<(int32_t) imMsgData.to_session_id();
	LOG_INFO <<(int32_t) imMsgData.msg_id();
	LOG_INFO <<(int32_t) imMsgData.create_time();
	LOG_INFO << imMsgData.msg_type();
	LOG_INFO << imMsgData.msg_data();
	LOG_INFO << imMsgData.attach_data();

}