//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-4-97
//  CS 170 Program #3 20 Points
//  Phone bills

#include <iostream.h>

void main() {
int StartTime;
int EndTime;

do {    // get starting time
	cout << "Enter the starting time of the phone call (in military time," << endl
		  << "or a 24-hour clock time): " << flush;
	cin >> StartTime;
	if ((StartTime % 100) > 59) cout << "Invalid time" << endl;
} while ((StartTime % 100) > 59);

do {    // get ending time
	cout << "Enter the ending time of the phone call (in military time," << endl
		  << "or a 24-hour clock time): " << flush;
	cin >> EndTime;
	if ((EndTime % 100) > 59) cout << "Invalid time" << endl;
} while ((EndTime % 100) > 59);

int Length = (EndTime / 100 - StartTime / 100) * 60 +
				 (EndTime % 100 - StartTime % 100);

if (EndTime < StartTime) Length = Length + (24 * 60);

cout << "The length of the phone call in minutes was: " << Length << endl;
cout << "The gross cost of the phone call is: $" <<
		(0.4 * Length) << endl;
float NetCost = 0.4 * Length *
	((StartTime > 1800 || StartTime < 800)? 0.50 : 1.0) *
	((Length > 60)? 0.85: 1.0);
NetCost *= 1.04;
cout << "The net cost (discounts and tax) is: $" << NetCost;
}


