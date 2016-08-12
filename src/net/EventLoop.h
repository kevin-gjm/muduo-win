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

namespace calm
{

class EventLoop : calm::uncopyable
{
 public:

  EventLoop();
  ~EventLoop();

  void loop();

  void assertInLoopThread()
  {
    if (!isInLoopThread())
    {
      abortNotInLoopThread();
    }
  }

  bool isInLoopThread() const { return threadId_ == calm::getCurrentThreadId(); }

 private:

  void abortNotInLoopThread();

  bool looping_; // atomic 
  const uint64_t threadId_;
};

}

#endif  // MUDUO_NET_EVENTLOOP_H
