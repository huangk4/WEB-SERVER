#pragma once

#include<queue>
#include<string>
#include<thread>
#include<mutex>
#include<queue>
#include<iostream>
#include<functional>
#include<cstdlib>
#include<list>
#include "CheckOS.h"

#ifdef I_OS_WIN32
#define WIN32_LEAN_AND_MEAN
#include <ws2tcpip.h>
#include<WinSock.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#ifdef I_OS_LINUX
#include<sys/socket.h>
#include<errno.h>
#include<netinet/in.h>
#include<sys/types.h>
#endif


void print_err(std::string info,int code);