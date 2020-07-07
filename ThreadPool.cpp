#pragma once
#include"pch.h"
#include"ThreadPool.h"

using namespace std;

bool ThreadPool::m_shutdown=false;

ThreadPool::~ThreadPool()
{
	this->StopAll();
}


void ThreadPool::Init()
{
	cout << "��ʼ���̳߳�" << endl;
	m_shutdown = false;
	for (size_t i = 0; i < m_ThreadNum; i++)
	{
		m_threadList.push_back(std::make_shared<std::thread>(&ThreadPool::Run, this));
	}
}

void ThreadPool::Run()
{
	while (!m_shutdown)
	{
		unique_lock<mutex> locker(m_mutex);
		m_notEmpty.wait(locker,[this]{return !m_taskQueue.empty()||m_shutdown;});
		//�ж��Ƿ���ִֹ������
		if(m_shutdown)
			return;
		//ȡ������ִ��
		std::shared_ptr<Task> ptask=m_taskQueue.front();
		m_taskQueue.pop();
		locker.unlock();
		ptask->Run();
	}
}

bool ThreadPool::AddTask(std::shared_ptr<Task> ptask)
{
	if (m_taskQueue.size() < m_maxTaskNum)
	{
		cout<<"����һ������\n";
		m_taskQueue.push(ptask);
		m_notEmpty.notify_one();
		return true;
	}
	return false;
}

void ThreadPool::StopAll()
{

	m_shutdown = true;
	for (auto thread : m_threadList)
	{
		if (thread)
		{
			thread->join();
		}
	}
	m_threadList.clear();
}

