
#include <thread_pool.h>
#include <count_down_latch.h>
#include <iostream>
#include <string_piece.h>
#include <timestamp.h>

using namespace calm;
void func()
{
	for (int i = 0; i < 100000000; ++i) {
	} // ¼ÆÊý.
}

void func1(int i)
{
	std::cout << "func in thread pool=" << i << std::endl;
}
int main()
{
	{
		ThreadPool pool;
		pool.setMaxQueueSize(100000);
		//pool.setThreadInitCallback(func);
		pool.start(10);

		for (int i = 0; i < 10; ++i)
		{
			pool.run(func);
		}

		CountDownLatch latch(1);
		pool.run(std::bind(&calm::CountDownLatch::countDown, &latch));
		latch.wait();
		pool.stop();
	}
	std::cin.get();
	return 0;
}