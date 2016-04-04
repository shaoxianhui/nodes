#include "Log.h"
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/ndc.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/property.h>
#include <log4cplus/loggingmacros.h>

using namespace log4cplus;

CLog::CLog()
{
	log4cplus::initialize();
	SharedFileAppenderPtr fun_append(new DailyRollingFileAppender(LOG4CPLUS_TEXT("Logs/fun.log"), DAILY, true, 5, true));
	SharedFileAppenderPtr node_append(new DailyRollingFileAppender(LOG4CPLUS_TEXT("Logs/nodeInfo.log"), DAILY, true, 5, true));
	fun_append->setLayout(std::auto_ptr<Layout>(new PatternLayout("%D - %m%n")));
	node_append->setLayout(std::auto_ptr<Layout>(new PatternLayout("%D - %m%n")));

	funlog = Logger::getInstance(LOG4CPLUS_TEXT("function"));
	funlog.addAppender(SharedAppenderPtr(fun_append.get()));
	nodelog = Logger::getInstance(LOG4CPLUS_TEXT("nodeInfo"));
	nodelog.addAppender(SharedAppenderPtr(node_append.get()));
}


CLog::~CLog()
{
	log4cplus::Logger::shutdown();
}
