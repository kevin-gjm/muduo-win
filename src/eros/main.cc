//////////////////////////////////////////////////////////////////////////
//
// Copyright(C)	2016, gjm_kevin.  All rights reserved.
// Author	:	gjm_kevin@163.com
//
//////////////////////////////////////////////////////////////////////////
#include "EventLoop.h"
#include "logging.h"
#include "InetAddress.h"

#include "eros.h"
#include <iostream>

using namespace calm;
using namespace calm::net;


int main(int argc, char* argv[])
{
	LOG_INFO << "eros start";
	EventLoop loop;
	InetAddress serverAddr("192.168.255.130",2007);
	Eros client(&loop, serverAddr);
	client.connect();
	loop.loop();

	std::cin.get();
	return 0;
}
