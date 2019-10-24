//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-19-97
//  Chapter 3 problem 3.29
//  Treasury bills, interest rates

#include <iostream.h>
#include <iomanip.h>
void main() {

cout << "This program calculates the annual interest on\n"
		  "treasury bills, given the denomination of the \n"
		  "bill, the price of the bill, and the period on\n"
		  "the bill.  \n";
float Denomination = 0.0;
cout << "Enter the denomination: " << flush;
cin >> Denomination;
cout << "Enter the price of the bill: " << flush;
float PriceOfBill = 0.0;
cin >> PriceOfBill;
cout << "Enter the period of the bill: (in days) " << flush;
float Period = 0.0;
cin >> Period;
float InterestRate = (Denomination / PriceOfBill -1) * 365 / Period * 100;
cout << setprecision(4) << endl <<
		  "The practical annual interest rate \n"
		  "on this bill is " << InterestRate << " percent.";
}

