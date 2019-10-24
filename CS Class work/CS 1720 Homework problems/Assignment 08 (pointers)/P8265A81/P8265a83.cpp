//Mark Salisbury
//CS 1720
//P8265A83.cpp
//Assignment 8.3
/*
A83. Write and test a function that is passed an array of n pointers 
to double and returns a newly created array that contains those n 
double values. Initialize the first array of doubles using the rand 
function to produce doubles between 0.0 and 1.0. Output the new array 
10 numbers per line with 3 decimal place precision. Put all of your 
code in one file as you did for the first 6 assignments. Submit the 
.cpp file. */

#include <iostream.h>
#include <stdlib.h>
#include <iomanip.h>
#include <time.h>

#define RAND_MAX	0x7FFF

double * copy(double *sourceDouble[], int n){
	double *newarray;
	newarray = new double[n]; 
	for (int i = 0; i < n; i++)
		newarray[i] = *sourceDouble[i];
	
	return newarray;
}

void fillarray(double *array[], int n){
	for (int i = 0; i < n; i++){
		array[i] = new double;
		*array[i] = double(rand()) / double(RAND_MAX);
	}
}

void printarray(double *array[], int n){
	setiosflags(ios::showpoint | ios::fixed);
	cout << setprecision(3);
	for (int i = 0; i < n; i++)
		cout << setw(5) << *array[i] << "   ";
}

void printarray(double array[], int n){
	setiosflags(ios::showpoint | ios::fixed);
	cout << setprecision(3);
	for (int i = 0; i < n; i++)
		cout << setw(5) << array[i] << "   ";
}

void main(){
	double *a[10] = {NULL};
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
