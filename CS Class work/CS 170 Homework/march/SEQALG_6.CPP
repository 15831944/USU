//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  Problems for Sequential Algorithms #6
//  This program is for employee pay tracking

#include <iostream.h>
#include <math.h>

void main() {
float RegHours = 0.00;
cout << "Enter weekly regular hours: " << flush;
cin >> RegHours;
float OverTHours = 0.00;
cout << "Enter weekly overtime hours: " << flush;
cin >> OverTHours;
float PayRate;
cout << "Enter your hourly wage: " << flush;
cin >> PayRate;
long GrossPay = (RegHours + OverTHours * 1.5) * (PayRate * 100);
float Pay = GrossPay / 100 + ((GrossPay % 100) / 100.00);
cout << endl << "Your gross pay is: $" << Pay << endl;
}
