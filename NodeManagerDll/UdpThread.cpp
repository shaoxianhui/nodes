#include "stdafx.h"
#include "UdpThread.h"
#include "uv.h"
#include "task.h"
#include "HartPackageReq.h"
#include "AllNodes.h"
#include "HartPackageAck.h"
#include "Log.h"
#include "common.h"
#include "NodeInfoList.h"
#include "SwitchPackageReq.h"
#include "SuccessPackageAck.h"
#include "ErrorPackageAck.h"
#include "CommandPackageReq.h"
#include "OnOffPackageReq.h"
#include "DisplayPackageReq.h"
#include "NodeInfoWithSocket.h"
extern int GPRSPort;
extern bool isStart;
static uv_udp_t udp_server;
static uv_loop_t loop;
static void alloc_cb(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) 
{
	static char slab[65536];
	buf->base = slab;
	buf->len = sizeof(slab);
}

static void sv_send_cb(uv_udp_send_t* req, int status) 
{
	CLog::GetInstance()->funLog("发送数据回调！");
	free(req);
}

static void sv_recv_cb(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags)
{
	if (nread <= 0 || isStart == FALSE)
		return;
	CLog::GetInstance()->funLog(CUtil::SockaddrToString(addr));
	switch ((uchar)rcvbuf->base[2])
	{
		//心跳
#ifdef _DEBUG
		case '1':
#endif // _DEBUG
		case 0x2B:
		{
			CHartPackageReq req;
			req.fromBuf(rcvbuf->base);
#ifndef _DEBUG
			if (req.valid() == TRUE)
#endif // _DEBUG
			{
				// 插入或者更新节点信息
				bool insert_or_update = CAllNodes::GetInstance()->insertNode(&req, addr);
				//申请发送请求
				uv_udp_send_t* send_req;
				send_req = (uv_udp_send_t*)malloc(sizeof *send_req);
				//响应包
				CHartPackageAck ack;
				memcpy(&ack.data, &req.data, req.data.getSize());
				if (insert_or_update == true)
				{
					ack.data.useTimeAdd = 1;
					ack.data.timeAdd = rand() % (HART_CYCLE / 100);
				}
				else
				{
					ack.data.useTimeAdd = 0;
					ack.data.timeAdd = 0;
				}

				//初始化buf
				uv_buf_t sndbuf;
				sndbuf = uv_buf_init(ack.toBuf(), ack.getSize());
				//发送响应包
				uv_udp_send(send_req, handle, &sndbuf, 1, (struct sockaddr*) addr, sv_send_cb);
			}
			break;
		}
		//正确数据包
		case 0xA1:
		{
			CSuccessPackageAck ack;
			ack.fromBuf(rcvbuf->base);
			if (ack.valid() == TRUE)
			{
				// 插入或者更新节点信息
				CNodeInfoWithSocket* node = CAllNodes::GetInstance()->findNodeBySocket(addr);
				if (node != NULL)
					node->info.setSuccess();
			}
			break;
		}
		//错误数据包
		case 0xA0:
		{
			CErrorPackageAck ack;
			ack.fromBuf(rcvbuf->base);
			if (ack.valid() == TRUE)
			{
				CNodeInfoWithSocket* node = CAllNodes::GetInstance()->findNodeBySocket(addr);
				if(node != NULL)
					node->info.setSuccess();
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

DWORD WINAPI UdpThreadProc(LPVOID lpParam)
{
	uv_loop_init(&loop);
	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", GPRSPort, &addr);
	uv_udp_init(&loop, &udp_server);
	uv_udp_bind(&udp_server, (const struct sockaddr*) &addr, 0);
	uv_udp_recv_start(&udp_server, alloc_cb, sv_recv_cb);
	uv_run(&loop, UV_RUN_DEFAULT);
	return 0;
}

CUdpThread::CUdpThread()
{
	isStart = TRUE;
	hThread = CreateThread(NULL, 0, UdpThreadProc, NULL, 0, &dwThreadID);
}

CUdpThread::~CUdpThread()
{
	
}

void CUdpThread::Stop()
{
	CLog::GetInstance()->funLog("关闭UDP监听！");
	isStart = FALSE;
}

void CUdpThread::Start()
{
	CLog::GetInstance()->funLog("开启UDP监听！");
	isStart = TRUE;
}

NODEMANAGERDLL_API void NodeCmdSend(CNodeInfo* nodeInfo, uchar type, ushort dataLen, uchar *ptrData)
{
	switch (type)
	{
	case 0x01:
	{
		CNodeInfoWithSocket* info = CAllNodes::GetInstance()->findNodeByUID(nodeInfo->UID);
		if (info != NULL)
		{
			uv_udp_send_t* send_req = new uv_udp_send_t;
			CSwitchPackageReq req;
			req.sw = ptrData[0];
			uv_buf_t buf;
			buf = uv_buf_init(req.toBuf(), req.getSize());
			uv_udp_send(send_req, &udp_server, &buf, 1, (const struct sockaddr*) &info->addr, sv_send_cb);
			info->info.setFail();
		}
		break;
	}
	case 0x02:
	{
		CNodeInfoWithSocket* info = CAllNodes::GetInstance()->findNodeByUID(nodeInfo->UID);
		if (info != NULL)
		{
			uv_udp_send_t* send_req = new uv_udp_send_t;
			CCommandPackageReq req;
			memcpy(&req.data, ptrData, dataLen);
			uv_buf_t buf;
			buf = uv_buf_init(req.toBuf(), req.getSize());
			uv_udp_send(send_req, &udp_server, &buf, 1, (const struct sockaddr*) &info->addr, sv_send_cb);
			info->info.setFail();
		}

		break;
	}
	}
}

void TCPOnOffNodeCmdSend(COnOffPackageReq* req)
{
	COnOffPackageData* data = req->data;
	int count = req->getCount();
	for (int i = 0; i < count; i++)
	{
		CNodeInfoWithSocket* info = NULL;
		if (data[i].useSN == 1)
		{
			info = CAllNodes::GetInstance()->findNodeBySN(data[i].SN);
		}
		else
		{
			info = CAllNodes::GetInstance()->findNodeByUID(data[i].UID);
		}
		if (info != NULL)
		{
			uv_udp_send_t* send_req = new uv_udp_send_t;
			CSwitchPackageReq req;
			req.sw = data[i].sw;
			uv_buf_t buf;
			buf = uv_buf_init(req.toBuf(), req.getSize());
			uv_udp_send(send_req, &udp_server, &buf, 1, (const struct sockaddr*) &info->addr, sv_send_cb);
			info->info.setFail();
		}
	}
}

void TCPDisplayNodeCmdSend(CDisplayPackageReq* req)
{
	CDisplayPackageReqData* data = req->data;
	int count = req->getCount();
	for (int i = 0; i < count; i++)
	{
		CNodeInfoWithSocket* info = NULL;
		if (data[i].useSN == 1)
		{
			info = CAllNodes::GetInstance()->findNodeBySN(data[i].SN);
		}
		else
		{
			info = CAllNodes::GetInstance()->findNodeByUID(data[i].UID);
		}
		if (info != NULL)
		{
			uv_udp_send_t* send_req = new uv_udp_send_t;
			CCommandPackageReq req;
			memcpy(&req.data, &data[i].disp, sizeof(data[i].disp));
			uv_buf_t buf;
			buf = uv_buf_init(req.toBuf(), req.getSize());
			uv_udp_send(send_req, &udp_server, &buf, 1, (const struct sockaddr*) &info->addr, sv_send_cb);
			info->info.setFail();
		}
	}
}