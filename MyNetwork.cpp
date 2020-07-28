#include "ThreadPool.h"
#include "MyNetwork.h"
#include "pch.h"
#include <cstring>

MyNetwork::MyNetwork(int listen) :m_stop(false), m_listenNum(listen)
{
#ifdef I_OS_WIN32
	InitWSA();
#endif

	//��ʼ��TCP�׽���
	m_listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	//���������׽��ֵ�ַ
	memset(&m_servaddr, 0, sizeof(m_servaddr));
	m_servaddr.sin_family = AF_INET;
	m_servaddr.sin_port = htons(1333);
	m_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind(m_listenfd, (SA*)&m_servaddr, sizeof(m_servaddr));
	//���׽���ת��Ϊ�����׽���
}

MyNetwork::~MyNetwork()
{
#ifdef I_OS_WIN32
	WSACleanup();
#endif
}

void MyNetwork::InitWSA()
{
#ifdef I_OS_WIN32
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		std::cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << std::endl;
	}
	// ���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
	{
		std::cout << "�׽��ֿ�汾�Ų�����" << std::endl;
		WSACleanup();
	}
	//������˵�ַ��Ϣ
#endif
}

int MyNetwork::Socket(int family, int type, int protocol)
{
	int code = socket(family, type, protocol);
	if (code < 0)
	{
		print_err("socket error", code);
	}
	return code;
}

void MyNetwork::Bind(int sockfd, SA* addr, socklen_t addrlen)
{
	int code = bind(sockfd, addr, addrlen);
	if (code != 0) //ע�����׼��bind������
	{
		print_err("bind error", code);
	}
}

void MyNetwork::Listen(int sockfd, int max)
{
	int code = listen(sockfd, max);
	if (code != 0)
	{
		print_err("listen error", code);
	}
}

int MyNetwork::Accept(int sockfd, SA* addr, socklen_t* addrlen)
{
	int code = accept(sockfd, addr, addrlen);
	if (code < 0)
	{
		print_err("accept error", code);
	}
	return code;
}

void MyNetwork::Run()
{
	const int testthead = 2;
	//�����̳߳�
	ThreadPool threadpool(testthead, m_listenNum);
	threadpool.Init();

	Listen(m_listenfd, m_listenNum);
	while (!m_stop)
	{
		// ��ȡͨ���׽��֣����̳߳�ȡ�߳�ȥ����
		sockaddr_in clientaddr;
		socklen_t nLen = sizeof(sockaddr_in);
		int connfd = Accept(m_listenfd, (SA*)&clientaddr, &nLen);
		auto session = std::make_shared<Session>(connfd);
		threadpool.AddTask(session);
	}
#ifdef I_OS_WIN32
	closesocket(m_listenfd);
#endif

#ifdef I_OS_LINUX
	close(m_listenfd);
#endif
}

void Session::Run()
{
	std::unique_ptr<char[]> recvline(new char[m_n]);
	while (true)
	{
		memset(recvline.get(), 0, m_n);
		int recvlen = recv(m_connfd, recvline.get(), m_n, 0);
		if (recvlen <= 0)
		{
			std::cout << "���ܿͻ�����Ϣ����\n";
		}
		else
		{
			hs.Analys(std::string(recvline.get()));
		}
#ifdef I_OS_WIN32
		closesocket(m_connfd);
#endif

#ifdef I_OS_LINUX
		close(m_connfd);
#endif
		break;
	}
}