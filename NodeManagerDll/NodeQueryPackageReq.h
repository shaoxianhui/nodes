#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CNodeQueryPackageReq
{
public:
	CNodeQueryPackageReq();
	~CNodeQueryPackageReq();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0x02;
	ushort length = 1;
	char rev = 0x00;                  //±£¡Ù
	uchar check = 0x00;
	/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)