#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CNodeQuickQueryPackageReq
{
public:
	CNodeQuickQueryPackageReq();
	~CNodeQuickQueryPackageReq();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0x03;
	ushort length = 1;
	char rev = 0x00;                  //����
	uchar check = 0x00;
	/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)