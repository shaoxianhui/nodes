#pragma once
#include "uv.h"
class CTcpTransaction {
public:
	CTcpTransaction() {};
	~CTcpTransaction() {};
public:
	uchar type;
	ushort numFrame;
	int count = 0;
	char  buffer[1024];
	int len;
};
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