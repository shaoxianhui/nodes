#pragma once
#include "common.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CHartPackageReqData
{
public:
	CHartPackageReqData();
	~CHartPackageReqData();
public:
	uchar UID[12];             //�豸ΨһID�������Ը���ΪΨһ��ʶ
	uchar phoneNum[11];        //�ֻ���
	uchar rev1;                //����������
	ushort timeReport;         //�ýڵ�������ʱ�䣬��λ100ms 
	uchar rev2[2];             //����������
public:
	int getSize() { return sizeof(*this); }
};
#pragma pack(pop)
