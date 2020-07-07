#pragma once

#include"pch.h"
#include"Task.h"

/**
�̳߳���
**/
class ThreadPool
{
private:
	std::queue<std::shared_ptr<Task>> m_taskQueue; //�������
	std::list<std::shared_ptr<std::thread>> m_threadList;	//�߳��б�
	static bool m_shutdown;   //ֹͣ��ȡ�����־
	size_t m_ThreadNum;   //�̳߳����Ѿ��������߳���
	std::mutex m_mutex;	//������
	size_t m_maxTaskNum;	//���������
	std::condition_variable m_notEmpty;	//��������

protected:


public:
	//���캯��������Ϊ�߳�����������������
	ThreadPool(size_t threadNum = std::thread::hardware_concurrency(),size_t maxTask=100) :m_ThreadNum(threadNum), m_maxTaskNum(maxTask) {};
	~ThreadPool();
	bool AddTask(std::shared_ptr<Task> ptask);  //�������
	void StopAll();  //ֹͣȫ���̳߳��е��߳�
	void Init();   //�����̳߳��е��߳�
	void Run();		//�߳��Զ���ȡ����ִ��
};