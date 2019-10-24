//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-30-97
//  Chapter 5
//  fun learning functions #1

#include <iostream.h>
#include <bool.h>

char GetChar ();
bool IsVowel (char ch);

void main() {
	cout << "Enter a character: " << flush;
	char Character = GetChar();
	if (IsVowel(Character))
		cout << Character << " is a vowel." << endl;
	else
		cout << Character << " is not a vowel." << endl;
}

// get a char
char GetChar () {
	char c;
	cin.get(c);
	return c;
}

// get a number
bool IsVowel (char ch) {
	switch (ch) {
	case 'a': case'A':
	case 'e': case'E':
	case 'i': case'I':
	case 'o': case'O':
	case 'u': case'U':
		return true;
	default:
		return false;
	}
}

