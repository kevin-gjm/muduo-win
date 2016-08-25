// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

//#pragma comment( lib, "ws2_32.lib"  )  // for select 
//#pragma comment(lib,"ws2_32")
//#include <WinSock2.h>
//#include "EventLoop.h"
//
//#include "logging.h"
//#include <assert.h>
//#include <WinBase.h>
//#include <direct.h>
//
//#include <WS2tcpip.h>
//#include <Windows.h>

#include <EventLoop.h>
#include <logging.h>
#include <Channel.h>
#include <Poller.h>


using namespace calm;
using namespace calm::net;

thread_local EventLoop* t_loopInThisThread = 0;

int initWinSock()
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(1, 1);
	if (0 == WSAStartup(wVersionRequested, &wsaData))
	{
		LOG_INFO << "RUN-MSG:Success to connect to the lib of socket!";
		return 0;
	}
	else
	{
		LOG_INFO << "ERR-MSG:Failed to connect to the lib of socket!";
		return -1;
	}
	//wVersionRequested是我们要求使用的WinSock的版本。
}

EventLoop::EventLoop()
  : looping_(false),
    threadId_(calm::getCurrentThreadId())
{
	initWinSock();
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

  timeval timeout;
  timeout.tv_sec = 10;	//wait_timeout 1 second
  timeout.tv_usec = 0;

  fd_set read_set, write_set, excep_set;
  FD_ZERO(&read_set);
  FD_ZERO(&write_set);
  FD_ZERO(&excep_set);

  int nfds = 0;
  do {
	  nfds  = select(0, NULL, NULL, NULL, &timeout);
  } while (nfds < 0 && errno == EINTR);

  LOG_TRACE << "EventLoop " << this << " stop looping";
  looping_ = false;
}

void EventLoop::abortNotInLoopThread()
{
  LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
            << " was created in threadId_ = " << threadId_
            << ", current thread id = " << calm::getCurrentThreadId();
}

