#pragma once
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API CNodeQuickQueryPackageAck
{
public:
	CNodeQuickQueryPackageAck();
	~CNodeQuickQueryPackageAck();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0xF3;
	ushort length;
	ushort numFrame;
	uchar* data = NULL;
	uchar check = 0x00;
public:
	void newPackage(ushort frame, CNodeInfo* node, int num, char* buf, int* len)
	{
		num = ceil((float)num / 8);
		data = new uchar[num];
		memcpy(data, node, num);
		length = num * sizeof(uchar) + sizeof(numFrame);
		numFrame = frame;
		fillCheck();
		*len = length + 6;
		memcpy(buf, this, 7);
		memcpy(buf + 7, data, num * sizeof(char));
		buf[*len - 1] = check;

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
		return check = sum;
	}
};
#pragma pack(pop)
