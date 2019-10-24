#include <iostream.h>
#include <cstring.h>  // cstring.h defines what a string is, since
							 // C++ by iteself doesn't come with built-in strings.

int main() {
	string FirstTestString;
	string SecondTestString;
	int i;
	for (i=0;i < 5; ++i) {
	cout << "Enter the first string: " << flush;
	cin >> FirstTestString;
	cout << "Enter the second string: " << flush;
	cin >> SecondTestString;

	if (FirstTestString == SecondTestString)
		cout << "Those two strings are the same." << endl;
	else if (FirstTestString < SecondTestString)
		cout << FirstTestString << " is less than " << SecondTestString << endl;
	else if (FirstTestString > SecondTestString)
		cout << SecondTestString << " is less than " << FirstTestString << endl;
	}
	return 0;
}
