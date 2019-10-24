//Mark Salisbury
//marks
//P8265A91.cpp
//CS 1720
/*
CS1720 Assignment 9

A91. Indirect Selection Sort of doubles. Write a program that uses indirect selection sorting
to sort an array of random doubles. To do this, write a function sort that accepts an array of
pointers to double and an int representing the number of elements in the array. Have your sort
function sort the array of pointers to double based upon the values in the original array of
doubles. Have your sort function call a swap function that swaps pointers in the array of
pointers.
    Initialize the array of doubles internally in your code when the array is declared.
	The array should contain 8 doubles.
    1. Output the array of doubles using a function print that prints the unsorted array of
	doubles to 2 decimal precision,  all on one line.
    2. Output the array of doubles using a function print that prints the unsorted array of
	doubles by dereferencing the addresses in the array of pointers to double.
    3. After sorting the array of pointers, output the array in sorted order using the print
	function of 2.
    4. Output the array of doubles in unsorted order again by using the print function of 1.

Turn in one .cpp file,
*/

#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip.h>

template <class T>
void swap(T *&a, T *&b){
		T *temp = a;
		a = b;
		b = temp;
}

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

	cout << setprecision(2) << setiosflags(ios::fixed | ios::showpoint);
	for (int i = 0; i < elements; i++){
		cout <<setw(8) << *array[i];
	}
	cout << endl;

}
void main(){
	double adoubles[8];
	double *adoublesPtr[8];
	srand(time(0));
	fillArray(adoubles, adoublesPtr, 8);
	cout << "Original array: " << endl;
	printArray(adoublesPtr, 8);
	cout << "Sorting array..." << endl;
	sort(adoublesPtr, 8);
	cout << "Sorted array:" << endl;
	printArray(adoublesPtr, 8);
}


