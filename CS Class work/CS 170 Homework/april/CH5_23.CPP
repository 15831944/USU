//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-28-97
//  Chapter 5, Problem 5.23
//  Program description

#include <iostream.h>
#include <math.h>
void main() {
float Start;
int NumOfYears;
cout << "This program determines the percentage rate that will     " << endl
	  << "double an amount of money over a variable number of years." << endl;
cout << "How much money will you start with: " << flush;
cin >> Start;
cout << "How many years: " << flush;
cin >> NumOfYears;
float Rate = M_LN2/NumOfYears*100;
cout << "Then you will have to find a bank with" << endl
	  << "an interest rate of " << Rate << "%" << endl;
}

