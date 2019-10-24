//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-7-97
//  CS 170 Program #4 20 Points
//  Employee types, wages, etc.

#include <iostream.h>
#include <iomanip.h>

void main() {
int EmpNum;
int EmpTyp;
char* EmpStrings [5][12];
EmpStrings[1][0] = "Salaried";
EmpStrings[2][0] = "Hourly";
EmpStrings[3][0] = "Commission";
EmpStrings[4][0] = "Piece";
int NumEmp;

float Pay;
float Other1;
float Other2;
int i = 0;

cout << "How many employees?: " << flush;
cin >> NumEmp;
Pay = 0.0;
Other1 = 0.0;
Other2 = 0.0;

while (i < NumEmp) {
	cout << endl << "Enter employee number: " << flush;
	cin >> EmpNum;
	EmpTyp = 0;
	cout << endl << "Employee types are: \n"
		  "   1- manager       \n"
		  "   2- hourly        \n"
		  "   3- commissioned  \n"
		  "   4- pieceworkers  \n";

	while (EmpTyp < 1 || EmpTyp > 4) {
		cout << "What is the employee type?: " << flush;
		cin >> EmpTyp;
		if (EmpTyp < 1 || EmpTyp > 4)
		cout << "Invalid Employee type.  Valid types are 1-4." << endl;
	}

	cout << endl;
	cout << setiosflags(ios::left);
	switch(EmpTyp) {
		case 1:
			cout << "Enter weekly salary: " << flush;
			cin >> Pay;
			break;
		case 2:
			cout << "Enter hourly rate: " << flush;
			cin >> Other1;
			cout << "Enter hours worked: " << flush;
			cin >> Other2;
			Pay = (Other2 > 40 ?(40+(Other2-40)*1.5):Other2) * Other1;
			break;
		case 3:
			cout << "Enter gross weekly sales: " << flush;
			cin >> Other1;
			Pay = 250 + 0.057 * Other1;
			break;
		case 4:
			cout << "Enter price per item: " << flush;
			cin >> Other1;
			cout << "Enter number of items produced: " << flush;
			cin >> Other2;
			Pay = Other1 * Other2;
			break;
		default:
			cout << "Invalid employee type.  Valid types are numbers 0-4." << endl;
		}
		cout << setw(12) << "Employee#" << setw(12)
			  << "Type" << setw(12) << "Pay" << setw(12) << "Other info" << endl;
		cout << "------------------------------------------------" << endl;
		cout << setw(12) << EmpNum << setw(12)
			  << EmpStrings[EmpTyp][0] << setw(12) << Pay << "("
			  << Other1 << " " << Other2 << ")"  << endl;
i++;
}
}


