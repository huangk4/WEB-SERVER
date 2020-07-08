#pragma once

#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>
#include <functional>
#include <cstdlib>
#include <cstring>
#include <list>
#include "CheckOS.h"
#include <chrono>
#include <condition_variable>
#ifdef I_OS_WIN32
#define WIN32_LEAN_AND_MEAN
#include <ws2tcpip.h>
#include <WinSock.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#ifdef I_OS_LINUX
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#endif


inline void print_err(std::string error, int code)
{
	std::cout << error << std::endl;
	std::cout << "错误代码为：" << code << std::endl;
	exit(1);
}
