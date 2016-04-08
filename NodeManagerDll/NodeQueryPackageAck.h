#pragma once
#include "NodeInfo.h"
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CNodeQueryPackageAck
{
public:
	CNodeQueryPackageAck();
	~CNodeQueryPackageAck();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0xF2;
	ushort length;
	ushort numFrame;
	CNodeInfo* data = NULL;
	uchar check = 0x00;
public:
	void toBuf(ushort frame, CNodeInfo* node, int num, char* buf, int* len)
	{
		data = new CNodeInfo[num];
		memcpy(data, node, num);
		length = num * sizeof(CNodeInfo) + sizeof(numFrame);
		numFrame = frame;
		*len = length + 6;
		memcpy(buf, this, 7);
		memcpy(buf + 7, data, num * sizeof(CNodeInfo));
		check = fillCheck();
		buf[*len - 1] = check;
	}
	void fromBuf(char* buf, int len)
	{ 
		int num = (len - 6 - sizeof(numFrame)) / sizeof(CNodeInfo);
		data = new CNodeInfo[num];
		memcpy(this, buf, 7);
		memcpy(data, buf + 7, num * sizeof(CNodeInfo));
		check = buf[len - 1];
	}
	int getSize() 
	{ 
		return length + 6;
	}
	bool valid()
	{
		return check == fillCheck();
	}
private:
	uchar fillCheck()
	{
		uchar sum = 0;
		char* buf = (char*)this;
		for (int i = 0; i < 7; i++)
		{
			sum += buf[i];
		}
		buf = (char*)data;
		for (int i = 0; i < length - sizeof(numFrame); i++)
		{
			sum += buf[i];
		}
		return sum;
	}
};
#pragma pack(pop)