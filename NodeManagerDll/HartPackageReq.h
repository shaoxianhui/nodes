#pragma once
#include "HartPackageReqData.h"
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CHartPackageReq
{
public:
	CHartPackageReq();
	~CHartPackageReq();
public:
	uchar header[2] = { 0xAD, 0x02 };
	uchar type = 0x2B;
	uchar length = 28;
	CHartPackageReqData data;
	uchar check = 0x00;
/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)
