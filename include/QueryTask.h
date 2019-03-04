 ///
 /// @file    QueryTask.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-04 00:24:27
 ///
 
#pragma once

#include "CacheManager.h"
#include "MyDict.h"
#include "Threadpool.h"
#include "TcpServer.h"
#include "Nocopyable.h"
#include <queue>
#include <json/json.h>

struct MyResult
{
	string _word;
	int _freq;
	int _dist;
};

struct MyCompare{
	bool operator()(MyResult left, MyResult right){
		if(left._dist != right._dist) return left._dist > right._dist;
		else if(left._freq != right._freq) return left._freq < right._freq;
		else return left._word > right._word;
	}
};

class QueryTask
: sc::Nocopyable
, public Task
{
public:
	QueryTask(const string& query, MyDict &dict, int num, 
			  sc::TcpConnectionPtr conn, CacheManager &mgr)
		: _queryWord(query.substr(0, query.size() - 1)), _dict(dict.getDict())
		, _index(dict.getIndexTable())
		, _num(num)
		, _conn(conn)
		, _cacheMgr(mgr) 
		{
			 if(!isUTF8(_queryWord)){
				 for(auto &c : _queryWord){
					 c = tolower(c);
				 }
			 }
		 }
	void process();

private:
	void queryIndex(const string &sin);
	int getDis(const string &rhs);
	void listResult();
	string toJson(/*const string&*/);

private:
	string _queryWord;
	set<string> _diff;
	vector<pair<string, int>> &_dict;
	map<string, set<int>> &_index;
	size_t _num;
	priority_queue<MyResult, vector<MyResult>, MyCompare> _resultque;
	sc::TcpConnectionPtr _conn;
	CacheManager &_cacheMgr;
};
