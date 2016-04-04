#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CSitchPackageReq
{
public:
	CSitchPackageReq();
	~CSitchPackageReq();
public:
	uchar header[2] = { 0xAD, 0x02 };
	uchar type = 0x02;
	__int8 length = 1;
	uchar sw;                                //0-开机 1-关机
	uchar check = 0x00;
/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)
