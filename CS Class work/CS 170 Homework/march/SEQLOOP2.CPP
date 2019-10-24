//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-31-97
//  Sequential, Decision & Looping Structures #2
//  percent pass/fail

#include <iostream.h>

void main() {

int Grade = 0;
int NumOfPass = 0;
int NumOfFail = 0;

while (Grade != 999) {
	cout << "Enter a grade (or 999 to quit): " << flush;
	cin >> Grade;
	if (Grade < 60)
		++ NumOfFail;
	else if (Grade > 59 && Grade < 101)
		++ NumOfPass;
}

cout << endl << "Failing percentage is: " <<
		  ((NumOfFail) * 100.0 / (NumOfFail + NumOfPass)) << "%";
cout << endl << "Passing percentage is: " <<
		  ((NumOfPass) * 100.0 / (NumOfFail + NumOfPass)) << "%";

}

