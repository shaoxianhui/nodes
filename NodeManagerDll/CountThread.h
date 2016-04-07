#pragma once
class CCountThread
{
public:
	CCountThread();
	~CCountThread();
private:
	HANDLE hThead;
	DWORD  dwThreadID;
	int veri_count;
public:
	static CCountThread* GetInstance()
	{
		static CCountThread instance;
		return &instance;
	}
	bool up()
	{
		if (veri_count++ > 10)
			return false;
		else
			return true;
	}
	int get()
	{
		return veri_count;
	}
	void zero()
	{
		veri_count = 0;
	}
};

