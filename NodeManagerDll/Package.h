#pragma once
#include "common.h"
class NODEMANAGERDLL_API CPackage
{
public:
	CPackage();
	~CPackage();
public:
	virtual int getSize() { return sizeof(*this); }
	uchar fillCheck()
	{
		uchar sum = 0;
		char* ptr = (char*)this;
		for (int i = 0; i < this->getSize() - 1; i++)
		{
			sum += ptr[i];
		}
		return sum;
	}
};

