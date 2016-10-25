//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#ifndef CALM_EROS_PDUPACKETPARSE_H_
#define CALM_EROS_PDUPACKETPARSE_H_
#include <string>
namespace calm
{
	namespace eros
	{
		class PBHeader;
		class PduPacketParse
		{
		public:
			virtual void onPacket(PBHeader& header, std::string& pBody) = 0;
		};
	}// end namespace eros
}// end namespace calm
#endif //CALM_EROS_PDUPACKETPARSE_H_