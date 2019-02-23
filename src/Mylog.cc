#include "Mylog.h"

#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatterLayout.hh>

#include <iostream>
using std::cout;

Mylog * Mylog::_pInstance = NULL;

Mylog * Mylog::getInstance()
{
	if (_pInstance == NULL)
	{
		_pInstance = new Mylog();
	}
	return _pInstance;
}

void Mylog::destroy()
{
	if (_pInstance)
		delete _pInstance;
}

void Mylog::warn(const char * msg)
{
	_root.warn(msg);
}

void Mylog::error(const char * msg)
{
	_root.error(msg);
}

void Mylog::debug(const char * msg)
{
	_root.debug(msg);
}

void Mylog::info(const char * msg)
{
	_root.info(msg);
}

Mylog::Mylog()
: _root(Category::getRoot().getInstance("root"))
{
	PatternLayout * patternlayout1 = new PatternLayout();
	patternlayout1->setConvertionPattern("%d [%p] %m%n");
	PatternLayout * patternlayout2 = new PatternLayout();
	patternlayout2->setConvertionPattern("%d [%p] %m%n");

	OstreamAppender * ostreamAppender = new OstreamAppender("ostreamAppender", &cout);
	ostreamAppender->setLayout(patternlayout1);

	FileAppender * fileAppender = new OstreamAppender("fileAppender", "../log/Server.log);
	fileAppender->setLayout(patternlayout2);

	_root.addAppender(ostreamAppender);
	_root.addAppender(fileAppender);
	_root.serPriority(Priority::DEBUG);
}

Mylog::~Mylog()
{
	Category::shutdown();
}