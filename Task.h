#pragma once

class Task
{
public:
	Task(void* data = nullptr) :m_pdata(data) {};
	~Task() {};
	virtual void Run() = 0;

protected:
	void* m_pdata;
};
