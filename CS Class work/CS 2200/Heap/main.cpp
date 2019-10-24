#include <iostream.h>
#include <stdlib.h>
#include "Heap.h"
#include "Table.h"

template <class T>
bool IsDataInOrder(T array[], int n){
	for (int i = 0; i < n - 1; i++){
		if (array[i] > array[i + 1])
			return false;
	}
	return true;
}

void main(){
	PriorityQueue<int> dataQueue(100);

	cout << "Problem 11.6:  Filling an array with random values, sorting..." << endl;

	int data[100];
	for (int i = 0; i < 100; i++) data[i] = rand() % 20 + 1;

	cout << "Checking array:  The data " << (IsDataInOrder(data, 100) ? "is" : "is not") << " in order." << endl;

	//cout << "Sorting data..." << endl;

	for (i = 0; i < 100; i++) dataQueue.Insert(data[i]);
	
	for (i = 99; i >= 0; i--) dataQueue.Pop(data[i]);

	for (i = 0; i < 100; i++) 
		cout << data[i] << '\t';

	cout << "Checking array:  The data " << (IsDataInOrder(data, 100) ? "is" : "is not") << " in order." << endl;

	Table<int,int> intTable;

	cout << "Exercise 11.1:  Filling a table with random values, sorting..." << endl;

	for (i = 0; i < 100; i++) {
		int r = rand() % 500 + 1;
		intTable.Insert(TableEntry<int, int>(r,r));
	}
	intTable.Traverse();
}

//Homework 4 - due July 10 (or late by July 12)

//Exercise (not Programming Problem) 1

//This will require you to draw 80 trees.
