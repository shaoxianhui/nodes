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
	uchar UID[12];             //�豸ΨһID�������Ը���ΪΨһ��ʶ
	uchar phoneNum[11];        //�ֻ���
	uchar useTimeAdd = 0;      //ʹ��timeAdd΢��ʱ�� 
	ushort timeAdd = 0;        //��λ100ms����ʱ�� ��ʾ��������ʱ��Ļ����϶������ӵ�ʱ�䣬��СΪ0����󲻳�����������ʱ�䡣 
	uchar rev2[2];             //����������
public:
	int getSize() { return sizeof(*this); }
};
#pragma pack(pop)
