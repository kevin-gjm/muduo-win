//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#ifndef CALM_EROS_PBHEADER_H_
#define CALM_EROS_PBHEADER_H_

#include "Buffer.h"
#include "uncopyable.h"
#include "types.h"
#include <vector>

namespace calm
{
	namespace eros
	{
		
		const static int8_t HEADER_LENGTH = 16;
		const static int16_t VERSION = 1;
		class PBHeader :calm::uncopyable
		{
		public:
			PBHeader();
			//default dtor
			//~PBHeader();

			char* getSerializeBuffer();
			void unSerialize(calm::net::Buffer* buf);
			void clear();

			inline void setLength(uint32_t length) { length_ = length; }
			inline void setFlag(uint16_t flag) { flag_ = flag; }
			inline void setModuleId(uint16_t moduleId) { moduleId_ = moduleId; }
			inline void setCommandId(uint16_t cmdId) { commandId_ = cmdId; }
			inline void setSeqNumber(uint16_t seq) { seqNumber_ = seq; }
			inline void setReserved(uint16_t reserved) { reserved_ = reserved; }

			inline uint32_t getLength()const { return length_; }
			inline uint16_t getFlag() const { return flag_; }
			inline uint16_t getModuleId() const { return moduleId_; }
			inline uint16_t getCommandId()const { return commandId_; }
			inline uint16_t getReserved() const { return reserved_; }
			inline uint16_t getSeqNumber()const { return seqNumber_; }
		private:
			typedef std::vector<uint8_t> ByteVector;

			uint32_t length_;
			uint16_t version_;
			uint16_t flag_;
			uint16_t moduleId_;
			uint16_t commandId_;
			uint16_t seqNumber_;
			uint16_t reserved_;
			ByteVector headerBuffer_;
		};// end class PBHeader
	}//end namespace eros
}// end namespace calm
#endif //CALM_EROS_PBHEADER_H_