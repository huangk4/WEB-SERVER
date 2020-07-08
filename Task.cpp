#include"pch.h"
#include"Task.h"

void TestTask::Run()
{
	std::cout << std::this_thread::get_id() << "£º123\n";
	std::this_thread::sleep_for(std::chrono::seconds(rand()%2));
}
