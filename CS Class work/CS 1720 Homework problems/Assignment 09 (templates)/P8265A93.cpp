//Mark Salisbury
//marks
//P8265A93.cpp
//CS 1720
/*
CS1720 Assignment 9
A93. Repeat A92 but use template functions for the sort, swap and 
print.

Turn in one .cpp file.
*/


#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template <class T>
void sort(T *array[], int elements){
	bool noswap = true;
	for (int i = 0; i < elements; i++){
		noswap = true;
		for (int j = 0; j < elements - 1 - i; j++){
			if (*array[j] > *array[j+1]){
				swap(array[j], array[j + 1]);
				noswap = false;
			}
		}
		if (noswap == true)
			break;
	}
}

template <class T>
void fillArray(T array[], T *thisArray[], int elements){
	for (int i = 0; i < elements; i++){
		array[i] = T(rand() % 100 + double(rand() % 1000) / 1000.0);
		thisArray[i] = &array[i];
	}
}

template <class T>
void printArray(T *array[], int elements){

	cout << setprecision(2) << setiosflags(ios::fixed | ios::showpoint | ios::left);
	for (int i = 0; i < elements; i++)
		cout <<setw(10) << *array[i];
}

void main(){
	string aStrings[] = { "This","is","a","sentence","with","eight","beautiful","words"};
	string *aStringsPtr[8];
	for (int i = 0; i < 8; i++)
		aStringsPtr[i] = &aStrings[i];
	cout << "Original array: " << endl;
	printArray(aStringsPtr, 8);
	cout << "Sorting array..." << endl;
	sort(aStringsPtr, 8);
	cout << "Sorted array:" << endl;
	printArray(aStringsPtr, 8);
}