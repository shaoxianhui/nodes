#pragma once
#pragma pack(push)
#pragma pack(1)
#include "common.h"
class NODEMANAGERDLL_API CCommandPackageReqData
{
public:
	CCommandPackageReqData();
	~CCommandPackageReqData();
public:
	uint  dispNum;                   //0~0xFFFFFFFF
	uchar validNum;                  //������Чλ���������趨��Чλ������õ���ʾ
	uchar fillStatus;                //ǰ����0��־��0������0��1:��0����Чλ��
	uchar posNum;                    //���ݷ���λ��0~250
	uchar rev;                       //����

};
#pragma pack(pop)
