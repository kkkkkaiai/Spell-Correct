 ///
 /// @file    test.cc
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-28 04:44:31
 ///
 
#include "DicProducer.h"
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	string libpath = "./lib/";
	string outpath = "../../../data/";
	DicProducer myDict(libpath, outpath);
	myDict.genCN();
	myDict.genEN();
	myDict.outPut();
	cout << "finished" << endl;
}
