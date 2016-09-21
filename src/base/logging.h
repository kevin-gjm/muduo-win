#ifndef CALM_BASE_LOGGING_H_
#define CALM_BASE_LOGGING_H_

#include <log_stream.h>
#include <timestamp.h>

#ifdef _MSC_VER
#define  WIN32_LEAN_AND_MEAN
#include <windows.h> //for get environment variable
#define	snprintf	sprintf_s
#define __func__ __FUNCTION__
#endif


namespace calm
{
	class Logger
	{
	public:
		enum LogLevel
		{
			TRACE,
			DEBUG,
			INFO,
			WARN,
			ERR,  //confilct with windows defination ERROR
			FATAL,
			NUM_LOG_LEVELS,
		};
		class SourceFile
		{
		public:
			template<int N>
			inline SourceFile(const char(&arr)[N])
				:data_(arr),
				size_(N - 1)
			{
				// linux use '/' as the directory separator but windows use '\'
				const char* slash = strrchr(data_, '\\');
				if (slash)
				{
					data_ = slash + 1;
					size_ -= static_cast<int>(data_ - arr);
				}
			}
			explicit SourceFile(const char* filename)
				:data_(filename)
			{
				const char* slash = strrchr(data_, '/');
				if (slash)
				{
					data_ = slash + 1;
				}
				size_ -= static_cast<int>(strlen(data_));
			}

			const char* data_;
			int size_;
		};// end class SourceFile

		Logger(SourceFile file, int line);
		Logger(SourceFile file, int line, LogLevel level);
		Logger(SourceFile file, int line, LogLevel level, const char* func);
		Logger(SourceFile file, int line, bool toAbort);
		~Logger();

		LogStream& stream(){ return impl_.stream_; }
		static LogLevel logLevel();
		static void setLogLevel(LogLevel level);
		typedef void(*OutputFunc)(const char* msg, int len);
		typedef void(*FlushFunc)();
		static void setOutput(OutputFunc);
		static void setFlush(FlushFunc);
	private:
		class Impl
		{
		public:
			typedef Logger::LogLevel LogLevel;
			Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
			void formatTime();
			void finish();

			Timestamp time_;
			LogStream stream_;
			LogLevel level_;
			int line_;
			SourceFile basename_;
		};// end class Impl
		Impl impl_;
	};// end class Logger
	extern Logger::LogLevel g_logLevel;

	inline Logger::LogLevel Logger::logLevel()
	{
		return g_logLevel;
	}


	//
	// CAUTION: do not write:
	//
	// if (good)
	//   LOG_INFO << "Good news";
	// else
	//   LOG_WARN << "Bad news";
	//
	// this expends to
	//
	// if (good)
	//   if (logging_INFO)
	//     logInfoStream << "Good news";
	//   else
	//     logWarnStream << "Bad news";
	//
#define LOG_TRACE if (calm::Logger::logLevel() <= calm::Logger::TRACE) \
  calm::Logger(__FILE__, __LINE__, calm::Logger::TRACE, __func__).stream()
#define LOG_DEBUG if (calm::Logger::logLevel() <= calm::Logger::DEBUG) \
  calm::Logger(__FILE__, __LINE__, calm::Logger::DEBUG, __func__).stream()
#define LOG_INFO if (calm::Logger::logLevel() <= calm::Logger::INFO) \
  calm::Logger(__FILE__, __LINE__).stream()
#define LOG_WARN calm::Logger(__FILE__, __LINE__, calm::Logger::WARN).stream()
#define LOG_ERROR calm::Logger(__FILE__, __LINE__, calm::Logger::ERR).stream()
#define LOG_FATAL calm::Logger(__FILE__, __LINE__, calm::Logger::FATAL).stream()
#define LOG_SYSERR calm::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL calm::Logger(__FILE__, __LINE__, true).stream()
	

	// Taken from glog/logging.h
	//
	// Check that the input is non NULL.  This very useful in constructor
	// initializer lists.

#define CHECK_NOTNULL(val) \
  ::calm::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

	// A small helper for CHECK_NOTNULL().
	template <typename T>
	T* CheckNotNull(Logger::SourceFile file, int line, const char *names, T* ptr)
	{
		if (ptr == NULL)
		{
			Logger(file, line, Logger::FATAL).stream() << names;
		}
		return ptr;
	}


} // end namespace calm


#endif //CALM_BASE_LOGGING_H_