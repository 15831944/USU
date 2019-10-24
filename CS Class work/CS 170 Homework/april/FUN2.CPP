//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-30-97
//  Chapter 5
//  fun learning functions #1

#include <iostream.h>
#include <bool.h>

long Factorial(int a);
int GetANumber();

void main() {
	int Num1 = GetANumber();
	long Fac1 = Factorial(Num1);
	cout << "The factorial of " << Num1 << " is: " << Fac1 << endl;
}

// factorial funtion
long Factorial(int a) {
	long Product = 1;
	for (a; a > 1; a--) {
		Product *= a;
	}
	return Product;
}

// get a number
int GetANumber () {
	int Number;
	cout << "Enter an integer: " << flush;
	cin >> Number;
	return Number;
}

