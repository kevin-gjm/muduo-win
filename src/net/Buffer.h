//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
// Date		:	2016.09.09
//
//////////////////////////////////////////////////////////////////////////
#ifndef CALM_NET_BUFFER_H_
#define CALM_NET_BUFFER_H_

#include "copyable.h"
#include "stringpiece.h"
#include "types.h"

#include "Endian.h"

#include <algorithm>
#include <vector>

#include <assert.h>
#include <string.h>

namespace calm
{
	namespace net
	{
		//////////////////////////////////////////////////////////////////////////
		// excerpts from muduo buffer
		// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
		//
		// @code
		// +-------------------+------------------+------------------+
		// | prependable bytes |  readable bytes  |  writable bytes  |
		// |                   |     (CONTENT)    |                  |
		// +-------------------+------------------+------------------+
		// |                   |                  |                  |
		// 0      <=      readerIndex   <=   writerIndex    <=     size
		// @endcode
		//////////////////////////////////////////////////////////////////////////
		class Buffer:public calm::copyable
		{
		public:
			static const size_t kCheapPrepend = 8;
			static const size_t kInitialSize = 1024;

			explicit Buffer(size_t initialSize = kInitialSize)
				:buffer_(kCheapPrepend+initialSize),
				readerIndex_(kCheapPrepend),
				writerIndex_(kCheapPrepend)
			{
				assert(1);
			}

			void swap(Buffer& rhs)
			{
				buffer_.swap(rhs.buffer_);
				std::swap(readerIndex_, rhs.readerIndex_);
				std::swap(writerIndex_, rhs.writerIndex_);
			}
			size_t readableBytes()
			{
				return writerIndex_ - readerIndex_;
			}
			size_t writableBytes()
			{
				return buffer_.size() - writerIndex_;
			}
			size_t prependableBytes()
			{
				return readerIndex_;
			}
			const char* peek() const
			{
				return begin() + readerIndex_;
			}
		private:
			char* begin()
			{
				return &*buffer_.begin();
			}
			const char* begin() const
			{
				return &*buffer_.begin();
			}

		private:
			std::vector<char> buffer_;
			size_t readerIndex_;
			size_t writerIndex_;
			static const char lCRLF[];
		};// end class Buffer
	}// end namespace net
}// end namespace calm

#endif //CALM_NET_BUFFER_H_