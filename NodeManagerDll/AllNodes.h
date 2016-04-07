#pragma once
#include <map>
#include "common.h"
#include "NodeInfoWithSocket.h"
#include "HartPackageReq.h"
#include "Util.h"
#include "NodeInfoList.h"
#include <time.h>
using namespace std;
class CAllNodes
{
private:
	map<string, CNodeInfoWithSocket> allNodes;
	uchar quickTable[1024];
private:
	CAllNodes();
	~CAllNodes();
public:
	static CAllNodes* GetInstance()
	{
		static CAllNodes instance;
		return &instance;
	}
	void insertNode(CHartPackageReq* req, uv_udp_t* handle, const sockaddr* addr)
	{
		string uid = CUtil::UIDtoString((char*)req->data.UID);
		NODE_MAP::iterator iter = allNodes.find(uid);
		CNodeInfoWithSocket info;
		memcpy(info.info.UID, req->data.UID, 12);
		memcpy(info.info.phoneNum, req->data.phoneNum, 11);
		if (addr != NULL) info.addr = *addr;
		if (handle != NULL) info.handle = handle;
		if (iter != allNodes.end())
		{
			//¸üÐÂ
			info.info.SN = iter->second.info.SN;
			info.info.allStatus = iter->second.info.allStatus;
		}
		else
		{
			//²åÈë
			info.info.SN = (uint)getCount();
			info.info.setFail();
		}
		info.info.setOnline();
		time(&info.timestamp);
		allNodes[uid] = info;
		handle->data = &allNodes[uid];
	}
	CNodeInfoWithSocket* findNode(uchar UID[12])
	{
		string uid = CUtil::UIDtoString((char*)UID);
		return &allNodes[uid];
	}
	size_t getCount()
	{
		return allNodes.size();
	}
	void fill(CNodeInfoList *ptrNodeInfoList)
	{
		if (ptrNodeInfoList->nodeNum >= 0 && ptrNodeInfoList->nodeInfoList != NULL)
		{
			int num = (int)getCount();
			if (num > 0)
			{
				uint size = min(num, ptrNodeInfoList->nodeNum);
				NODE_MAP::iterator it;
				int count = 0;
				for (it = allNodes.begin(); it != allNodes.end(); it++)
				{
					//it->second.
					/*memcpy(ptrNodeInfoList->nodeInfoList[count].UID, it->second.info.UID, 12);
					memcpy(ptrNodeInfoList->nodeInfoList[count].phoneNum, it->second.info.phoneNum, 11);
					ptrNodeInfoList->nodeInfoList[count]. = it->second.info.SN;
					ptrNodeInfoList->nodeInfoList[count].SN = it->second.info.SN;*/
					ptrNodeInfoList->nodeInfoList[count] = it->second.info;
					if (++count == size)
						break;
				}
				ptrNodeInfoList->nodeNum = size;
				return;
			}
		}
		ptrNodeInfoList->nodeNum = 0;
	}
	void updateQuickTable(CNodeInfo* node)
	{
		quickTable[node->SN / 8] = quickTable[node->SN / 8] | ((node->allStatus & 0x01) << (node->SN % 8));
	}
	void updateStatus()
	{
		for (NODE_MAP::iterator iter = allNodes.begin();iter != allNodes.end();iter++)
		{
			time_t now;
			time(&now);
			if (now - iter->second.timestamp > HART_CYCLE * 2 / 1000)
			{
				iter->second.info.setOffline();
			}
		}
	}
};

