#pragma once
class CTcpThread
{
private:
	CTcpThread();
	~CTcpThread();
private:
	HANDLE hThread;
	DWORD  dwThreadID;
public:
	static CTcpThread* GetInstance()
	{
		static CTcpThread instance;
		return &instance;
	}
};