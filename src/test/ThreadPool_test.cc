
#include <thread_pool.h>
#include <count_down_latch.h>
#include <iostream>

using namespace calm;
void func()
{
	std::cout << "init func" << std::endl;
}

void func1(int i)
{
	std::cout << "func in thread pool=" << i << std::endl;
}
int main()
{
	ThreadPool pool;
	pool.setMaxQueueSize(10);
	pool.setThreadInitCallback(func);
	pool.start(10);

	for (int i = 0; i < 1000; ++i)
	{
		pool.run(std::bind(func1,i));
	}
	
	CountDownLatch latch(1);
	pool.run(std::bind(&calm::CountDownLatch::countDown,&latch));
	latch.wait();
	std::cin.get();

}