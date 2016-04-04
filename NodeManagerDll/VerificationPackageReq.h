#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CVerificationPackageReq
{
public:
	CVerificationPackageReq();
	~CVerificationPackageReq();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0x01;
	ushort length = 128;
	char cert[128] = { 0x00 };
	uchar check = 0x00;
	/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)