#pragma once
#include <map>
#include "common.h"
#include "NodeInfoWithSocket.h"
#include "HartPackageReq.h"
#include "Util.h"
#include "NodeInfoList.h"
#include <time.h>
#include "NodeQueryPackageAck.h"
#include "NodeQuickQueryPackageAck.h"
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
	void insertNode(CHartPackageReq* req, uv_udp_t* handle = NULL, const sockaddr* addr = NULL)
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
			//更新
			info.info.SN = iter->second.info.SN;
			info.info.allStatus = iter->second.info.allStatus;
		}
		else
		{
			//插入
			info.info.SN = (uint)getCount();
			info.info.setFail();
		}
		info.info.setOnline();
		time(&info.timestamp);
		allNodes[uid] = info;
		if(handle != NULL)
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
	int getNodeQueryPackageAck(CNodeQueryPackageAck* ack, int* len)
	{
		int num = (int)getCount();
		num = ceil((float)num / MAX_NODE_FRAME);
		num = min(num, *len);
		CNodeInfo data[MAX_NODE_FRAME];
		ushort numFrame = 0;
		int ret = 0;
		if (num > 0)
		{
			NODE_MAP::iterator it;
			int count = 0;
			for (it = allNodes.begin(); it != allNodes.end(); it++)
			{
				data[count++] = it->second.info;
				if (count == MAX_NODE_FRAME)
				{
					//生成一个包
					ack[numFrame].toBuf(numFrame, data, MAX_NODE_FRAME);
					ret += MAX_NODE_FRAME;
					count = 0;
					numFrame++;
					if (numFrame == num)
						break;
				}
			}
			if (count > 0 && count < MAX_NODE_FRAME && numFrame < num)
			{
				//生成一个不完整包
				ack[numFrame].toBuf(numFrame, data, count);
				ret += count;
				count = 0;
				numFrame++;
			}
			*len = numFrame;
		}
		return ret;
	}
	int getNodeQucikQueryPackageAck(CNodeQuickQueryPackageAck* ack, int* len)
	{
		int node_num = getCount();
		int chars_num = ceil((float)node_num / 8);
		int num = ceil((float)chars_num / MAX_CHARS_FRAME);
		num = min(num, *len);
		ushort numFrame = 0;
		if (num == 1)
		{
			//生成一个包
			ack[numFrame].toBuf(0, quickTable, chars_num);
			*len = 1;
		}
		return node_num;
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

