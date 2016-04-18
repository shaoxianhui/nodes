#include "stdafx.h"
#include "TimerThread.h"
#include "uv.h"
#include "task.h"
#include "AllNodes.h"
#include "Log.h"

static uv_timer_t repeat;
static uv_loop_t loop;

static void repeat_cb(uv_timer_t* handle)
{
	CLog::GetInstance()->funLog("Timer!");
	CAllNodes::GetInstance()->updateStatus();
}

DWORD WINAPI TimerThreadProc(LPVOID lpParam)
{
	uv_loop_init(&loop);
	uv_timer_init(&loop, &repeat);
	uv_timer_start(&repeat, repeat_cb, HART_CYCLE * 2, HART_CYCLE * 2);
	uv_run(&loop, UV_RUN_DEFAULT);
	return 0;
}

CTimerThread::CTimerThread()
{
	hThead = CreateThread(NULL, 0, TimerThreadProc, NULL, 0, &dwThreadID);
}

CTimerThread::~CTimerThread()
{
}
