// NodeManagerDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "NodeInfo.h"
#include "UdpThread.h"
#include "TcpThread.h"
#include "Log.h"
#include "sqlite3.h"
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "common.h"
#include "AllNodes.h"
#include "NodeInfoList.h"
#include "SitchPackageReq.h"
/////////////////////////////////////////////////////////////////////////////
static bool isStart = FALSE;
static int GPRSPort = 0;
static int cmdPort = 0;
static int maxNode = 0;
static unsigned char sec[128];
static int vv = 0;
/////////////////////////////////////////////////////////////////////////////
using namespace std;
/////////////////////////////////////////////////////////////////////////////
NODEMANAGERDLL_API void InitDll(void)
{
	/*map<string, string> ok;
	ok.insert(pair<string, string>("122", "aclive"));
	map<char*, string> ok1;
	char ffi[12];
	ok1.insert(pair<char*, string>(ffi, "345"));
	sqlite3 * pDB;
	char* errMsg;
	sqlite3_open("E:\\NodeManager\\sqlite-tools-win32-x86-3120000\\hello.db", &pDB);
	int res = sqlite3_exec(pDB, "begin transaction;", 0, 0, &errMsg);

	for (int i = 1; i < 10; ++i)
	{
		std::stringstream strsql;
		strsql << "insert into test_tab  values(";
		strsql << i << "," << (i + 10) << ");";
		std::string str = strsql.str();
		res = sqlite3_exec(pDB, str.c_str(), 0, 0, &errMsg);
		if (res != SQLITE_OK)
		{
			std::cout << "执行SQL 出错." << errMsg << std::endl;
		}
	}

	res = sqlite3_exec(pDB, "commit transaction;", 0, 0, &errMsg);

	std::cout << "SQL成功执行." << std::endl;*/

	CUdpThread::GetInstance();
	//CTcpThread::GetInstance();
	CLog::GetInstance();
	/*CHartPackageReq req;
	for (int i = 0; i < 12; i++)
	{
	req.data.UID[i] = vv + i;
	}
	for (int i = 0; i < 11; i++)
	{
	req.data.phoneNum[i] = 0x30 + i;
	}
	vv++;
	CAllNodes::GetInstance()->insertNode(&req, NULL);*/
}
NODEMANAGERDLL_API void InitGPRS(int _GPRSPort, int _cmdPort, int _maxNode, unsigned char _sec[128])
{
	GPRSPort = _GPRSPort;
	cmdPort = _cmdPort;
	maxNode = _maxNode;
	memcpy(sec, _sec, 128);
}
NODEMANAGERDLL_API void StartGPRS(void)
{
	isStart = TRUE;
}
NODEMANAGERDLL_API void StopGPRS(void)
{
	isStart = FALSE;
}
NODEMANAGERDLL_API void NodeNumRequest(uint *nodeNum)
{
	*nodeNum = (uint)CAllNodes::GetInstance()->getCount();
}
NODEMANAGERDLL_API void NodeInfoRequest(CNodeInfoList *ptrNodeInfoList)
{
	CAllNodes::GetInstance()->fill(ptrNodeInfoList);
}
//NODEMANAGERDLL_API void NodeCmdSend(CNodeInfo* nodeInfo, unsigned char type, unsigned short dataLen, unsigned char *ptrData)
//{

//}
/////////////////////////////////////////////////////////////////////////////