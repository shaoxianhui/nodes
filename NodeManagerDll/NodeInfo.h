#pragma once
#include "common.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CNodeInfo
{
public:
	uchar UID[12];          //设备唯一ID
	uchar phoneNum[11];     //手机号
	uchar allStatus;	    //bit0:节点在线状态标识
							//     1 = 在线，0 = 离线
							//bit1:最近一次发送数据成功/失败标识
							//     0 = 失败，1 = 成功
							//bit2~bit7保留，值为0
    uint SN;                //该节点在快递查询列表的位序值（0~0xFFFFFFFF）
public:
	CNodeInfo();
	~CNodeInfo();
public:
	void setOnline();
	void setOffline();
	void setSuccess();
	void setFail();
	bool isOnline();
	bool isSuccess();
	bool isOnlineAndSuccess();
};
#pragma pack(pop)