//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-31-97
//  Sequential, Decision & Looping Structures #5
//  mx + b = 0

#include <iostream.h>

void main() {
float M = 0.0;
float B = 0.0;
float X = 0.0;
int i = 0;
do {
cout << endl <<
"This program finds x for the equation mx + b = 0." << endl;
cout << "Enter m: " << flush;
cin >> M;
cout << "Enter b: " << flush;
cin >> B;
if (M == 0)
	cout << "No slope. No definite value for x." << endl;
else {
	X = -B / M;
	cout << "The x value satisfying mx + b = 0 is: " << X
	<< endl << "where m = " << M << " and b = " << B << endl;
}
++i;
} while (i < 3);

}


