//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#include "PBHeader.h"

using namespace calm;
using namespace calm::net;
using namespace calm::eros;

PBHeader::PBHeader()
	:length_(0),
	version_(VERSION),
	flag_(0),
	moduleId_(0),
	commandId_(0),
	seqNumber_(0),
	reserved_(0),
	headerBuffer_()
{
	headerBuffer_.resize(HEADER_LENGTH);
}

char* PBHeader::getSerializeBuffer()
{
	headerBuffer_[0] = static_cast<uint8_t>(length_ >> 24);
	headerBuffer_[1] = static_cast<uint8_t>((length_ >> 16) & 0xFF);
	headerBuffer_[2] = static_cast<uint8_t>((length_ >> 8) & 0xFF);
	headerBuffer_[3] = static_cast<uint8_t>(length_ & 0xFF);
	headerBuffer_[4] = static_cast<uint8_t>(version_ >> 8);
	headerBuffer_[5] = static_cast<uint8_t>(version_ & 0xFF);
	headerBuffer_[6] = static_cast<uint8_t>(flag_ >> 8);
	headerBuffer_[7] = static_cast<uint8_t>(flag_ & 0xFF);
	headerBuffer_[8] = static_cast<uint8_t>(moduleId_ >> 8);
	headerBuffer_[9] = static_cast<uint8_t>(moduleId_ & 0xFF);
	headerBuffer_[10] = static_cast<uint8_t>(commandId_ >> 8);
	headerBuffer_[11] = static_cast<uint8_t>(commandId_ & 0xFF);
	headerBuffer_[12] = static_cast<uint8_t>(seqNumber_ >> 8);
	headerBuffer_[13] = static_cast<uint8_t>(seqNumber_ & 0xFF);
	headerBuffer_[14] = static_cast<uint8_t>(reserved_ >> 8);
	headerBuffer_[15] = static_cast<uint8_t>(reserved_ & 0xFF);
	return (char*)(&headerBuffer_[0]);
}

void PBHeader::unSerialize(Buffer* buf)
{
	if (buf->readableBytes() < HEADER_LENGTH)
		return;
	memcpy(&headerBuffer_[0], buf->peek(), HEADER_LENGTH);
	length_ = buf->readInt32();
	version_ = buf->readInt16();
	flag_ = buf->readInt16();
	moduleId_ = buf->readInt16();
	commandId_ = buf->readInt16();
	seqNumber_ = buf->readInt16();
	reserved_ = buf->readInt16();
}
void PBHeader::clear()
{
	memset(&headerBuffer_[0], 0, HEADER_LENGTH);
	length_ = 0;
	version_ = VERSION;
	flag_ = 0;
	moduleId_ = 0;
	commandId_ = 0;
	seqNumber_ = 0;
	reserved_ = 0;
}
