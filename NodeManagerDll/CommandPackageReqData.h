#pragma once
#include "common.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CCommandPackageReqData
{
public:
	CCommandPackageReqData();
	~CCommandPackageReqData();
public:
	uint  dispNum = 0;                   //0~0xFFFFFFFF
	uchar validNum = 0;                  //������Чλ���������趨��Чλ������õ���ʾ
	uchar fillStatus = 0;                //ǰ����0��־��0������0��1:��0����Чλ��
	uchar posNum = 0;                    //���ݷ���λ��0~250
	uchar rev;                           //����
};
#pragma pack(pop)
