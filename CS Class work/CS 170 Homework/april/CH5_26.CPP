//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-28-97
//  Chapter 5, Problem 5.23
//  Program description

#include <iostream.h>
#include <ctype.h>


void main() {
char CurrChar;
cout << "This program is also stupid, like the last one I did.      " << endl
	  << "Go ahead and type whatever you want.  Press CTRL-Z to stop." << endl;
while (cin.get(CurrChar)) {
	if (isalnum(CurrChar) == 0)
		cout << CurrChar << flush;
}
}

