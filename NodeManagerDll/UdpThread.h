#pragma once
class CUdpThread
{
private:
	CUdpThread();
	~CUdpThread();
private:
	HANDLE hThread;
	DWORD  dwThreadID;
public:
	static CUdpThread* GetInstance()
	{
		static CUdpThread instance;
		return &instance;
	}
	void Stop();
	void Start();
};