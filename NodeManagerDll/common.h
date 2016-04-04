#pragma once
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
NODEMANAGERDLL_API void InitDll(void);

NODEMANAGERDLL_API void InitGPRS(int GPRSPort, int cmdPort, int maxNode, unsigned char sec[128]);

NODEMANAGERDLL_API void StartGPRS(void);

NODEMANAGERDLL_API void StopGPRS(void);

NODEMANAGERDLL_API void NodeNumRequest(unsigned int *nodeNum);

NODEMANAGERDLL_API void NodeInfoRequest(CNodeInfoList *ptrNodeInfoList);

NODEMANAGERDLL_API void NodeCmdSend(CNodeInfo* nodeInfo, unsigned char type, unsigned short dataLen, unsigned char *ptrData);