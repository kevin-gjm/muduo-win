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
			size_t readableBytes() const
			{
				return writerIndex_ - readerIndex_;
			}
			size_t writableBytes() const
			{
				return buffer_.size() - writerIndex_;
			}
			size_t prependableBytes() const
			{
				return readerIndex_;
			}
			const char* peek() const
			{
				return begin() + readerIndex_;
			}
			const char* findCRLF() const
			{
				const char* crlf = std::search(peek(),beginWrite(), kCRLF, kCRLF + 2);
				return crlf == beginWrite() ? NULL : crlf;
			}
			const char* findCRLF(const char* start) const
			{
				assert(peek() <= start);
				assert(start <= beginWrite());
				const char* crlf = std::search(start, beginWrite(), kCRLF, kCRLF + 2);
				return crlf == beginWrite() ? NULL : crlf;
			}
			const char* findEOL() const
			{
				const void* eol = memchr(peek(), '\n', readableBytes());
				return static_cast<const char*>(eol);
			}
			const char* findEOL(const char* start) const
			{
				assert(peek() <= start);
				assert(start <= beginWrite());
				const void* eol = memchr(start, '\n', readableBytes());
				return static_cast<const char*>(eol);
			}
			char* beginWrite()
			{
				return begin() + writerIndex_;
			}
			const char* beginWrite() const
			{
				return begin() + writerIndex_;
			}
			void hasWritten(size_t len)
			{
				assert(len <= writableBytes);
				writerIndex_ += len;
			}
			void unwrite(size_t len)
			{
				assert(len <= readableBytes);
				writerIndex_ - +len;
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
			static const char kCRLF[];
		};// end class Buffer
	}// end namespace net
}// end namespace calm

#endif //CALM_NET_BUFFER_H_