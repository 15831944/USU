//Mark Salisbury
//marks
//P8265A92.cpp
//CS 1720
/*
CS1720 Assignment 9

A92. Indirect Selection Sort of Strings. Write a program that uses 
indirect selection sorting to sort an array of strings using the 
string class. To do this, write a function sort that accepts an 
array of pointers to string and an int representing the number of 
elements in the array. Have your sort function sort the array of 
pointers to string based upon the values in the original array of 
strings. Have your sort function call a swap function that swaps 
pointers in the array of pointers.
    Initialize the array of strings internally in your code when 
	the array is declared. The array should contain 8 short strings.
    1. Output the array of strings using a function print that prints
	the unsorted array of strings,  all on one line.
    2. Output the array of strings using a function print that prints
	the unsorted array of strings by dereferencing the addresses in 
	the array of pointers to string.
    3. After sorting the array of pointers, output the array of 
	strings in sorted order using the print function of 2.
    4. Output the array of strings in unsorted order by using the 
	print function of 1.

Turn in one .cpp file.
*/


#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;


/*  this function will give a compiler error if defined here,
so I will use the swap already defined in the string class.
template <class T>
void swap(T *&a, T *&b){
		T *temp = a;
		a = b;
		b = temp;
}
*/

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
	for (int i = 0; i < elements; i++){
		cout <<setw(10) << *array[i];
	}

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


