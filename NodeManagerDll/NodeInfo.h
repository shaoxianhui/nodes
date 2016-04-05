#pragma once
#include "common.h"
#pragma pack(push)
#pragma pack(1)
class NODEMANAGERDLL_API  CNodeInfo
{
public:
	uchar UID[12];          //�豸ΨһID
	uchar phoneNum[11];     //�ֻ���
	uchar allStatus;	    //bit0:�ڵ�����״̬��ʶ
							//     1 = ���ߣ�0 = ����
							//bit1:���һ�η������ݳɹ�/ʧ�ܱ�ʶ
							//     0 = ʧ�ܣ�1 = �ɹ�
							//bit2~bit7������ֵΪ0
    uint SN;                //�ýڵ��ڿ�ݲ�ѯ�б��λ��ֵ��0~0xFFFFFFFF��
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