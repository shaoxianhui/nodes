// NodeManagerDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "NodeInfo.h"
#include "UdpThread.h"
#include "TcpThread.h"
#include "TimerThread.h"
#include "CountThread.h"
#include "Log.h"
#include "sqlite3.h"
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "common.h"
#include "AllNodes.h"
#include "NodeInfoList.h"
#include "SwitchPackageReq.h"
#include "HeartCountTimer.h"
/////////////////////////////////////////////////////////////////////////////
bool isStart = FALSE;
int GPRSPort = 0;
int cmdPort = 0;
int maxNode = 0;
bool printLog = TRUE;
unsigned char sec[128];
/////////////////////////////////////////////////////////////////////////////
using namespace std;
/////////////////////////////////////////////////////////////////////////////

NODEMANAGERDLL_API void InitGPRS(int _GPRSPort, int _cmdPort, int _maxNode, unsigned char _sec[128])
{
	char log[128] = { 0x00 };
	sprintf(log, "InitGPRS : gprsport = %d, cmdport = %d, maxnode = %d, status = success", _GPRSPort, _cmdPort, _maxNode);
	CLog::GetInstance()->funLog(log);
	GPRSPort = _GPRSPort;
	cmdPort = _cmdPort;
	maxNode = _maxNode;
	memcpy(sec, _sec, 128);
	CUdpThread::GetInstance();
	CTcpThread::GetInstance();
	CTimerThread::GetInstance();
	CVeriCountThread::GetInstance();
	CHeartCountTimer::GetInstance();
}
NODEMANAGERDLL_API void StartGPRS(void)
{
	if (isStart == TRUE)
	{
		return;
	}
	else
	{
		CUdpThread::GetInstance()->Start();
	}
}
NODEMANAGERDLL_API void StopGPRS(void)
{
	if (isStart == FALSE)
	{
		return;
	}
	else
	{
		CUdpThread::GetInstance()->Stop();
	}
}
NODEMANAGERDLL_API void StartLog(void)
{
	if (printLog == TRUE)
	{
		return;
	}
	else
	{
		CLog::GetInstance()->Start();
	}
}
NODEMANAGERDLL_API void StopLog(void)
{
	if (printLog == FALSE)
	{
		return;
	}
	else
	{
		CLog::GetInstance()->Stop();
	}
}
NODEMANAGERDLL_API void NodeNumRequest(uint *nodeNum)
{
	*nodeNum = (uint)CAllNodes::GetInstance()->getCount();
}
NODEMANAGERDLL_API void NodeInfoRequest(CNodeInfoList *ptrNodeInfoList)
{
	CAllNodes::GetInstance()->fill(ptrNodeInfoList);
}
/////////////////////////////////////////////////////////////////////////////