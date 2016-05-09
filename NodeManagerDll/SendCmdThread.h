#pragma once
class CSendCmdThread
{
private:
	CSendCmdThread();
	~CSendCmdThread();
private:
	HANDLE hThread;
	DWORD dwThreadID;
public:
	static CSendCmdThread* GetInstance()
	{
		static CSendCmdThread instance;
		return &instance;
	}
};

