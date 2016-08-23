
#include <log_file.h>
#include <logging.h>
#include <memory>
#include <thread>

std::shared_ptr<calm::LogFile> g_logFile;

void outputFunc(const char* msg, int len)
{
	g_logFile->append(msg, len);
}

void flushFunc()
{
	g_logFile->flush();
}

int main3(int argc, char* argv[])
{
	char name[256];
	strncpy(name, argv[0], 256);
	g_logFile.reset(new calm::LogFile("kevin", 200 * 1000));
	calm::Logger::setOutput(outputFunc);
	calm::Logger::setFlush(flushFunc);

	std::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

	for (int i = 0; i < 10000; ++i)
	{
		LOG_INFO << line << i;

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
	return 0;
}
