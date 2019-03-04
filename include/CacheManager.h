 ///
 /// @file    CacheManager.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-04 00:14:34
 ///
 
#pragma once

#include "Mylog.h"
#include "Cache.h"

class CacheManager
{
public:
	CacheManager(const string &path)
	: _cacheDiskPath(path) {}
	void initCache();
	Cache<>& getCache();
	string& getPath() { return _cacheDiskPath; }
	void periodUpdate();

private:
	vector<Cache<>> _cacheList;
	map<pthread_t, size_t> _Thread2Cache;
	string _cacheDiskPath;
};
