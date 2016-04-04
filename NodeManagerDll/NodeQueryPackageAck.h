#pragma once
#include "NodeInfo.h"
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CNodeQueryPackageAck
{
public:
	CNodeQueryPackageAck();
	~CNodeQueryPackageAck();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0xF2;
	ushort length;
	ushort numFrame;
	CNodeInfo* data;
	uchar check = 0x00;
};
#pragma pack(pop)