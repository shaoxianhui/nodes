#pragma once
#pragma pack(push)
#include "common.h"
class NODEMANAGERDLL_API CSuccessPackageAck
{
public:
	CSuccessPackageAck();
	~CSuccessPackageAck();
public:
	uchar header[2] = { 0xAD, 0x02 };
	uchar type = 0xA1;                            
	__int8 length = 1;
	uchar rev = 0;                                //0-开机 1-关机
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
