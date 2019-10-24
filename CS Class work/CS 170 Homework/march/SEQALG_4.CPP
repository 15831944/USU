//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  Problems for Sequential Algorithms #4
//  This program calculates the average temperature

#include <iostream.h>
#include <math.h>
void main() {
float LotLength = 0;
cout << "Enter the length of the lot: " << flush;
cin >> LotLength;
float LotWidth = 0;
cout << "Enter the width of the lot: " << flush;
cin >> LotWidth;
float HouseLength;
cout << "Enter the length of the house on the lot: " << flush;
cin >> HouseLength;
float HouseWidth;
cout << "Enter the width of the house on the lot: " << flush;
cin >> HouseWidth;

float seconds =
((LotWidth * LotLength) - (HouseLength * HouseWidth)) * 30;

cout << seconds << endl;
int Hours = int(seconds / 3600);
int Minutes = int(seconds / 60) - (Hours * 60);
int Seconds = seconds - (Minutes * 60 + Hours * 3600);

cout << "Time required to mow lawn: (hours:minutes:seconds) "
<< endl << Hours << ":" << Minutes << ":" << Seconds;

}
