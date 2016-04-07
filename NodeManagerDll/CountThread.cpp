#include "stdafx.h"
#include "CountThread.h"
#include "uv.h"
#include "task.h"
#include "AllNodes.h"
#include "Log.h"

static uv_timer_t repeat;
static uv_loop_t loop;
static int veri_count = 0;

static void repeat_cb(uv_timer_t* handle)
{
	CLog::GetInstance()->funLog("Verification Count = 0!");
	veri_count = 0;
}

DWORD WINAPI CountThreadProc(LPVOID lpParam)
{
	uv_loop_init(&loop);
	uv_timer_init(&loop, &repeat);
	uv_timer_start(&repeat, repeat_cb, 60 * 1000, 60 * 1000);
	uv_run(&loop, UV_RUN_DEFAULT);
	return 0;
}

CCountThread::CCountThread()
{
	hThead = CreateThread(NULL, 0, CountThreadProc, NULL, 0, &dwThreadID);
}


CCountThread::~CCountThread()
{
}
