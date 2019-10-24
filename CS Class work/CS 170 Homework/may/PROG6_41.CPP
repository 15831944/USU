//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  5-01-97
//  Chapter 6, Problem 6.41
//  Fibonacci Sequence

#include <iostream.h>
#include <math.h>
int Fibonacci(int NumA, int NumB);
void main() {

cout << "This program computes the golden ratio.  No input." << endl;
int NumA = 1;
int NumB = 1;
int NumC = Fibonacci(NumA, NumB);

while (fabs(((float) NumB / NumA) - ((float) NumC / NumB)) >= .0005 ) {
NumA = NumB;
NumB = NumC;
NumC = Fibonacci(NumA , NumB);
}

float Ratio = (float) NumC / NumB;
cout << "The Golden Ratio is: " << Ratio;
}

Fibonacci(int NumA, int NumB) {
return (NumA + NumB);
}


