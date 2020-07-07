#pragma once
#include"pch.h"

void print_err(std::string error,int code)
{
	std::cout << error << std::endl;
	std::cout<<"´íÎó´úÂëÎª:"<<code<<std::endl;
	exit(1);
}

