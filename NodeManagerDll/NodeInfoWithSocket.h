#pragma once
#include "NodeInfo.h"
#include "uv.h"
class CNodeInfoWithSocket
{
public:
	CNodeInfoWithSocket();
	~CNodeInfoWithSocket();
public:
	CNodeInfo info;
	sockaddr  addr;
	char cmdbuf[1024] = { 0x00 };
	int cmdlen = 0;
	time_t    timestamp;
};

