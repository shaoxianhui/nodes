#pragma once
#include "HartPackageAckData.h"
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CHartPackageAck
{
public:
	CHartPackageAck();
	~CHartPackageAck();
public:
	uchar header[2] = { 0xAD, 0x02 };
	uchar type = 0x2D;
	uchar length = 28;
	CHartPackageAckData data;
	uchar check = 0x00;
/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)
