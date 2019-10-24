//Mark Salisbury
//CS 1720
//P8265A81.cpp
//Assignment 8.1
/*
Use pointers in these programs and functions wherever you can.

A81. Write a program that uses a function copy(). The function 
copy uses pointers to copy an array of double. The copy
function will use the new operator to allocate an array of n 
doubles and will returns the address of the new array. Put all
of your code in one file as you did for the first 6 assignments.
Submit the .cpp file.  Initialize the first array of doubles by 
using the rand() function to produce an array of doubles between
0.0 and 1.0. Output the copy of the array using pointer notation.
*/
#include <iostream.h>
#include <stdlib.h>
#include <iomanip.h>
#include <time.h>

#define RAND_MAX	0x7FFF

double * copy(double sourcearray[], int n){
	double *newarray;
	newarray = new double[n]; 
	for (int i = 0; i < n; i++)
		newarray[i] = sourcearray[i];
	
	return newarray;
}

void fillarray(double * array, int n){
	for (int i = 0; i < n; i++)
		array[i] = double(rand()) / double(RAND_MAX);
}

void printarray(double * array, int n){
	setiosflags(ios::showpoint | ios::fixed);
	cout << setprecision(6);
	for (int i = 0; i < n; i++)
		cout << setw(8) << array[i] << '\t';
}

void main(){
	double a[10];
	double *bPtr;

	srand(time(0));

	fillarray(a, 10);
	cout << "Array a:" << endl;
	printarray(a, 10);
	cout << "Array a is being copied to array b..." << endl;
	bPtr = copy(a, 10);
	cout << "Array b:" << endl;
	printarray(bPtr, 10);
	
}
