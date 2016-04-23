#include "stdafx.h"
#include "HeartCountTimer.h"
#include "uv.h"
#include "task.h"
#include "Log.h"
#include "common.h"
static uv_timer_t repeat;
static uv_loop_t loop;

static void repeat_cb(uv_timer_t* handle)
{
	CLog::GetInstance()->funLog("ÐÄÌø°üÇåÁã!");
	CHeartCountTimer::GetInstance()->zero();
}

DWORD WINAPI HeartCountTimerThreadProc(LPVOID lpParam)
{
	uv_loop_init(&loop);
	uv_timer_init(&loop, &repeat);
	uv_timer_start(&repeat, repeat_cb, HART_CYCLE / 2, HART_CYCLE / 2);
	uv_run(&loop, UV_RUN_DEFAULT);
	return 0;
}

CHeartCountTimer::CHeartCountTimer()
{
	heart_count = 0;
	hThread = CreateThread(NULL, 0, HeartCountTimerThreadProc, NULL, 0, &dwThreadID);
}


CHeartCountTimer::~CHeartCountTimer()
{
}
