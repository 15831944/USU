//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-24-97
//  Problems for Algorithms with conditional Operations #5
//  home mortgage

#include <iostream.h>

void main() {
double Mortgage;
do {
cout << "Enter the amount of the mortgage: \n(not to exceed 100,000$) " << flush;
cin >> Mortgage;
} while (Mortgage > 100000.00 || Mortgage < 0.00);

float Deposit = 0.00;
if (Mortgage >= 50000) Deposit = 5000 + 0.25 * Mortgage;
else if (Mortgage >= 25000) Deposit = 1250 + 0.10 * Mortgage;
else if (Mortgage < 25000) Deposit = 0.05 * Mortgage;

cout << "\nYour required deposit is: $" << Deposit;

}
