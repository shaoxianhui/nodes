#pragma once
#include <string>
#include "common.h"
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
		char temp[3];
		for (int i = 0; i < 12; i++)
		{
			sprintf_s(temp, "%02X", uid[i]);
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
};

