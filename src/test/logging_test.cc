#include <logging.h>
#include <thread_pool.h>
#include <stdio.h>
#include <iostream>

int g_total;
FILE* g_file;

using namespace calm;
void dummyOutput(const char* msg, int len)
{
	g_total += len;
	if (g_file)
	{
		fwrite(msg, 1, len, g_file);
	}
}

void bench(const char* type)
{
	calm::Logger::setOutput(dummyOutput);
	calm::Timestamp start(calm::Timestamp::now());
	g_total = 0;

	int n = 1000 * 1000;
	const bool kLongLog = false;
	calm::string empty = " ";
	calm::string longStr(3000, 'X');
	longStr += " ";
	for (int i = 0; i < n; ++i)
	{
		LOG_INFO << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz"
			<< (kLongLog ? longStr : empty)
			<< i;
	}
	calm::Timestamp end(calm::Timestamp::now());
	double seconds = timeDifference(end, start);
	printf("%12s: %f seconds, %d bytes, %10.2f msg/s, %.2f MiB/s\n",
		type, seconds, g_total, n / seconds, g_total / seconds / (1024 * 1024));
}

void logInThread()
{
	LOG_INFO << "logInThread";
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main5()
{

	calm::ThreadPool pool("pool");
	pool.start(5);
	pool.run(logInThread);
	pool.run(logInThread);
	pool.run(logInThread);
	pool.run(logInThread);
	pool.run(logInThread);

	LOG_TRACE << "trace";
	LOG_DEBUG << "debug";
	LOG_INFO << "Hello";
	LOG_WARN << "World";
	LOG_ERROR << "Error";
	LOG_INFO << sizeof(calm::Logger);
	LOG_INFO << sizeof(calm::LogStream);
	LOG_INFO << sizeof(calm::Fmt);
	LOG_INFO << sizeof(calm::LogStream::Buffer);

	//g_file = stdout;
	bench("nop");

	g_file = fopen("E:\\log", "w");

	bench("E:\\log");
	fclose(g_file);
	std::cin.get();
	return 0;
}