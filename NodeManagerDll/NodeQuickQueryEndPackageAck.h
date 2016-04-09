#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CNodeQuickQueryEndPackageAck
{
public:
	CNodeQuickQueryEndPackageAck();
	~CNodeQuickQueryEndPackageAck();
public:
	uchar  header[2] = { 0xAA, 0x55 };
	uchar  type = 0xF3;
	ushort length = 30;
	ushort numFrame = 0xFFFF;
	uint   totalNodeNum;                //��ʾ��������ٸ��ڵ�״̬
	uchar  check = 0;
	/////////////////////////////////////////////////////////////
	CommomCode
};
#pragma pack(pop)