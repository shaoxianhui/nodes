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
	uv_udp_t* handle;
	sockaddr  addr;
};

