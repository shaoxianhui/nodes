#pragma once
#include "Util.h"
#include "OnOffPackageData.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API COnOffPackageReq
{
public:
	COnOffPackageReq();
	~COnOffPackageReq();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0x04;
	ushort length;
	uchar cmdtype = 0x01;
	COnOffPackageData* data = NULL;
	uchar check = 0x00;
public:
	void toBuf(COnOffPackageData* node, int num, char* buf, int* len)
	{
		if (node != NULL)
		{
			if (data != NULL)
				delete[] data;
			data = new COnOffPackageData[num];
			memcpy(data, node, num * sizeof(COnOffPackageData));
			length = num * sizeof(COnOffPackageData) + sizeof(cmdtype);
			check = fillCheck();
		}
		if (buf != NULL)
		{
			*len = length + 6;

			memcpy(buf, this, 6);
			memcpy(buf + 6, data, getCount() * sizeof(COnOffPackageData));
			check = fillCheck();
			buf[*len - 1] = check;
		}
	}
	void fromBuf(char* buf)
	{
		memcpy(this, buf, 6);

		int num = getCount();
		if (data != NULL)
			delete[] data;
		data = new COnOffPackageData[num];

		memcpy(data, buf + 6, num * sizeof(COnOffPackageData));
		check = buf[getSize() - 1];
	}
	int getCount()
	{
		return (length - sizeof(cmdtype)) / sizeof(COnOffPackageData);
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
		for (int i = 0; i < 6; i++)
		{
			sum += buf[i];
		}
		buf = (char*)data;
		for (int i = 0; i < length - sizeof(cmdtype); i++)
		{
			sum += buf[i];
		}
		return sum;
	}
};
#pragma pack(pop)