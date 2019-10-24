#include <iostream.h>
#include <ctype.h>
#include <fstream.h>

int main() {

	ifstream fin("c:\\cs170\\input3.txt");

	int  NbrUpperCase = 0;      // number of upper case characters seen so far
	char CurrentCharacter;  // current input character

	// process the characters one at a time

	while ( fin.get(CurrentCharacter) ) {

		// got another character

		// determine whether character is upper case or not

		if ( isupper(CurrentCharacter) ) {
			// got an upper case

			++NbrUpperCase;
		}
	}

	// display the count

	cout << "Upper case chars: " << NbrUpperCase << endl;

	// we are all done

	return 0;
}
