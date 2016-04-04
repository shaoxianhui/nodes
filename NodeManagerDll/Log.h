#pragma once
#include <string>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/ndc.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/property.h>
#include <log4cplus/loggingmacros.h>
using namespace std;
using namespace log4cplus;
class CLog
{
private:
	CLog();
	~CLog();
public:
	static CLog* GetInstance()
	{
		static CLog instance;
		return &instance;
	}
private:
	Logger funlog;
	Logger nodelog;
public:
	void funLog(string message)
	{
		LOG4CPLUS_DEBUG(funlog, message);
	}
	void nodeLog(string message)
	{
		LOG4CPLUS_DEBUG(nodelog, message);
	}
};

