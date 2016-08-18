

#include <async_logging.h>
#include <logging.h>
#include <timestamp.h>

#include <stdio.h>

#include <thread>



int kRollSize = 500 * 1024 * 1024;

calm::AsyncLogging* g_asyncLog = NULL;

void asyncOutput(const char* msg, int len)
{
	g_asyncLog->append(msg, len);
}

void bench(bool longLog)
{
	calm::Logger::setOutput(asyncOutput);

	int cnt = 0;
	const int kBatch = 1000;
	calm::string empty = " ";
	calm::string longStr(3000, 'X');
	longStr += " ";

	for (int t = 0; t < 30; ++t)
	{
		calm::Timestamp start = calm::Timestamp::now();
		for (int i = 0; i < kBatch; ++i)
		{
			LOG_INFO << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz "
				<< (longLog ? longStr : empty)
				<< cnt;
			++cnt;
		}
		calm::Timestamp end = calm::Timestamp::now();
		printf("%f\n", timeDifference(end, start) * 1000000 / kBatch);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main(int argc, char* argv[])
{
	//{
	//	// set max virtual memory to 2GB.
	//	size_t kOneGB = 1000 * 1024 * 1024;
	//	rlimit rl = { 2 * kOneGB, 2 * kOneGB };
	//	setrlimit(RLIMIT_AS, &rl);
	//}

//	printf("pid = %d\n", getpid());

	char name[256];
	strncpy(name, argv[0], 256);
	calm::AsyncLogging log("kevin_ming", kRollSize);
	log.start();
	g_asyncLog = &log;

	bool longLog = true;
	bench(longLog);
}
