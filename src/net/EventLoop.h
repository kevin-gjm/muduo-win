// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

// modify by:Kevin <gjm_kevin@163.com>


#ifndef CALM_NET_EVENTLOOP_H_
#define CALM_NET_EVENTLOOP_H_

#include <thread.h>
#include <uncopyable.h>

#include <memory>
#include <vector>
#include <mutex>

namespace calm
{
	namespace net
	{
		class Channel;
		class Poller;
		//class TimeQueue; //是否可以参考 libevent确定定时器的使用

		class EventLoop : calm::uncopyable
		{
		public:
			typedef std::function<void()> Functor;
			EventLoop();
			~EventLoop();

			void loop();
			void quit();
			Timestamp pollReturnTime() const { return pollReturnTime_; }
			int64_t iteration() const { return iteration_; }

			void runInLoop(const Functor& cb);

			void queueInLoop(const Functor&cb);

			//ignore the timer

			void wakeup();

			void updateChannel(Channel* channel);
			void removeChannel(Channel* channel);
			bool hasChannel(channel* channel);

			void assertInLoopThread()
			{
				if (!isInLoopThread())
				{
					abortNotInLoopThread();
				}
			}

			bool isInLoopThread() const { return threadId_ == calm::getCurrentThreadId(); }

			bool eventHandling() const { return eventHandling_; }
			//ignore the context
			//void setContext()
			static EventLoop* getEventLoopOfCurrentThread();
		private:

			void abortNotInLoopThread();
			void handleRead();
			void doPendingFunctors();
			void printActiveChannels() const;

			typedef std::vector<Channel*> ChannelList;

			bool looping_; // atomic 
			bool quit_;
			bool eventHandling_;
			bool callingPendingFunctors_;
			int64_t iteration_;

			const uint64_t threadId_;
			Timestamp pollReturnTime_;
			
			std::shared_ptr<Poller> poller_;

			int wakeupFd_;
			std::shared_ptr<Channel> wakeupChannel_;

			ChannelList activeChannels_;
			Channel* currentActiveChannel_;

			std::mutex mutex_;
			std::vector<Functor> pendingFunctors_;
		};
	}// end namespace net
}// end namespace calm

#endif  // MUDUO_NET_EVENTLOOP_H
