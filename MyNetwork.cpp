#include "ThreadPool.h"
#include "Task.h"
#include "MyNetwork.h"
#include "pch.h"

void MyNetwork::InitWSA()
{
#ifdef I_OS_WIN32
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		std::cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << std::endl;
	}
	else {
		std::cout << "��ʼ���׽��ֿ�ɹ���" << std::endl;
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		std::cout << "�׽��ֿ�汾�Ų�����" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "�׽��ֿ�汾��ȷ��" << std::endl;
	}
	//������˵�ַ��Ϣ
#endif
}

int MyNetwork::Socket(int family, int type, int protocol)
{
	int code;
	if ((code = socket(family, type, protocol)) < 0)
	{
		print_err("socket error", code);
	}
	return code;
}

void MyNetwork::Bind(int listenfd, SA *servaddr, socklen_t size)
{
	int code;
	if ((code=bind(listenfd, servaddr, size) )!= 0)//ע�����׼��bind������
	{
		print_err("bind error",code);
	}
}

void MyNetwork::Listen(int listenfd,int max)
{
	int code;
	if ((code=listen(listenfd, max)) != 0)
	{
		print_err("listen error",code);
	}
}

int MyNetwork::Accept(int listenfd,SA *servaddr, socklen_t* len)
{
	int code;
	if ((code=accept(listenfd,servaddr,len)) < 0)
	{
		print_err("accept error", code);
	}
	return code;
}

void Session::showinfo(int connfd,char recvline[],std::string &t)//������ʾ������Ϣ
{
	std::cout << "���յ����� id:" << connfd << " ����Ϣ" << recvline << std::endl;
	std::cout << "������ظ��� id:" << connfd << " ����Ϣ\n";
	std::cin >> t;
}

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

void MyNetwork::Run()
{
	const int testthead = 2;
	//�����̳߳�
	ThreadPool threadpool(testthead, m_listenNum);
	threadpool.Init();

	Listen(m_listenfd,m_listenNum);
	while (!m_stop)
	{
		//��ȡͨ���׽��֣����̳߳�ȡ�߳�ȥ����
		int connfd=Accept(m_listenfd,(SA *)NULL,NULL);
		auto session=std::make_shared<Session>(connfd);
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
	std::unique_ptr<char[]> sendline(new char[m_n]);
	while (true)
	{
		memset(recvline.get(), 0, m_n);
		memset(sendline.get(), 0, m_n);
		int recvlen=recv(m_connfd,recvline.get(),m_n,0);
		if (recvlen < 0)
		{
			std::cout<<"���ܿͻ�����Ϣ����\n";
			break;
		}
		std::string t;
		showinfo(m_connfd,recvline.get(),t);
		int sendlen=t.length();
#ifndef I_OS_LINUX
		strcpy_s(sendline.get(), m_n, t.c_str());
#else
		strncpy(sendline.get(), t.c_str(), m_n);
#endif
		int send_len = send(m_connfd, sendline.get(), sendlen, 0);
		if (send_len < 0)
		{
			std::cout<<"������Ϣ����\n";
			break;
		}
	}

}
