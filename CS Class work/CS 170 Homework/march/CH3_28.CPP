//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-19-97
//  Chapter 3, problem 3.28
//  inches, miles, feet, coversions

#include <iostream.h>

void main() {

cout << "Enter the distance in inches: " << flush;
long TotalInches;
cin >> TotalInches;
int Miles = (TotalInches / (5280.0 * 12.0));
int Feet = (TotalInches / 12) % 5280;
int Inches = TotalInches - (Miles * 5280.0 + Feet) * 12.0;
cout  << "\nIn " << TotalInches << " inches there are \n" <<
Miles << " miles, " <<
Feet	<< " feet, and " << Inches << " inches." << endl;
}
