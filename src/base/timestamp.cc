#include <timestamp.h>
//#include <win_time.h>

#include <sys/timeb.h>
#include <time.h>

using namespace calm;

Timestamp Timestamp::now()
{
	/*win_time_val_t wintv;
	win_gettimeofday(&wintv);
	return Timestamp(static_cast<int64_t>(wintv.sec)*Timestamp::kMicroSecondsPerSecond + static_cast<int64_t>(wintv.msec));*/
	return Timestamp();
}

std::string Timestamp::toString() const
{
	/*unsigned short millitm = 0;
	tm *local = LocalTime(millitm);

	char buf[30] = { 0 };

	if (withMillisecond)
	{
		sprintf(buf, "%04u-%02u-%02u %02u:%02u:%02u.%03u",
			local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
			local->tm_hour, local->tm_min, local->tm_sec, millitm);
	}
	else
	{
		sprintf(buf, "%04u-%02u-%02u %02u:%02u:%02u",
			local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
			local->tm_hour, local->tm_min, local->tm_sec);
	}

	return std::string(buf);
	*/
	return std::string();
}

std::string Timestamp::toFormattedString(bool showMicro) const
{
	return std::string();
}

