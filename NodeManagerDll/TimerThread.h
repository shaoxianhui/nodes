#pragma once
class CTimerThread
{
public:
	CTimerThread();
	~CTimerThread();
private:
	HANDLE hThead;
	DWORD  dwThreadID;
public:
	static CTimerThread* GetInstance()
	{
		static CTimerThread instance;
		return &instance;
	}
};

