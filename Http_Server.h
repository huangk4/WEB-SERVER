#pragma once

#include "pch.h"

#include <string>
#include <array>
#include <unordered_map>

class Http_Server
{
public:
	Http_Server(const int nClient);
	void Analys(std::string&& strInfo);

private:
	void bad_request();
	void header(std::string strType);

private:
	std::unordered_map<std::string, std::string> mapHttpInfo;
	int m_nClient;

#ifdef I_OS_WIN
	std::array<std::string, 11> arHttpInfo{"Host", "Connection", "DNT", "Upgrade-Insecure-Requests",
		"User-Agent", "Sec-Fetch-User", "Accept", "Sec-Fetch-Site", "Sec-Fetch-Mode", "Accept-Encoding",
		"Accept-Language"};
	const std::string m_strPath{ "./2048-dara" };
#endif

#ifdef I_OS_LINUX
	std::array<std::string, 11> arHttpInfo;
	const std::string m_strPath{ "/root/2048-dara" };
#endif
};

inline void Http_Server::bad_request()
{
	std::string strRes{ "HTTP/1.0 400 BAD REQUEST\r\n"
		"Content-type: text/html\r\n\r\n"
		"<P>Your browser sent a bad request, "
		"such as a POST without a Content-Length.\r\n" };
	send(m_nClient, strRes.c_str(), strRes.size(), 0);
}

inline void Http_Server::header(std::string strType)
{
	std::string strHeader("HTTP/1.0 200 OK\r\nContent-Type: " + strType + "\r\ncharset: utf-8\r\n"
		"Connection: keep-alive\r\n\r\n");
	send(m_nClient, strHeader.c_str(), strHeader.size(), 0);
}