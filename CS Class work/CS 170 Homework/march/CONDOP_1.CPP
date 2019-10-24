//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-21-97
//  Problems for Algorithms with conditional Operations #1
//  This program is for employee pay tracking

#include <iostream.h>
#include <math.h>

void main() {
float TotHours = 0.00;
cout << "Enter weekly total hours: " << flush;
cin >> TotHours;
float RegHours = TotHours;
float OverTHours = 0.00;
if (TotHours > 40) {
	OverTHours = TotHours - 40;
	RegHours = 40; }
float PayRate;
cout << "Enter your hourly wage: " << flush;
cin >> PayRate;
long GrossPay = (RegHours + OverTHours * 1.5) * (PayRate * 100);
float Pay = GrossPay / 100 + ((GrossPay % 100) / 100.00);
cout << endl << "Your gross pay is: $" << Pay << endl;
}
