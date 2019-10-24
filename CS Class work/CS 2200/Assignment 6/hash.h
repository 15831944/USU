#include <iostream>
#include <string>

using namespace std;

#include "BST.h"
// concatenate the first five letters of a word into a binary number.

class HashTable {
public:
	HashTable();
	BOOL Insert(string H);
	BOOL Remove(string H);
	BOOL IsInTable(string H);
	int  NValuesAtNode(int x);

protected:
	int Hash(string x);
	BinarySearchTree<string> Nodes[37];
};

