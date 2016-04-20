#pragma once
#include <string>
#include "common.h"
#include "uv.h"
using namespace std;
class CUtil
{
public:
	CUtil();
	~CUtil();
public:
	static string UIDtoString(char* uid)
	{
		string s;
		char temp[3] = { 0x00 };
		for (int i = 0; i < 12; i++)
		{
			sprintf_s(temp, "%02X", (uchar)uid[i]);
			s += temp;
		}
		return s;
	}
	static void StringtoUID(string suid, char* uid)
	{
		for (int i = 0; i < 12; i++)
		{
			sscanf_s(suid.c_str() + 2 * i, "%02X", uid + i);
		}
	}
	static uchar CalcCheck(char* buf, int len)
	{
		uchar sum = 0;
		for (int i = 0; i < len - 1; i++)
		{
			sum += buf[i];
		}
		return sum;
	}
	static string SockaddrToString(const struct sockaddr* addr)
	{
		unsigned short port;
		char* pPort = (char*)&port;
		pPort[0] = addr->sa_data[1];
		pPort[1] = addr->sa_data[0];

		char buf[64] = { 0x00 };
		uv_ip4_name((sockaddr_in*)addr, buf, 64);
		sprintf_s(buf, "%s:%d", buf, port);
		string ret = buf;
		return ret;
	}
};

