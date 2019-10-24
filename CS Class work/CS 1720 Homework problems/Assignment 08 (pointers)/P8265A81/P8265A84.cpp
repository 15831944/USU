//Mark Salisbury
//CS 1720
//P8265A84.cpp
//Assignment 8.4 
/*
A84. Write and test a function max() that is passed an array of n 
pointers to double and returns a pointer to the maximum of the n 
doubles. Initialize the array of doubles using the rand() function 
to produce doubles between 0.0 and 1.0. Put all of your code in one 
file as you did for the first 6 assignments. Submit the .cpp file. 
*/

#include <iostream.h>
#include <stdlib.h>
#include <iomanip.h>
#include <time.h>

#define RAND_MAX	0x7FFF

double * max(double *sourceDouble[], int n){
	double *maxPtr;
	maxPtr = new double;

	*maxPtr = *sourceDouble[0];
	for (int i = 1; i < n; i++){
		if (*sourceDouble[i] > *maxPtr)
			*maxPtr = *sourceDouble[i];
	}
	
	return maxPtr;
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

void main(){
	double *a[10] = {NULL};
	double *bPtr;

	srand(time(0));

	fillarray(a, 10);
	cout << "Array a:" << endl;
	printarray(a, 10);
	cout << "searching for the max number in a..." << endl;
	bPtr = max(a, 10);
	cout << "the maximum number in a is " << *bPtr << endl;
		
}