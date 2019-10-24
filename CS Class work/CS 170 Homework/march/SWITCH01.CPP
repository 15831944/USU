//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-27-97
//  Switch assignment #1
//  city power bill

#include <iostream.h>

void main() {
cout << "*** City power bill program ***" << endl;
cout << "\nEnter account number (integer value): " << flush;
int AccountNum;
cin >> AccountNum;

cout << endl << "  Code types are: " << endl <<
		  "	R = Residential power rate" << endl <<
		  "	C = Commercial power rate" << endl <<
		  "	I = Industrial power rate" << endl;
cout << "  Enter code type: " << flush;
char Code;
cin >> Code;

int RHours = 0.00;
int CHours = 0.00;
int PeakH = 0.00;
int OffPeakH = 0.00;
float Bill = 0.00;

switch (Code) {
	case 'r': case 'R':
		cout << "\n Enter the number of residential rate hours: " << flush;
		cin >> RHours;
		Bill = 6.00 + 0.052 * RHours;
		break;
	case 'C': case 'c':
		cout << "\n Enter the number of commercial rate hours: " << flush;
		cin >> CHours;
		Bill = 60.00 + ((CHours > 1000.00) ? (CHours - 1000.00): 0) * 0.045;
		break;
	case 'I': case 'i':
		cout << "\n Enter the number of industrial peak rate hours: " << flush;
		cin >> PeakH;
		cout << "\n Enter the number of industrial off-peak rate hours: " << flush;
		cin >> OffPeakH;
		Bill = 76.00 + ((PeakH > 1000.00) ? (PeakH - 1000.00): 0) * 0.065 +
		 40.00 + ((OffPeakH > 1000.00) ? (OffPeakH - 1000.00): 0) * 0.028;
		break;
	default:
		cout << "\nInvalid code type.  Valid code types are R, C, and I." << endl;
}
long TotalCents = Bill * 100;
int Dollars = TotalCents / 100;
int Cents = TotalCents % 100;
float NiceBill = Dollars + Cents / 100.00;

cout << "\nThe monthly cost is: $" << NiceBill;
}



