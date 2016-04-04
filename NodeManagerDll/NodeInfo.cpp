#include "NodeInfo.h"
#include "stdio.h"
#include "string.h"

CNodeInfo::CNodeInfo()
{
	memset(UID, 0, sizeof(UID));
	//sprintf((char*)phoneNum, "%s", "00000000000");
	allStatus = 0;
	SN = 0;
}

CNodeInfo::~CNodeInfo()
{
}

void CNodeInfo::setOnline()
{
	allStatus = allStatus | 0x01;
}
void CNodeInfo::setOffline()
{
	allStatus = allStatus & 0xFE;
}
void CNodeInfo::setSuccess()
{
	allStatus = allStatus | 0x02;
}
void CNodeInfo::setFail()
{
	allStatus = allStatus & 0xFD;
}
bool CNodeInfo::isOnline()
{
	return ((allStatus & 0x01) == 0x01);
}
bool CNodeInfo::isSuccess()
{
	return ((allStatus & 0x02) == 0x02);
}
bool CNodeInfo::isOnlineAndSuccess()
{
	return ((allStatus & 0x03) == 0x03);
}