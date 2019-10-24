//  Mark Salisbury
//  529-71-8265
//  2nd hour
//   3-20-97
//  Chapter 2, problem 2.16
//  farenheit - celcius conversions

#include <iostream.h>

void main() {

cout << "Enter the temperature in farenheit: " << flush;
float FTemp;
cin >> FTemp;
cout << FTemp << " degrees farenheit is " << 5.0/9.0*(FTemp-32)
	  << " degrees celcius.";
}
