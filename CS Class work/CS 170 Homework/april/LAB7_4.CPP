#include <iostream.h>
#include <ctype.h>
#include <cstring.h>
#include <fstream.h>

typedef int bool;
const bool  true    = 1;
const bool  false   = 0;

int main(void) {

	// count the number of characters, words, and lines

	// input variables

	string FileName;
	cout << "Enter the name of the file to read: " << flush;
	cin >> FileName;

	ifstream fin(FileName.c_str());

	char CurrentCharacter;

	// output variables

	int NbrChars = 0;
	int NbrWords = 0;
	int NbrLines = 0;

	// helping variables

	bool InBetweenWords = true;  // keeps track whether current
										  // character is part of a word


	// process the characters one at a time.  must read all characters
	// including whitespace

	while (fin.get(CurrentCharacter)) {

		// found another character

		++NbrChars;

		// determine whether character is whitespace or part of a word

		if ( isspace(CurrentCharacter) ) { // character is whitespace

			InBetweenWords = true;

			if (CurrentCharacter == '\n') {

				// found end of another line

				++NbrLines;
			}
		}
		else { // character is part of a word

			// determine whether its the start of a word

			if ( InBetweenWords ) { // found a new word

				InBetweenWords = false;
				++NbrWords;
			}
		}
	}

	// display the counts

	cout << "Chars: " << NbrChars << endl
	 << "Words: " << NbrWords << endl
	 << "Lines: " << NbrLines << endl ;

	// we are all done

	return 0;
}
