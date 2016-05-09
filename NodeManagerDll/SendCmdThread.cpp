#include "stdafx.h"
#include "SendCmdThread.h"
#include "uv.h"
#include "task.h"
#include "Log.h"
#include "common.h"
#include "AllNodes.h"
static uv_timer_t repeat;
static uv_loop_t loop;

static void repeat_cb(uv_timer_t* handle)
{
	CAllNodes::GetInstance()->sendCmd();
}

DWORD WINAPI SendCmdThreadProc(LPVOID lpParam)
{
	uv_loop_init(&loop);
	uv_timer_init(&loop, &repeat);
	uv_timer_start(&repeat, repeat_cb, 5000, 5000);
	uv_run(&loop, UV_RUN_DEFAULT);
	return 0;
}

CSendCmdThread::CSendCmdThread()
{
	hThread = CreateThread(NULL, 0, SendCmdThreadProc, NULL, 0, &dwThreadID);
}


CSendCmdThread::~CSendCmdThread()
{
}
