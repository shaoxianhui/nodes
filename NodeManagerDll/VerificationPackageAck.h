#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CVerificationPackageAck
{
public:
	CVerificationPackageAck();
	~CVerificationPackageAck();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0xF1;
	ushort length = 1;
	char cert = 0x00;                  //0-��֤ʧ�� 1-��֤�ɹ�
	uchar check = 0x00;
	/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)