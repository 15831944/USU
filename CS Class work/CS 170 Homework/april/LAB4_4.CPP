//
// count the number of words in the text.
//

#include <iostream.h>
#include <ctype.h>
#include <fstream.h>

// Typedef required for Borland 4.52 and earlier
typedef int bool;
const bool  true    = 1;
const bool  false   = 0;

int main() {

	ifstream fin("c:\\cs170\\input2.txt");


	char CurrentCharacter;        // current character being processed
	int NumberWords = 0;          // number of words so far
	bool InBetweenWords = true;  // is current character part of a word

	// process the characters one at a time.  must read all characters
	// including whitespace

	while (fin.get(CurrentCharacter)) {

		// determine whether character is whitespace or part of a word

		if ( isspace(CurrentCharacter) )  // character is whitespace

			InBetweenWords = true;

		else { // character is part of a word

			// determine whether its the start of a word

			if ( InBetweenWords ) { // found a new word

				InBetweenWords = false;
				++NumberWords;
			}
		}
	}

	// display the count

	cout << "Words: " << NumberWords << endl;

	return 0;
}
