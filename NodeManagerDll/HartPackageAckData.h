#pragma once
#pragma pack(push)
#pragma pack(1)
#include "common.h"
class NODEMANAGERDLL_API CHartPackageAckData
{
public:
	CHartPackageAckData();
	~CHartPackageAckData();
public:
	uchar UID[12];             //�豸ΨһID�������Ը���ΪΨһ��ʶ
	uchar phoneNum[11];        //�ֻ���
	uchar useTimeAdd;          //ʹ��timeAdd΢��ʱ�� 
	ushort timeAdd;            //��λ100ms����ʱ�� ��ʾ��������ʱ��Ļ����϶������ӵ�ʱ�䣬��СΪ0����󲻳�����������ʱ�䡣 
	uchar rev2[2];             //����������
public:
	int getSize() { return sizeof(*this); }
};
#pragma pack(pop)
