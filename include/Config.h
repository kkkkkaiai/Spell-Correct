 ///
 /// @file    Config.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-03 21:50:21
 ///
 
#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

namespace sc
{

class Config
{
public:
	static Config* getInstance(const string& rhs){
		if(!_Instance){
			_Instance = new Config(rhs);
		}
		return _Instance;
	}
	
	void Delete(){
		if(_Instance)
			delete _Instance;
	}

	map<string, string> &getConfigMap() { return _configMap; }

private:
	Config(const string&);
	~Config() {}
private:
	static Config* _Instance;
	string _filepath;
	map<string, string> _configMap;
};

}
