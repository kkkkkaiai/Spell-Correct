 ///
 /// @file    StrUtility.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 05:44:50
 ///
 
#ifndef __STR_UTILITY_H__
#define __STR_UTILITY_H__

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int min(int a, int b, int c);

bool isUTF8(const string &one);

vector<string> Str2Vec(const string& rhs);
		
#endif
