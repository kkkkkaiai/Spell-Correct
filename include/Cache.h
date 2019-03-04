///
 /// @file    Cache.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-03 23:28:08
 ///
 
#pragma once

#include "MutexLock.h"
#include "Nocopyable.h"

#include <assert.h>

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <class K = string, class D = string>
struct Node
{
	K _query;
	D _jsonfile;
	Node *prev, *next;
	Node(K k, D d)
	: _query(k)
	, _jsonfile(d)
	, prev(NULL)
	, next(NULL) {}
};

template <class K = string, class D = string>
class Cache
{
	friend class CacheManager;
public:
	Cache(size_t size = 10){
		_size = size;
		_head = NULL;
		_tail = NULL;
		_newCacheCnt = 0;
		_isUpdating = false;
		_isSetting = false;
	};
	D get(K);
	void set(K, D);
	void readFromFile(const string&);
	void writeToFile(const string&);
	void setUpdateTag() { _isUpdating = true; }
	void removeUpdateTag() { _isUpdating = false; }
	void waitSet() {
		if(_isSetting){
			while(_isSetting);
		}
		return;
	}
	bool getSettingStatus() { return _isSetting; }

private:
	void remove(Node<K, D>*);
	void setHead(Node<K, D>*);

private:
	size_t _size;
	map<K, Node<K, D>*> _cacheMap;
	int _newCacheCnt;
	Node<K, D> *_head, *_tail;
	Node<K, D> *_entry;
	bool _isUpdating;
	bool _isSetting;
};

template<class K, class D>
D Cache<K, D>::get(K key)
{
	auto it = _cacheMap.find(key);
	if(it != _cacheMap.end()){
		Node<K, D> *node = it->second;
		remove(node);
		setHead(node);
		return node->_jsonfile;
	}
	else
		return D();
}

template<class K, class D>
void Cache<K, D>::set(K key, D data)
{
	if(_isUpdating){
		while(_isUpdating);
	}
	_isSetting = true;
	auto it = _cacheMap.find(key);
	if(it != _cacheMap.end()){
		Node<K, D>* node = it->second;
		node->_jsonfile = data;
		remove(node);
		setHead(node);
	}
	else{
		Node<K, D> *newNode = new Node<K, D>(key, data);
		if(_cacheMap.size() == _size){
			auto toDel = _cacheMap.find(_tail->_query);
			Node<K, D> *todel = _tail;
			remove(_tail);
			delete todel;
			_cacheMap.erase(toDel);
		}
		++_newCacheCnt;
		setHead(newNode);
		_cacheMap[key] = newNode;
	}
	_isSetting = false;
}

template<class K, class D>
void Cache<K, D>::remove(Node<K, D> *node){
	if(node->prev != NULL){
		node->prev->next = node->next;
	}
	else{
		_head = node->next;
	}
	if(node->next != NULL){
		node->next->prev = node->prev;
	}
	else{
		_tail = node->prev;
	}
}


template<class K, class D>
void Cache<K, D>::setHead(Node<K, D> *node){
	node->next = _head;
	node->prev = NULL;
	if(_head != NULL){
		_head->prev = node;
	}
	_head = node;
	if(_tail == NULL){
		_tail = _head;
	}
}



template<class K, class D>
void Cache<K, D>::writeToFile(const string& cachePath){
	ofstream os(cachePath);
	Node<K, D> *cur = _tail;
	while(cur != _head->prev){
		os << cur->_query << " " << cur->_jsonfile << endl;
		cur = cur->prev;
	}
	os.close();
}

template<class K, class D>
void Cache<K, D>::readFromFile(const string& cachePath){
	ifstream is(cachePath);
	K key;
	D data;
	while(is >> key >> data){
		set(key, data);
	}
	_newCacheCnt = 0;
	is.close();
}
