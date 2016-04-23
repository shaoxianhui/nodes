#pragma once
#include "common.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CHartPackageAckData
{
public:
	CHartPackageAckData();
	~CHartPackageAckData();
public:
	uchar UID[12];             //设备唯一ID，程序以该作为唯一标识
	uchar phoneNum[11];        //手机号
	uchar useTimeAdd = 0;      //使用timeAdd微调时间 
	ushort timeAdd = 0;        //单位100ms，该时间 表示在心跳包时间的基础上额外增加的时间，最小为0，最大不超过心跳包的时间。 
	uchar rev2[2];             //保留数据区
public:
	int getSize() { return sizeof(*this); }
};
#pragma pack(pop)
