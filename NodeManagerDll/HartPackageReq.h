#pragma once
#pragma pack(push)
#pragma pack(1)
#include "HartPackageReqData.h"
class NODEMANAGERDLL_API  CHartPackageReq
{
public:
	CHartPackageReq();
	~CHartPackageReq();
public:
	uchar header[2] = { 0xAD, 0x02 };
	uchar type = 0x2B;
	__int8 length = 28;
	CHartPackageReqData data;
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
	bool valid()
	{
		uchar sum = 0;
		char* ptr = (char*)this;
		for (int i = 0; i < this->getSize() - 1; i++)
		{
			sum += ptr[i];
		}
		return check == sum;
	}
};
#pragma pack(pop)
