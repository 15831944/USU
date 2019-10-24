//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  5-DD-97
//  Chapter x, Problem x.xx
//  Program description
/* 2.    Write a function named Reduce which takes the integer numerator
and denominator of a fraction and reduces the fraction, changing the
numerator and denominator (reference parameters) as necessary.  Write
a program that uses this function.  A sample run could look like.

Enter the numerator:  4
Enter the denominator:  6

The reduced fraction is 2/3
*/

#include <iostream.h>

int GCF(int Numerator,int Denominator);
void LowestForm(int &Numerator, int &Denominator);

void main() {
cout << "This program reduces fractions." << endl
	  << "Enter the numerator: " << flush;
int Numerator;
cin >> Numerator;
int Denominator;

do {
cout << "Enter the denominator: " << flush;
cin >> Denominator;
if (Denominator == 0)
	cout << "The denominator cannot be 0.  Try again." << endl;
} while (Denominator == 0);

LowestForm(Numerator, Denominator);
cout << "The reduced fraction is: "
	  << Numerator << flush;
if (Denominator != 1)
cout << "/" << Denominator << endl;

}


int GCF(int n1,int n2) {
	if (n1 % n2 == 0)
		return n2;
	else
		return GCF(n2, n1 % n2);
}

void LowestForm (int &Numerator, int &Denominator) {
	int Divisor;
	if (Numerator < Denominator) {
		Divisor = GCF(Numerator, Denominator);
		Numerator = Numerator / Divisor;
		Denominator = Denominator / Divisor;
	}
	else {
		Divisor = GCF(Numerator, Denominator);
		Numerator = Numerator / Divisor;
		Denominator = Denominator / Divisor;
	}
	return;
}

