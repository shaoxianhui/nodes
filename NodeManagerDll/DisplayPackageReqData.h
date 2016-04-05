#pragma once
#include "Util.h"
#include "CommandPackageReqData.h"
#pragma pack(push)
#pragma pack(1)
class CDisplayPackageReqData
{
public:
	CDisplayPackageReqData();
	~CDisplayPackageReqData();
public:
	uchar UID[12];          //设备唯一ID
	uchar phoneNum[11];     //手机号
	uchar useSN;	        //0-
	uint  SN;
	CCommandPackageReqData disp;
};
#pragma pack(pop)