#pragma once

#include <log4cpp/Category.hh>
#include <iostream>
#include <string>
using std::cout;
using std::endl;

using namespace log4cpp;

namespace sc
{

class Mylog
{
public:
	static Mylog * getInstance();
	static void destroy();

	void warn(const char * msg);
	void info(const char * msg);
	void error(const char * msg);
	void debug(const char * msg);

private:
	Mylog();
	~Mylog();

private:
	Category & _root;
	static Mylog * _pInstance;
};

}

#define prefix(msg) string("[").append(__FILE__)\
		.append(":").append(__FUNCTION__)\
		.append(":").append(std::to_string(__LINE__))\
		.append("]").append(msg).c_str()

#define LogWarn(msg) sc::Mylog::getInstance()->warn(prefix(msg))
#define LogInfo(msg) sc::Mylog::getInstance()->info(prefix(msg))
#define LogError(msg) sc::Mylog::getInstance()->Error(prefix(msg))
#define LogDebug(msg) sc::Mylog::getInstance()->Debug(prefix(msg))

