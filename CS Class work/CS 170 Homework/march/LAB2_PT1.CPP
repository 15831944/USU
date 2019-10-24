//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  March 17*, 1997    *St. Patrick's Day
//  Lab 2- part 1
//  does algebraic stuff
#include <iostream.h>

int main()
{  // Variable definitions and initializations:
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	cout << "Enter integer value a: " << flush;
	cin >> a;
	cout << "Enter integer value b: " << flush;
	cin >> b;
	cout << "Enter integer value c: " << flush;
	cin >> c;
	cout << "Enter integer value d: " << flush;
	cin >> d;


	// Now cacluate the results.
	d = d * a;
	c = c + (2 * a);
	d = d - (b/c);
	c = c * (b%c);
	b = b/2;

	// Finally display the results.
	cout << "a:"<<a<<endl;
	cout << "b:"<<b<<endl;
	cout << "c:"<<c<<endl;
	cout << "d:"<<d<<endl;

	//Exit indicating lack of errors.
	return 0;
}  //main

