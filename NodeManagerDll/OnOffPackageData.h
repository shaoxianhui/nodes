#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API COnOffPackageData
{
public:
	COnOffPackageData();
	~COnOffPackageData();
public:
	uchar UID[12];          //�豸ΨһID
	uchar phoneNum[11];     //�ֻ���
	uchar useSN;	        //0-
	uint  SN;
	uchar sw;
};
#pragma pack(pop)