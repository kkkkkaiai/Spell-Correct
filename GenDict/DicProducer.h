 ///
 /// @file    DicProducer.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-28 03:21:42
 ///
 
#pragma once
#include "include/cppjieba/Jieba.hpp"

#include <string>

using std::unordered_map;
using std::string;

const char* const DICT_PATH = "/home/warren/Spell-Correct/GenDict/dict/jieba.dict.utf8";
const char* const HMM_PATH = "/home/warren/Spell-Correct/GenDict/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "/home/warren/Spell-Correct/GenDict/dict/user.dict.utf8";
const char* const IDF_PATH = "/home/warren/Spell-Correct/GenDict/dict/idf.utf8";
const char* const STOP_WORD_PATH = "/home/warren/Spell-Correct/GenDict/dict/stop_words.utf8";


class DicProducer
{
public:
	DicProducer(const string & lib, const string & out)
	: _libpath(lib)
	, _outpath(out)
	{}

	void genEN();
	void genCN();

	void outPut();

private:
	unordered_map<string, int> _cnDict;
	unordered_map<string, int> _enDict;
	string _libpath;
	string _outpath;
};
