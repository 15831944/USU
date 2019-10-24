//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  5-DD-97
/*
1.  Write a function using reference parameters that returns the
square and cube of an integer parameter.  Write a program that uses
this function.
*/
#include <iostream.h>

void SquareCube(int Num, int &Square, int &Cube) {
	Square = Num * Num;
	Cube = Square * Num;
	return;
}

void main() {
	cout << "This program will tell you the " << endl
		  << "square and cube of a number." << endl
		  << "Enter a number: " << flush;
	int Num;
	cin >> Num;
	int Square;
	int Cube;
	SquareCube (Num, Square, Cube);
	cout << "The square is: " << Square << endl
		  << "The cube is:   " << Cube << endl;
}
