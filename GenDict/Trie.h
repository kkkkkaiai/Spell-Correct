 ///
 /// @file    Trie.h
 /// @author  WarrenC(Chenkai0130@outlook.com)
 /// @date    2019-02-27 08:07:51
 ///
 
#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#define MAX 26
using namespace std;

typedef struct node{
	struct node *next[MAX];
	int num;
}Node;

class Trie{
public:
	Trie()
		: root(new Node)
	{
		for(int i = 0; i < MAX; ++i)
			root->next[i] = NULL;
		root->num = 0;
	}
	void read(const string &filename);
	void list(const string &filename);

private:
	Node *root;
};
