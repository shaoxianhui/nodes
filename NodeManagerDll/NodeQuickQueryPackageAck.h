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
	void toBuf(ushort frame, uchar* quickTable, int num, char* buf = NULL, int* len = NULL)
	{
		if (quickTable != NULL)
		{
			if (data != NULL)
				delete[] data;
			data = new uchar[num];
			memcpy(data, quickTable, num);
			length = (ushort)(num * sizeof(uchar) + sizeof(numFrame));
			numFrame = frame;
		}
		if (buf != NULL)
		{
			*len = length + 6;
			memcpy(buf, this, 7);
			memcpy(buf + 7, data, getCount() * sizeof(char));
			check = fillCheck();
			buf[*len - 1] = check;
		}
	}
	void fromBuf(char* buf)
	{
		memcpy(this, buf, 7);

		int num = getCount();
		if (data != NULL)
			delete[] data;
		data = new uchar[num];

		memcpy(data, buf + 7, num * sizeof(uchar));
		check = buf[getSize() - 1];
	}
	int getCount()
	{
		return (length - sizeof(numFrame)) / sizeof(uchar);
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
