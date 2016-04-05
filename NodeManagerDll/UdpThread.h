#pragma once
class CUdpThread
{
private:
	CUdpThread();
	~CUdpThread();
private:
	HANDLE hThead;
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