#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CNodeQueryEndPackageAck
{
public:
	CNodeQueryEndPackageAck();
	~CNodeQueryEndPackageAck();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0xF2;
	ushort length = 30;
	ushort  numFrame = 0xFFFF;
	uint	totalNodeNum;                //表示共传输多少个节点状态
	uchar	rev[24];                    //保留定义
	uchar   check = 0;
	/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)