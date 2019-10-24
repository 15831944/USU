//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  Problems for Sequential Algorithms #5
//  This program is for account balances

#include <iostream.h>
#include <math.h>
void main() {
float StartAccntBal = 0.00;
cout << "Enter your account balance at the beginning of the month: " << flush;
cin >> StartAccntBal;
float TotalWithdrawls = 0.00;
cout << "Enter your total withdrawls for the month: " << flush;
cin >> TotalWithdrawls;
float TotalDeposits;
cout << "Enter your total deposits for the month: " << flush;
cin >> TotalDeposits;
float EndAccntBal = StartAccntBal - TotalWithdrawls + TotalDeposits
- (TotalWithdrawls + TotalDeposits) * 0.01;
cout << "Your ending account balance is: " << EndAccntBal << endl;

}
