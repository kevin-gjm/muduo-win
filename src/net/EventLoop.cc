// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)


#include "EventLoop.h"

#include "logging.h"

#include <assert.h>
//#include <WinSock2.h>

using namespace calm;

thread_local EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
  : looping_(false),
    threadId_(calm::getCurrentThreadId())
{
  LOG_TRACE << "EventLoop created " << this << " in thread " << threadId_;
  if (t_loopInThisThread)
  {
    LOG_FATAL << "Another EventLoop " << t_loopInThisThread
              << " exists in this thread " << threadId_;
  }
  else
  {
    t_loopInThisThread = this;
  }
}

EventLoop::~EventLoop()
{
  assert(!looping_);
  t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;

  //timeval timeout;
  //timeout.tv_sec = 1;	//wait_timeout 1 second
  //timeout.tv_usec = 0;

  //fd_set read_set, write_set, excep_set;
  //FD_ZERO(&read_set);
  //FD_ZERO(&write_set);
  //FD_ZERO(&excep_set);
  //while (looping_)
  //{
	 // int nfds = select(0, &read_set, &write_set, &excep_set, &timeout);
  //}
  while(looping_)
  { }
  LOG_TRACE << "EventLoop " << this << " stop looping";
  looping_ = false;
}

void EventLoop::abortNotInLoopThread()
{
  LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
            << " was created in threadId_ = " << threadId_
            << ", current thread id = " << calm::getCurrentThreadId();
}

