#pragma once
#include "common.h"
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CNodeQuickQueryPackageAckOk
{
public:
	CNodeQuickQueryPackageAckOk();
	~CNodeQuickQueryPackageAckOk();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0x13;
	ushort length = 3;
	ushort numFrame;
	uchar data = 0x00;
	uchar check = 0x00;
	/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)