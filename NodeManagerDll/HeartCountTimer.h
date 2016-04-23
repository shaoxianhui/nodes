#pragma once
extern int maxNode;
class CHeartCountTimer
{
private:
	CHeartCountTimer();
	~CHeartCountTimer();
private:
	HANDLE hThread;
	DWORD dwThreadID;
	int heart_count;
public:
	static CHeartCountTimer* GetInstance()
	{
		static CHeartCountTimer instance;
		return &instance;
	}
	bool up()
	{
		if (heart_count++ > maxNode)
			return false;
		else
			return true;
	}
	int get()
	{
		return heart_count;
	}
	void zero()
	{
		heart_count = 0;
	}
};

