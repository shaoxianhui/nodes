#pragma once
class CCountThread
{
public:
	CCountThread();
	~CCountThread();
private:
	HANDLE hThead;
	DWORD  dwThreadID;
public:
	static CCountThread* GetInstance()
	{
		static CCountThread instance;
		return &instance;
	}
};

