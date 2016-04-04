#pragma once
#pragma pack(push)
#pragma pack(1)
#include "common.h"
class NODEMANAGERDLL_API CHartPackageReqData
{
public:
	CHartPackageReqData();
	~CHartPackageReqData();
public:
	uchar UID[12];             //设备唯一ID，程序以该作为唯一标识
	uchar phoneNum[11];        //手机号
	uchar rev1;                //保留数据区
	ushort timeReport;         //该节点心跳包时间，单位100ms 
	uchar rev2[2];             //保留数据区
public:
	int getSize() { return sizeof(*this); }
};
#pragma pack(pop)
