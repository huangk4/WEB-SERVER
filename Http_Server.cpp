#include "Http_Server.h"
#include <regex>
#include <cassert>

using namespace std;

Http_Server::Http_Server(const int nClient)
{
	m_nClient = nClient;
#ifdef I_OS_LINUX
	arHttpInfo = { "Host", "Connection", "DNT", "Upgrade-Insecure-Requests",
		"User-Agent", "Sec-Fetch-User", "Accept", "Sec-Fetch-Site", "Sec-Fetch-Mode", "Accept-Encoding",
		"Accept-Language" };
#endif
}

void Http_Server::Analys(string&& strInfo)
{
	regex re1{ "GET (.*) HTTP/1.1" };
	smatch result;
	string strGet;
	if (regex_search(strInfo, result, re1))
	{
		strGet = result[1];
		cout << result[1] << endl;
	}
	for (const auto& x : arHttpInfo)
	{
		regex re{ x + ": (.*)" };
		smatch results;
		if (regex_search(strInfo, results, re))
		{
			mapHttpInfo.insert(pair<string, string>(x, results[0]));
		}
	}
	if (strGet == "favicon.ico")	// Í¼±ê
	{
		return bad_request();
	}
	else if (strGet == "/")
	{
		header("text/html");
		string strFile{ m_strPath + "/index.html" };
		shared_ptr<FILE> fp(fopen(strFile.c_str(), "r"), [](FILE* fp) { fclose(fp); });
		assert(fp != nullptr);
		char chBuff[1024] = { 0 };
		fgets(chBuff, sizeof(chBuff), fp.get());
		while (!feof(fp.get()))
		{
			send(m_nClient, chBuff, strlen(chBuff), 0);
			fgets(chBuff, sizeof(chBuff), fp.get());
		}
	}
	else
	{
		if (strGet.find(".css") != string::npos)
		{
			header("text/css");
			string strFile{ m_strPath + strGet };
			shared_ptr<FILE> fp(fopen(strFile.c_str(), "r"), [](FILE* fp) { fclose(fp); });
			assert(fp != nullptr);
			char chBuff[1024] = { 0 };
			fgets(chBuff, sizeof(chBuff), fp.get());
			while (!feof(fp.get()))
			{
				send(m_nClient, chBuff, strlen(chBuff), 0);
				fgets(chBuff, sizeof(chBuff), fp.get());
			}
		}
		else if (strGet.find(".js") != string::npos)
		{
			header("application/javascript");
			string strFile{ m_strPath + strGet };
			shared_ptr<FILE> fp(fopen(strFile.c_str(), "r"), [](FILE* fp) { fclose(fp); });
			assert(fp != nullptr);
			char chBuff[1024] = { 0 };
			fgets(chBuff, sizeof(chBuff), fp.get());
			while (!feof(fp.get()))
			{
				send(m_nClient, chBuff, strlen(chBuff), 0);
				fgets(chBuff, sizeof(chBuff), fp.get());
			}
		}
		else if (strGet.find(".woff") != string::npos)
		{
			header("application/octet-stream");
			string strFile{ m_strPath + strGet };
			shared_ptr<FILE> fp(fopen(strFile.c_str(), "r"), [](FILE* fp) { fclose(fp); });
			char chBuff[1024] = { 0 };
			fgets(chBuff, sizeof(chBuff), fp.get());
			while (!feof(fp.get()))
			{
				send(m_nClient, chBuff, strlen(chBuff), 0);
				fgets(chBuff, sizeof(chBuff), fp.get());
			}
		}
		else
		{
			return bad_request();
		}
	}
}

