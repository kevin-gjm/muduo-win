
#include <log_stream.h>

#include <limits>
#include <algorithm>
#include <assert.h>

#ifdef _WIN32
#define	snprintf	sprintf_s
#endif

using namespace calm;
using namespace calm::detail;

namespace calm
{
namespace detail
{
	const char digits[] = "9876543210123456789";
	const char* zero = digits + 9;
	const char digitsHex[] = "0123456789ABCDEF";
	template<typename T>
	size_t convert(char buf[], T value)
	{
		T i = value;
		char* p = buf;
		do 
		{
			int lsd = static_cast<int>(i % 10);
			i /= 10;
			*p++ = zero[lsd];
		} while (i!=0);
		if (value < 0)
		{
			*p++ = '-';
		}
		*p = '\0';
		std::reverse(buf, p);
		return p - buf;
	}
	size_t convertHex(char buf[], uintptr_t value)
	{
		uintptr_t i = value;
		char* p = buf;
		do 
		{
			int lsd = static_cast<int>(i % 16);
			i /= 16;
			*p++ = digitsHex[lsd];
		} while (i != 0);
		*p = '\0';
		std::reverse(buf, p);
		return p - buf;
	}
	template class FixedBuffer<kSmallBuffer>;
	template class FixedBuffer<kLargeBuffer>;
}// end namespace detail
}// end namespace calm
template<typename T>

void LogStream::_formatInteger(T v)
{
	if (buffer_.avail() >= kMaxNumericSize)
	{
		size_t len = convert(buffer_.current(), v);
		buffer_.add(len);
	}
}
LogStream& LogStream::operator<<(short v)
{
	*this << static_cast<int>(v);
	return *this;
}
LogStream& LogStream::operator<<(unsigned short v)
{
	*this << static_cast<unsigned int>(v);
	return *this;
}
LogStream& LogStream::operator<<(int v)
{
	_formatInteger(v);
	return *this;
}
LogStream& LogStream::operator<<(unsigned int v)
{
	_formatInteger(v);
	return *this;
}
template<typename T>
Fmt::Fmt(const char * fmt, T val)
{
	length_ = snprintf(buf_, sizeof buf_, fmt, val);
}
