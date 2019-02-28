 ///
 /// @file    DicProducer.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-28 03:26:41
 ///
 
#include "DicProducer.h"
#include <dirent.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <cctype>
#include <sstream>

using namespace std;


void pure(string &word)
{
	for(auto iter = word.begin(); iter != word.end();){
		if(!isalpha(*iter))
			iter = word.erase(iter);
		else
			++iter;
	}
}

void DicProducer::genCN()
{
	string cn = _libpath + "cn/";
	chdir(cn.data());
	cout << cn << endl;
	DIR* cur = opendir(".");
	struct dirent *entry;
	while((entry = readdir(cur)) != NULL){
		string filename = entry->d_name;
		if(filename != "." && filename != ".."){
			cppjieba::Jieba jieba(
				DICT_PATH,
				HMM_PATH,
				USER_DICT_PATH,
				IDF_PATH,
				STOP_WORD_PATH);
			vector<string> words;
			vector<cppjieba::Word> jiebawords;
			string s;
			ifstream is(filename);
			while(getline(is, s)){
				jieba.CutAll(s, words);
				for(auto c = words.begin(); c != words.end(); ++c){
					if(c->size() >=3){
						_cnDict[*c]++;
					}
				}
			}
			is.close();
		}
	}
	closedir(cur);
}

void DicProducer::genEN()
{
	string en = _libpath + "en/";
	chdir(en.data());
	cout << en << endl;
	DIR * cur = opendir(".");
	struct dirent *entry;
	while((entry = readdir(cur)) != NULL){
		string filename(entry->d_name);
		if(filename != "." && filename != ".."){
			ifstream is(filename);
			string s;
			string result;
			while(getline(is, s)){
				std::istringstream iss(s);
				string word;
				while(iss >> word) {
					pure(word);
					if(_enDict.count(word))
						_enDict[word]++;
					else
						_enDict[word] = 1;
				}
			}
			is.close();
		}	
	}
	closedir(cur);
}

void DicProducer::outPut()
{
	{
		string cnFilepath = _outpath + "cnDict.dat";
		cout << cnFilepath << endl;
		ofstream cn(cnFilepath);
		if(!cn)
		{
			cout << "cnOutERROR" << endl;
		}
		auto cnu_map_it = _cnDict.begin();
		while(cnu_map_it != _cnDict.end()){
			cn << cnu_map_it->first << " " << cnu_map_it->second << endl;
			++cnu_map_it;
		}
		cn.close();
	}

	{
		string enFilepath = _outpath + "enDict.dat";
		cout << enFilepath << endl;
		ofstream en(enFilepath);
		if(!en)
		{
			cout << "enOutERROR" << endl;
			return ;
		}
		auto enu_map_it = _enDict.begin();
		while(enu_map_it != _enDict.end()){
			en << enu_map_it->first << " " << enu_map_it->second << endl;
			++enu_map_it;
		}
		en.close();
	}
}
