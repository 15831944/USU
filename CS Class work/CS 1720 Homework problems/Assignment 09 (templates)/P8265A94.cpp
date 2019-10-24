//Mark Salisbury
//marks
//P8265A94.cpp
//CS 1720
/*
A94. Indirect Shuffle. Write a program that uses indirect shuffle to 
shuffle an array of strings using the string class. To do this, write 
a function shuffle that accepts an array of pointers to string and an 
int representing the number of elements in the array. Have your 
shuffle function shuffle the array of pointers to string. Have your 
shuffle function call a swap function that swaps pointers in the 
array of pointers.
    Initialize the array of strings internally in your code when the 
	array is declared. The array should contain 8 short strings.
    1. Output the array of strings using a function print that prints 
	the unshuffled array of strings by dereferencing the addresses in 
	the array of pointers to string.
    2. After shuffling the array of pointers, output the array of 
	strings in shuffled order using the print function of 1.
   3. Output the array of strings in unshuffleed order by using a 
   print function that simple prints the array of strings. This will 
   print the strings in their original order.

Turn in one .cpp file.
*/

#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template <class T>
void shuffle(T *array[], int elements){
	
	for (int i = 0; i < elements; i++){
		swap(array[i], array[ rand() % elements ]);	
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
void printArrayIndirect(T *array[], int elements){

	cout << setprecision(2) << setiosflags(ios::fixed | ios::showpoint | ios::left);
	for (int i = 0; i < elements; i++){
		cout <<setw(10) << *array[i];
	}
}

template <class T>
void printArray(T array[], int elements){

	cout << setprecision(2) << setiosflags(ios::fixed | ios::showpoint | ios::left);
	for (int i = 0; i < elements; i++){
		cout << setw(10) << array[i];
	}

}
void main(){
	string aStrings[] = { "This","is","a","sentence","with","eight","beautiful","words"};
	string *aStringsPtr[8];
	for (int i = 0; i < 8; i++)
		aStringsPtr[i] = &aStrings[i];
	cout << "Original array: " << endl;
	printArrayIndirect(aStringsPtr, 8);
	cout << "Shuffling array..." << endl;
	shuffle(aStringsPtr, 8);
	cout << "Shuffled array:" << endl;
	printArrayIndirect(aStringsPtr, 8);
	cout << "Printing elements of the original array directly:" << endl;
	printArray(aStrings, 8);
}



