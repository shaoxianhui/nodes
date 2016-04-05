#pragma once
#include "DisplayPackageReqData.h"
#include "Util.h"
#pragma pack(push)
#pragma pack(1)
class CDisplayPackageReq
{
public:
	CDisplayPackageReq();
	~CDisplayPackageReq();
public:
	uchar header[2] = { 0xAA, 0x55 };
	uchar type = 0x04;
	ushort length;
	uchar cmdtype = 0x02;
	CDisplayPackageReqData* data = NULL;
	uchar check = 0x00;
public:
	void newPackage(CDisplayPackageReqData* node, int num, char* buf, int* len)
	{
		data = new CDisplayPackageReqData[num];
		memcpy(data, node, num);
		length = num * sizeof(CDisplayPackageReqData) + sizeof(cmdtype);
		fillCheck();
		*len = length + 5;
		memcpy(buf, this, 6);
		memcpy(buf + 6, data, num * sizeof(CDisplayPackageReqData));
		buf[*len - 1] = check;

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
		return check = sum;
	}
};
#pragma pack(pop)
