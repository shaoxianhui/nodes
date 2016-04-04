#pragma once
#include "CommandPackageReqData.h"
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CCommandPackageReq
{
public:
	CCommandPackageReq();
	~CCommandPackageReq();
public:
	uchar header[2] = { 0xAD, 0x02 };
	uchar type = 0x2C;
	__int8 length = 8;
	CCommandPackageReqData data;
	uchar check = 0x00;
/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)