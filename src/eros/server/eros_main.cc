#include "eros_server.h"

//int main()
int main_server()
{
	EventLoop loop;
	InetAddress listenAddr(2016);
	ErosServer server(&loop, listenAddr);
	server.start();
	loop.loop();
	return 0;
}