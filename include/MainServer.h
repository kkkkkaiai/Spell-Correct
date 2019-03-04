 ///
 /// @file    MainServer.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-04 06:11:39
 ///
 
#pragma once

#include "CacheManager.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "MyDict.h"
#include "QueryTask.h"
#include "Config.h"
#include "TimerThread.h"
#include "Mylog.h"
#include <iostream>
#include <memory>

using namespace sc;

void onConnection(const TcpConnectionPtr&);
void onMessage(const TcpConnectionPtr&);
void onClose(const TcpConnectionPtr&);

class MainServer
{
	friend void onConnection(const TcpConnectionPtr&);
	friend void onMessage(const TcpConnectionPtr&);
	friend void onClose(const TcpConnectionPtr&);

public:
	MainServer(const string & ConfigPath)
	: _configMap(Config::getInstance(ConfigPath)->getConfigMap())
	, _threadpool(stoi(_configMap["ThreadpoolCap"]),stoi(_configMap["TaskQueSize"]))
    , _tcpserver(_configMap["ServerIP"], (stoi(_configMap["Port"])))
    , _cacheMgr(_configMap["cachePath"])
    , _timer(5, 5, bind(&CacheManager::periodUpdate, &_cacheMgr))
	{}
	
	void start();
	void stop();
private:
	map<string, string> &_configMap;
	Threadpool _threadpool;
	TcpServer _tcpserver;
	MyDict* _dict;
	CacheManager _cacheMgr;
	TimerThread _timer;
};
