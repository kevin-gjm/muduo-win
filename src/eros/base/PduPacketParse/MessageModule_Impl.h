//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#ifndef CALM_EROS_MESSAGEMODULE_IMPL__H_
#define CALM_EROS_MESSAGEMODULE_IMPL_H_
#include "../eros/base/PduPacketParse.h"

namespace calm
{
	namespace eros
	{
		class MessageMoudle_Impl final :public calm::eros::PduPacketParse
		{
		public:
			void onPacket(PBHeader& header, std::string& pBody);
		private:
			void _messageData(std::string& pbBody);
		};

		PduPacketParse* getMessageModule();
	}//end namespace eros
}//end namespace calm
#endif //CALM_EROS_MESSAGEMODULE_IMPL_H_