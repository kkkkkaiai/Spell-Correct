 ///
 /// @file    QueryTask.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-03-04 02:12:31
 ///
 
#include "QueryTask.h"

void QueryTask::process()
{
	if(_queryWord.size() == 0){
		string nonsense = "What do you mean?";
		_conn->sendInLoop(nonsense);
		return ;
	}
	cout << "----------" << pthread_self() << "---------------" << endl;
	cout << "Task Processing Target: " << _queryWord  << " size = " << _queryWord.size() << " sockfd= " << _conn->getSockfd() << endl;
	Cache<> *  curCache = &_cacheMgr.getCache();
	string res;
	cout << "before get" << endl;
	res = curCache->get(_queryWord);
	if(res.size() > 0) {
		cout << "find through Cache"  << endl;
		_conn->sendInLoop(res);
		return;
	}
	string actualWord;
	if(isUTF8(_queryWord)){
		for(string::size_type col = 0; col < _queryWord.size(); col+=3){
			string sing = _queryWord.substr(col, 3);
			queryIndex(sing);

			actualWord += sing;
		}
	}
	else{
		for(string::size_type col = 0; col <_queryWord.size(); ++col){
			string sing = _queryWord.substr(col, 1);
			queryIndex(sing);
			actualWord += sing;
		} 
	}
	cout << endl;
	cout << " resquesize = " << _resultque.size() << " " << endl;
	res = toJson(/*actualWord*/);
	cout << actualWord << " = " << res << endl;
	_conn->sendInLoop(res);
	curCache->set(_queryWord, res);
	cout << "Cache Updated" << endl;
}

void QueryTask::queryIndex(const string& sin){
	auto head = _index[sin];
	for(auto c : head){
		string word = _dict[c].first;
		if(_diff.find(word) != _diff.end())
			continue;
		int freq = _dict[c].second;
		int dist = getDis(word);
		if(dist >= 5)
			continue;
		_diff.insert(word);
		MyResult instance{word, freq, dist};
		_resultque.push(instance);

	}
	cout << sin << " : " << _conn->getSockfd() << " " << pthread_self() <<  " " << _resultque.size() << " " << _queryWord.substr(0, _queryWord.size()) << " |||" << endl;
}

int QueryTask::getDis(const string& rhs){
	vector<string> s1(Str2Vec(_queryWord)), s2(Str2Vec(rhs));
	int len1 = s1.size();
	int len2 = s2.size();
	int **d = new int* [len1 + 1];  
	for(int i = 0; i <= len1; i++)  
		d[i] = new int[len2 + 1];  
	int i,j;  
	for(i = 0; i <= len1; i++)  
		d[i][0] = i;  
	for(j = 0; j <= len2; j++)  
		d[0][j] = j;  
	for(i = 1; i <= len1; i++)  
	{  
		for(j = 1; j <= len2; j++)  
		{  
			int cost= s1[i - 1] == s2[j - 1] ? 0 : 1;  
			int deletion = d[i - 1][j] + 1;  
			int insertion = d[i][j - 1] + 1;  
			int substitution = d[i - 1][j - 1] + cost;  
			d[i][j] = min(deletion, insertion, substitution);  
		}  
	} 
	int ret = d[len1][len2];
	for(int i = 0; i <= len1; i++)  
	{  
		delete[] d[i];  
	}  
	delete[] d;
	return ret;
}


void QueryTask::listResult(){
	cout << "For QueryWord \"" << _queryWord << "\", we find the following lines:" << endl;
	size_t total = _resultque.size() >= _num ? _num : _resultque.size();
	while(total){
		MyResult pend = _resultque.top();
		cout << pend._word << " " << pend._freq << " " << pend._dist << endl;
		_resultque.pop();
		--total;
	}
}


string QueryTask::toJson(/*const string& rhs*/){
	Json::Value root;
	Json::FastWriter writer;
	Json::Value word;
	size_t total = _resultque.size() >= _num ? _num : _resultque.size();
	while(total){
		MyResult pend = _resultque.top();
		_resultque.pop();
		word = pend._word;
		root.append(word);
		--total;
	}

	string json_file = writer.write(root);

	return json_file;
}

