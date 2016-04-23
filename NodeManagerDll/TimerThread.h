#pragma once
class CTimerThread
{
private:
	CTimerThread();
	~CTimerThread();
private:
	HANDLE hThread;
	DWORD  dwThreadID;
public:
	static CTimerThread* GetInstance()
	{
		static CTimerThread instance;
		return &instance;
	}
};

