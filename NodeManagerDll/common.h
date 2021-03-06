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

extern "C" NODEMANAGERDLL_API void InitGPRS(int GPRSPort, int cmdPort, int maxNode, unsigned char sec[128]);

extern "C" NODEMANAGERDLL_API void StartGPRS(void);

extern "C" NODEMANAGERDLL_API void StopGPRS(void);

extern "C" NODEMANAGERDLL_API void StartLog(void);

extern "C" NODEMANAGERDLL_API void StopLog(void);

extern "C" NODEMANAGERDLL_API void NodeNumRequest(unsigned int *nodeNum);

extern "C" NODEMANAGERDLL_API void NodeInfoRequest(CNodeInfoList *ptrNodeInfoList);

extern "C" NODEMANAGERDLL_API void NodeCmdSend(CNodeInfo* nodeInfo, unsigned char type, unsigned short dataLen, unsigned char *ptrData);
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