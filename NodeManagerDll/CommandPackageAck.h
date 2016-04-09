#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CCommandPackageAck
{
public:
	CCommandPackageAck();
	~CCommandPackageAck();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0xF4;
	ushort length = 1;
	uchar data = 0;
	uchar check = 0x00;
	/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)