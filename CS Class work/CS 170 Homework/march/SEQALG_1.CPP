//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  Problems for Sequential Algorithms #1
//  This program calculates the average temperature

#include <iostream.h>

void main() {
int MaxTemp = 0;
int MinTemp = 0;
cout << "Enter the maximum temperature: " << flush;
cin >> MaxTemp;
cout << "Enter the mininum temperature: " << flush;
cin >> MinTemp;
cout << "The average temperature was: " << (MaxTemp + MinTemp) / 2;
}
