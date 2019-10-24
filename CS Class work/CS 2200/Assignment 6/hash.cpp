#include "hash.h"

HashTable::HashTable(){

}

BOOL HashTable::Insert(string H){
	return Nodes[Hash(H)].InsertData(H);	
}

BOOL HashTable::Remove(string H){
	return Nodes[Hash(H)].DeleteNode(H);
}

BOOL HashTable::IsInTable(string H){
	string *T = &H;
	return Nodes[Hash(H)].SearchForNodeData(T);
}

int  HashTable::NValuesAtNode(int x){
	return Nodes[x].GetSize();
}

int HashTable::Hash(string x){
	int value = 0;
	char c;
	for (int i = 0; i < 12 && i < x.length(); i++){
		c = x[i];
		value *= 32;
		value += toupper(c) - 'A';
		value %= 37;
	}
	return value;
}
	
void HashTable::DumbFunction(BinarySearchTree<int> a){ }

// Linkage in Names with File Scope

//HashTable h;
//BinarySearchTree<int> C;