 ///
 /// @file    StrUtility.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-23 05:44:50
 ///
 
#include "StrUtility.h"

int min(int a, int b, int c){
	int tmp = a < b? a: b;
	return tmp < c ? tmp : c;
}

bool isUTF8(const string &one){
	return ( one[0] & 0xe0 && one[1] & 0x80 && one[2] & 0x80);
}

vector<string> Str2Vec(const string& rhs){
	vector<string> ret;
	if(isUTF8(rhs)){
		for(string::size_type col = 0; col < rhs.size(); col+=3){
			string temp = rhs.substr(col, 3);
			ret.push_back(temp);
		}
	}
	else{
		for(string::size_type col = 0; col < rhs.size(); ++col){
			string temp = rhs.substr(col, 1);
			ret.push_back(temp);
		}
	}
	return ret;
}
		
