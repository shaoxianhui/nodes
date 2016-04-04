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
bool isStart = FALSE;
int GPRSPort = 0;
int cmdPort = 0;
int maxNode = 0;
unsigned char sec[128];
/////////////////////////////////////////////////////////////////////////////
using namespace std;
/////////////////////////////////////////////////////////////////////////////

NODEMANAGERDLL_API void InitGPRS(int _GPRSPort, int _cmdPort, int _maxNode, unsigned char _sec[128])
{
	GPRSPort = _GPRSPort;
	cmdPort = _cmdPort;
	maxNode = _maxNode;
	memcpy(sec, _sec, 128);
	CUdpThread::GetInstance();
	CTcpThread::GetInstance();
	CLog::GetInstance()->funLog("初始化GPRS！");
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