#pragma once
#include "stdafx.h"
#include "NodeInfo.h"
class NODEMANAGERDLL_API CNodeInfoList
{
public:
	CNodeInfoList();
	~CNodeInfoList();
public:
	int nodeNum = 0;
	CNodeInfo* nodeInfoList = NULL;
};

