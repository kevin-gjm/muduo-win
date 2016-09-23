#include "TcpServer.h"
#include "logging.h"
#include <functional>

using namespace calm;
using namespace calm::net;

class EchoServer
{
public:
	EchoServer(EventLoop* loop,InetAddress& listenAddr)
		:loop_(loop),
		server_(loop,listenAddr,"EchoServer")
	{
		server_.setConnectionCallback(std::bind(&EchoServer::onConnection,this,std::placeholders::_1));
		server_.setMessageCallback(std::bind(&EchoServer::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
	}
	void start()
	{
		server_.start();
	}
private:
	void onConnection(const TcpConnectionPtr& conn)
	{
		LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
			<< conn->localAddress().toIpPort() << " is "
			<< (conn->connected() ? "UP" : "DOWN");
		conn->send("hello calm\n");
	}
	void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
	{
		string msg(buf->retrieveAllAsString());
		LOG_TRACE << conn->name() << " recv " << msg.size() << " bytes at " << time.toString();
		if (msg == "exit\n")
		{
			conn->send("bye\n");
			conn->shutdown();
		}
		if (msg == "quit\n")
		{
			loop_->quit();
		}
		conn->send(msg);
	}
	EventLoop* loop_;
	TcpServer server_;
};//end EchoServer

int main_echoserver()
{
	LOG_INFO << "ThreadId = " << getCurrentThreadId();
	EventLoop loop;
	InetAddress listenAddr(2016);
	EchoServer server(&loop, listenAddr);
	server.start();

	loop.loop();
	return 0;
}