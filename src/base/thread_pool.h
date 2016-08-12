#ifndef CALM_BASE_THREADPOOL_H_
#define CALM_BASE_THREADPOOL_H_

#include <uncopyable.h>
#include <types.h>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>
#include <deque>
#include <vector>

namespace calm
{

	class ThreadPool :calm::uncopyable
	{
	public:
		typedef std::function<void()> Task;
		explicit ThreadPool(const string& nameArg = string("ThreadPool"));
		~ThreadPool();
		// must set before start
		void setMaxQueueSize(int maxSize){ maxQueueSize_ = maxSize; }
		void setThreadInitCallback(const Task& cb)
		{
			threadInitCallback_ = cb;
		}

		void start(int numThreads);
		void stop();
		const string& name() const
		{
			return name_;
		}

		size_t queueSize() const;
		void run(const Task& f);
		

	private:
		bool _isFull() const;
		void _runInThread();
		Task _take();

		mutable  std::mutex mutex_;
		std::condition_variable notEmpty_;
		std::condition_variable notFull_;

		std::deque<Task> queue_;
		//FIXME
		//here use: std::vector<std::thread> thread_;  can it works ??
		//perform well than blow?
		//貌似没有必要搞成智能指针
		std::vector<std::shared_ptr<std::thread>> thread_;
		
		size_t maxQueueSize_;
		Task threadInitCallback_;
		string name_;
		bool running_;

	};//end class ThreadPool
}//end namespace calm
#endif //CALM_BASE_THREADPOOL_H_