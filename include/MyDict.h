 ///
 /// @file    MyDict.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-03 22:06:19
 ///
 
#pragma once

#include "StrUtility.h"
#include <map>
#include <set>

using namespace std;

class MyDict
{
public:
	static MyDict* getInstance(const string & p1, const string & p2){
		if(!_Instance)
			_Instance = new MyDict(p1, p2);
		return _Instance;
	}
	void init();
	void initDict();
	void initIndex();
	vector<pair<string, int>> &getDict() { return _dict; }
	map<string, set<int>> &getIndexTable() { return _index; }
	void list();
	static void Delete(){
		if(_Instance)
			delete _Instance;
	}

private:
	MyDict(const string & cnPath, const string & enPath)
	: _enPath(enPath)
	, _cnPath(cnPath) {}
	~MyDict() {}

private:
	string _enPath;
	string _cnPath;
	static MyDict * _Instance;
	vector<pair<string, int>> _dict;
	map<string, set<int>> _index;
};
