#pragma once
#include <map>
#include "common.h"
#include "NodeInfoWithSocket.h"
#include "HartPackageReq.h"
#include "Util.h"
#include "NodeInfoList.h"
using namespace std;
class CAllNodes
{
private:
	map<string, CNodeInfoWithSocket> allNodes;
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
		}
		else
		{
			//²åÈë
			info.info.SN = (uint)getCount();
		}
		allNodes[uid] = info;
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
};

