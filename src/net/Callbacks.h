//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
// Date		:	2016.09.20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CALM_NET_CALLBACKS_H_
#define CALM_NET_CALLBACKS_H_
#include <functional>
#include <memory>
#include "timestamp.h"

namespace calm
{
	namespace net
	{
		class Buffer;
		class TcpConnection;
		typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
		typedef std::function<void ()> TimerCallback;
		typedef std::function<void(const TcpConnectionPtr&)> ConnectionCallback;
		typedef std::function<void(const TcpConnectionPtr&)> CloseCallback;
		typedef std::function<void(const TcpConnectionPtr&)> WriteCompleteCallback;
		typedef std::function<void(const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;

		typedef std::function<void(const TcpConnectionPtr&, Buffer*, Timestamp)>MessageCallback;
		
		void defaultConnectionCallback(const TcpConnectionPtr& conn);
		void defaultMessageCallback(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp receiveTime);
	}// end namespace net
}// end namespace calm

#endif //CALM_NET_CALLBACKS_H_