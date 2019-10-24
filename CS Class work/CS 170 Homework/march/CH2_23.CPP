#include <iostream.h>

//  Mark Salisbury
//  Chapter 2- #23
//  This program computes the average of 5 integers

void main() {
const int NumOfInts = 5;
int IntList[NumOfInts];
int i = 0; //increment counter
int sum = 0;

for (i = 1; i <= NumOfInts; i++) {
cout << "Please enter integer # " << i << endl;
cin >> IntList[(i-1)];
sum = IntList[(i-1)]+sum;
}
cout << "The average of " << NumOfInts << " integers is:" << (sum/NumOfInts);
}