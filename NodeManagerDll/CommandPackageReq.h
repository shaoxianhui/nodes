#pragma once
#pragma pack(push)
#pragma pack(1)
#include "common.h"
#include "CommandPackageReqData.h"
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
	uchar check = 0;
public:
	int getSize() { return sizeof(*this); }
	uchar fillCheck()
	{
		uchar sum = 0;
		char* ptr = (char*)this;
		for (int i = 0; i < this->getSize() - 1; i++)
		{
			sum += ptr[i];
		}
		return check = sum;
	}
};
#pragma pack(pop)