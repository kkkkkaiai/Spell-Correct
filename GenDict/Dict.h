 ///
 /// @file    Dict.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-27 07:15:18
 ///
 
#pragma once

#include "include/cppjieba/Jieba.hpp"
#include <iostream>
#include "Trie.h"

using namespace std;

const char * const DICT_PATH = "/home/warren/Spell-Correct/GenDict/dict/jieba.dict.utf8";
const char * const HMM_PATH = "/home/warren/Spell-Correct/GenDict/dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "/home/warren/Spell-Correct/GenDict/dict/user.dict.utf8";
const char * const IDF_PATH = "/home/warren/Spell-Correct/GenDict/dict/idf.utf8";
const char * const STOP_WORD_PATH = "/home/warren/Spell-Correct/GenDict/dict/stop_words.utf8";

class Dict
{
public:
	Dict(const string& lib, const string & data)
	: _libPath(lib), _outPath(data) { }

	void genCN();
	void genEN();

	void output();

private:
	map<string, int> _cnDict;
	Trie _enDict;
	string _libPath;
	string _outPath;
};
