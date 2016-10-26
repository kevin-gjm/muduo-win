#ifndef CALM_EROS_MODULE_H_
#define CALM_EROS_MODULE_H_
#include "IM.BaseDefine.pb.h"
#include "../eros/base/PduPacketParse.h"
#include "../eros/base/PduPacketParse/MessageModule_Impl.h"

using namespace calm;
using namespace calm::eros;

PduPacketParse* PduPacketParse::getModule(uint16_t moduleId)
{
	PduPacketParse* pRet=nullptr;
	switch (moduleId)
	{
	case IM::BaseDefine::SID_MSG :
		pRet = getMessageModule();
	default:
		break;
	}
	return pRet;
}

#endif //CALM_EROS_MODULE_H_