//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-9-97
//  CS 170 Program #5 20 Points
//  Caesar Ciphers

#include <iostream.h>
#include <fstream.h>

void main() {

char CurrChar;
int  Rotate;
cout << "This program performs a caesar cipher on a file. \n"
		  "How many letters do you wish to rotate?: " << flush;
cin >> Rotate;
Rotate = Rotate % 26;
ifstream fin ("A:\\APRIL\\CAESAR.TXT");

while (fin.get(CurrChar)) {
	// checks to see if it is a letter
	if ((CurrChar >= 'a' && CurrChar <= 'z') ||
		(CurrChar >= 'A' && CurrChar <= 'Z')) {
		// changes to uppercase if lowercase
		if (CurrChar >= 'a' && CurrChar <= 'z')
			CurrChar = CurrChar + 'A' - 'a';
		// rotates letter
		CurrChar += Rotate;
		// checks for wrap, allows for a rotation > 26 chars
		if (CurrChar > 'Z')
			CurrChar = (CurrChar - 'Z')  + 'A' ;
	}

	cout << CurrChar << flush;
}

}
