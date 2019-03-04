 ///
 /// @file    Config.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-03 21:57:21
 ///

#include "Config.h"

using namespace sc;

Config* Config::_Instance = NULL;

Config::Config(const string & path)
{
	ifstream ifs(path);
	string section;
	string content;
	while(ifs >> section >> content){
		_configMap.insert(make_pair(section, content));
	}
	ifs.close();
}
