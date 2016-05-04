#pragma once
#include <string>
using namespace std;
class CNodeInfo;
class CNodeInfoList;
#ifdef NODEMANAGERDLL_EXPORTS
#define NODEMANAGERDLL_API __declspec(dllexport)
#else
#define NODEMANAGERDLL_API __declspec(dllimport)
#endif

#define uchar unsigned char
#define uint unsigned int
#define ushort unsigned short
#define NODE_MAP map<string, CNodeInfoWithSocket>

#pragma pack(push)
#pragma pack(1)
struct NODEMANAGERDLL_API C_CNodeInfo
{
	uchar UID[12];          //�豸ΨһID
	uchar phoneNum[11];     //�ֻ���
	uchar allStatus;	    //bit0:�ڵ�����״̬��ʶ
							//     1 = ���ߣ�0 = ����
							//bit1:���һ�η������ݳɹ�/ʧ�ܱ�ʶ
							//     0 = ʧ�ܣ�1 = �ɹ�
							//bit2~bit7������ֵΪ0
	uint SN;                //�ýڵ��ڿ�ݲ�ѯ�б��λ��ֵ��0~0xFFFFFFFF��
};
struct NODEMANAGERDLL_API C_CNodeInfoList
{
	int nodeNum = 0;
	C_CNodeInfo* nodeInfoList = NULL;
};
#pragma pack(pop)

NODEMANAGERDLL_API void InitGPRS(int GPRSPort, int cmdPort, int maxNode, unsigned char sec[128]);

NODEMANAGERDLL_API void StartGPRS(void);

NODEMANAGERDLL_API void StopGPRS(void);

NODEMANAGERDLL_API void NodeNumRequest(unsigned int *nodeNum);

NODEMANAGERDLL_API void NodeInfoRequest(C_CNodeInfoList *c_ptrNodeInfoList);

NODEMANAGERDLL_API void NodeCmdSend(C_CNodeInfo* c_nodeInfo, unsigned char type, unsigned short dataLen, unsigned char *ptrData);
NODEMANAGERDLL_API string getKey();
#define CommomCode public:\
void fromBuf(char* buf) { memcpy((char*)this, buf, getSize()); } \
char* toBuf() { fillCheck(); return (char*)this; } \
int getSize() { return sizeof(*this); } \
uchar fillCheck()\
{\
	return check = CUtil::CalcCheck((char*)this, getSize());\
}\
bool valid()\
{\
	return check == CUtil::CalcCheck((char*)this, getSize());\
}

#define MAX_NODE_FRAME 35
#define MAX_CHARS_FRAME 960
#define HART_CYCLE 10000 //ms