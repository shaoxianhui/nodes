#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CErrorPackageAck
{
public:
	CErrorPackageAck();
	~CErrorPackageAck();
public:
	uchar header[2] = { 0xAD, 0x02 };
	uchar type = 0xA0;                            
	__int8 length = 1;
	uchar rev = 0;                                //0-���� 1-�ػ�
	uchar check = 0;
/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)
