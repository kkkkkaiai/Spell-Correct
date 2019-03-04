 ///
 /// @file    MainServer.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-04 06:22:15
 ///
 
#include "MainServer.h"

sc::Threadpool *g_threadpool = NULL;
CacheManager *g_cacheMgr = NULL;

void onConnection(const TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
	string loginfo = conn->toString() + " The link was established.";
	LogInfo(loginfo);
	conn->send("Connection Established.");
}

void onMessage(const sc::TcpConnectionPtr &conn)
{
	string query(conn->receive());
	QueryTask* ptask(new QueryTask(query, *MyDict::getInstance("", ""), 5, conn, *g_cacheMgr));
	cout << "QueryTask Added.	sockio = " << conn->getSockfd() << " " << ptask << endl;
	g_threadpool->addTask(ptask);
}

void onClose(const sc::TcpConnectionPtr & conn)
{
	string loginfo = conn->toString() + " close.";
	LogInfo(loginfo);
	cout << conn->toString() << " closed" << endl;
}

void MainServer::start()
{
	LogInfo("Server Started");
	_dict = MyDict::getInstance(_configMap["cnDictPath"], _configMap["enDictPath"]);
	_dict->init();
	_cacheMgr.initCache();
	_timer.start();
	g_threadpool = &_threadpool;
	g_cacheMgr = &_cacheMgr;
	_threadpool.start();
	_tcpserver.setConnectionCallback(&onConnection);
	_tcpserver.setMessageCallback(&onMessage);
	_tcpserver.setCloseCallback(&onClose);
	_tcpserver.start();
}

void MainServer::stop()
{
	_dict->Delete();
	Config::getInstance("asd")->Delete();
	_tcpserver.stop();
	_threadpool.stop();
}

