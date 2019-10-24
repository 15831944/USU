//P362
//marks
//Mark Salisbury
//P362A81.cpp
/*CS1700 Assignment 8 Functions 

Use value and reference parameters correctly! 

A81. Write a program that will have four functions. The first function 
GetInput will have 4 parameters and will prompt for and get four 
doubles from the keyboard.  The second function swap will have two 
parameters and will swap two doubles that are passed to it. The third 
function Sort4 will have 4 parameters, will call swap when needed and 
will sort (from smallest to largest) 4 doubles that are passed to it. 
The fourth function will be Print4 and will print (to the screen) the 
4 doubles that are passed to it. Have your program (main) consist only 
of calls to these four functions and have your program output to the 
screen the unsorted doubles and the sorted doubles.*/

#include <iostream.h>

void GetInput(double [], const int &);
void Sort4(double [], const int &);
void Print4(const double [], const int &);

void main(void){
	const int ArraySize = 4;
	double D[ArraySize];
	GetInput(D, ArraySize);
	Sort4(D, ArraySize);
	Print4(D, ArraySize);
}

void GetInput(double D[], const int &ASize){
	for (int i = 0; i < ASize; i++){
		cout << "Enter a double: ";
		cin >> D[i];
	}
}
void Sort4(double D[], const int &ASize){
	void Swap(double &a, double &b);
	
	cout << "Sorting array in ascending order..." << endl;

	for (int passes = 1; passes < ASize; passes++){
		for (int i = 0; i < ASize - passes; i++){
			if (D[i] > D[i + 1])
				Swap(D[i], D[i + 1]);
		}
	}
}
void Swap(double &a, double &b){
	double temp = a;
	a = b;
	b = temp;
}
void Print4(const double D[], const int &ASize){
	for (int i = 0; i < ASize; i++)
			cout << "Double" << i + 1 << ": " << D[i] << endl;
}


