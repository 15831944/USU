//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-21-97
//  Problems for Algorithms with conditional Operations #4
//  Pricing codes

#include <iostream.h>

void main() {
float Price;
cout << "Enter article price: " << flush;
cin >> Price;
char PCode;
cout << "Enter the article pricing code: (H, T, Q, Z):" << flush;
cin >> PCode;
if (PCode != 'H' && PCode != 'h' && PCode != 'T' && PCode != 't' &&
	 PCode != 'Q' && PCode != 'q' && PCode != 'Z' && PCode != 'z')
	 cout << "\nInvalid pricing code\n";
cout << "Original price: " << Price << endl;
cout << "Discout amount: " << flush;
float DRate = 0.0;
if (PCode == 'H' || PCode == 'h') DRate = 0.50;
if (PCode == 'T' || PCode == 't') DRate = 0.33;
if (PCode == 'Q' || PCode == 'q') DRate = 0.25;
if (PCode == 'Z' || PCode == 'z') DRate = 0.00;
if (DRate > 0.00) cout << (Price * DRate); else cout << "No discount";
cout << "\nNew discounted price: " << (Price * (1- DRate));

}
