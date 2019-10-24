//Mark Salisbury
//CS 1720
//P8265A82.cpp
//Assignment 8.2
/*
A82. Write and test a function search() that uses pointers to 
search for the address (not the index) of a given integer in a given
array. If the given integer is found, the function returns its address;
otherwise it returns NULL. Initialize the array of int by using the
rand function to produce ints between 0 and 99.  Output the array and 
then prompt for the search value and output the address found in the 
array. Put all of your code in one file as you did for the first 6 
assignments. Submit the .cpp file.  */


#include <iostream.h>
#include <stdlib.h>
#include <iomanip.h>
#include <time.h>

int * search( int *array, int integer, int n ){
	for (int i = 0; i < n; i++){
		if (array[i] == integer)
			return &array[i];
	}
	return NULL;
}

void fillarray(int * array, int n){
	for (int i = 0; i < n; i++)
		array[i] = rand() % 100;
}

void printarray(int * array, int n){
	setiosflags(ios::showpoint | ios::fixed);
	cout << setprecision(6);
	for (int i = 0; i < n; i++)
		cout << setw(8) << array[i] << '\t';
}

void main(){
	int a[10];
	int *bPtr;
	int value;
	
	srand(time(0));
	
	fillarray(a, 10);
	cout << "Array a:" << endl;
	printarray(a, 10);
	
	cout << "Which value should I search the array for? ";
	cin >> value;
	
	bPtr = search(a, value, 10);
	
	if (bPtr == NULL)
		cout << value << " was not found in array a." << endl;
	else
		cout << value << " was found in array a at address " << bPtr << '.' << endl;
	
}
