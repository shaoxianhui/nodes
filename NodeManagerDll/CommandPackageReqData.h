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
	uchar validNum = 0;                  //数据有效位数，超过设定有效位数不会得到显示
	uchar fillStatus = 0;                //前导补0标志，0：不补0，1:补0到有效位数
	uchar posNum = 0;                    //数据分区位置0~250
	uchar rev;                           //保留
};
#pragma pack(pop)
