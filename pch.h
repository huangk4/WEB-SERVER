#pragma once

#include "CheckOS.h"
#include <iostream>

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
#include <arpa/inet.h>
#endif


inline void print_err(std::string strError, int nCode)
{
	std::cout << strError << std::endl;
	std::cout << "´íÎó´úÂëÎª:" << nCode << std::endl;
	exit(1);
}