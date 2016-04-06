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
extern int GPRSPort;
extern bool isStart;
static uv_udp_t udp_server;
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
//static uv_udp_t client;
static void sv_recv_cb(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags)
{
	if (nread <= 0)
		return;
	switch (rcvbuf->base[2])
	{
#ifdef _DEBUG
	case '1':
#endif // DEBUG
	case 0x2B:
	{
		CHartPackageReq req;
		memcpy(&req, rcvbuf->base, req.getSize());
		CAllNodes::GetInstance()->insertNode(&req, handle, addr);
		uv_udp_send_t* send_req;
		uv_buf_t sndbuf;
		send_req = (uv_udp_send_t*)malloc(sizeof *send_req);
		CHartPackageAck ack;
		memcpy(&ack.data, &req.data, req.data.getSize());
		ack.fillCheck();
		sndbuf = uv_buf_init((char*)&ack, ack.getSize());

		//uv_udp_init(uv_default_loop(), &client);
		uv_udp_send(send_req, handle, &sndbuf, 1, (struct sockaddr*) addr, sv_send_cb);
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
	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", GPRSPort, &addr);
	uv_udp_init(uv_default_loop(), &udp_server);
	uv_udp_bind(&udp_server, (const struct sockaddr*) &addr, 0);
	uv_udp_recv_start(&udp_server, alloc_cb, sv_recv_cb);
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	return 0;
}

CUdpThread::CUdpThread()
{
	isStart = TRUE;
	hThead = CreateThread(NULL, 0, UdpThreadProc, NULL, 0, &dwThreadID);
}

CUdpThread::~CUdpThread()
{
	
}

void CUdpThread::Stop()
{
	CLog::GetInstance()->funLog("关闭UDP监听！");
	isStart = FALSE;
	uv_udp_recv_stop(&udp_server);
}

void CUdpThread::Start()
{
	CLog::GetInstance()->funLog("开启UDP监听！");
	isStart = TRUE;
	uv_udp_recv_start(&udp_server, alloc_cb, sv_recv_cb);
}

NODEMANAGERDLL_API void NodeCmdSend(CNodeInfo* nodeInfo, uchar type, ushort dataLen, uchar *ptrData)
{

	uv_udp_send_t* send_req = new uv_udp_send_t;
	switch (type)
	{
	case 0x01:
	{
		CSwitchPackageReq req = CSwitchPackageReq();
		req.sw = ptrData[0];

		uv_buf_t buf;
		buf = uv_buf_init((char*)&req, req.getSize());
		CNodeInfoWithSocket* info = CAllNodes::GetInstance()->findNode(nodeInfo->UID);
		uv_udp_send(send_req, info->handle, &buf, 1, (const struct sockaddr*) &info->addr, sv_send_cb);
		uv_run(uv_default_loop(), UV_RUN_NOWAIT);
		break;
	}
	case 0x02:
	{
		break;
	}
	}
}
