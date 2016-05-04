#pragma once
#include "stdafx.h"
#include "NodeInfo.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CNodeInfoList
{
public:
	CNodeInfoList();
	~CNodeInfoList();
public:
	int nodeNum = 0;
	CNodeInfo* nodeInfoList = NULL;
};
#pragma pack(pop)
