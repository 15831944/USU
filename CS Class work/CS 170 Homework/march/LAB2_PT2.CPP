//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  March 17*, 1997    *St. Patrick's Day
//  Lab 2- part 2
//  does algebraic stuff

#include <iostream.h>

void main() {
int a = 0;
int b = 0;
int c = 0;
int d = 0;
cout << "This program gives you the value of algebraic expressions." << endl;
cout << "The first expression is: (2 * a * a) + (4 * a) - 29" << endl;
cout << "Enter a: " << flush;
cin >> a;
float result1 = ((2.0 * a * a) + (4.0 * a) - 29.0);
cout << "The value of expression1 is: " << result1 << endl;

cout << "The second expression is: (4 * c + a * c) / (3 * b)" << endl;
cout << "Enter a: " << flush;
cin >> a;
cout << "Enter b: " << flush;
cin >> b;
cout << "Enter c: " << flush;
cin >> c;
float result2 = ((4.0 * c + a * c) / (3.0 * b));
cout << "The value of expression2 is: " << result2 << endl;

cout << "The third expression is: " << endl <<
"(10 * b + 4* a) / (3 * c) + (c* b / a) / (4 / d)" << endl;
cout << "Enter a: " << flush;
cin >> a;
cout << "Enter b: " << flush;
cin >> b;
cout << "Enter c: " << flush;
cin >> c;
cout << "Enter d: " << flush;
cin >> d;
float result3 = ((10.0 * b + 4.0* a) / (3.0 * c) + (c* b / a) / (4.0 / d));
cout << "The value of expression3 is: " << result3 << endl;
}

