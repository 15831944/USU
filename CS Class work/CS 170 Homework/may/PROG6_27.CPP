//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  5-01-97
//  Chapter 6, Problem 6.27
//  Program description

#include <iostream.h>

void MakeChange(float Amount);
void main() {
float Amount;
cout << "Enter an amount of money.  This program will output " << endl
	  << "the change for this amount." << endl;
cin >> Amount;
MakeChange(Amount);
}

void MakeChange(float Amount) {
int TotalCents = Amount * 100;
int Dollars = TotalCents / 100;
TotalCents = TotalCents % 100;
int Quarters = TotalCents / 25;
TotalCents = TotalCents % 25;
int Dimes = TotalCents / 10;
TotalCents = TotalCents % 10;
int Nickels = TotalCents / 5;
TotalCents = TotalCents % 5;
int Cents = TotalCents;
cout << "The change for " << Amount << " is: " << endl
	  << (2*Dollars) << " half dollar(s)," << endl
	  << Quarters << " quarter(s)," << endl
	  << Dimes << " dime(s)," << endl
	  << Nickels << " nickel(s)," << endl
	  << Cents << " and pennie(s)." << endl;
return;
}


