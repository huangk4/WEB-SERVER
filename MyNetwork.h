#pragma once
#include "Task.h"
using SA = struct sockaddr;

class Session :public Task
{
private:
	int m_connfd;
	int m_n;//缓冲区大小
	struct sockaddr_in m_servaddr;
public:
	Session(int connfd,int n=65535) :m_connfd(connfd),m_n(n) {}
	void Run();
	void showinfo(int connfd, char recvline[], std::string& t);
};

class MyNetwork
{
private:
	struct sockaddr_in m_servaddr;
	bool m_stop;
	int m_listenfd,connfd;
	int m_listenNum;//最大监听人数
	
public:
	MyNetwork(int listen=100);
	~MyNetwork();
	
	void Run();
	void InitWSA();
	int Socket(int family, int type, int protocol);
	void Bind(int sockfd, SA* addr, socklen_t addrlen);
	void Listen(int sockfd, int max);
	int Accept(int sockfd, SA* addr, socklen_t* addrlen);
};
