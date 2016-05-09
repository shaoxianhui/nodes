#pragma once
class CVeriCountThread
{
private:
	CVeriCountThread();
	~CVeriCountThread();
private:
	HANDLE hThread;
	DWORD  dwThreadID;
	int veri_count;
public:
	static CVeriCountThread* GetInstance()
	{
		static CVeriCountThread instance;
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

