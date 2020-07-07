#pragma once

using SA = struct sockaddr;
void InitWSA();
int Socket(int family, int type, int protocol);
void Bind(SOCKET listenfd, SA* servaddr, socklen_t size);
void Listen(SOCKET listenfd, int max);
int Accept(SOCKET listenfd, SA* servaddr, socklen_t* len);





class Session :public Task
{
private:
	int m_connfd;
	int m_n;//��������С
	struct sockaddr_in m_servaddr;
public:
	Session(int connfd,int n=65535) :m_connfd(connfd),m_n(n) {}
	void Run();
};



class MyNetwork
{
private:
	struct sockaddr_in m_servaddr;
	bool m_stop;
	int m_listenfd,connfd;
	int m_listenNum;//����������
	

public:
	MyNetwork(int listen=100);
	~MyNetwork();

	
	void Run();
};

//if((m_sockfd=socket(AF_INET,SOCK_STREAM,0))<0)