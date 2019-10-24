#include <iostream.h>
#include <cstring.h>  // cstring.h defines what a string is, since
                      // C++ by iteself doesn't come with built-in strings.
	                    
int main() {
	cout << "Enter test string: " << flush;
	string TestString;
	cin >> TestString;

	// insert your code here
cout << "\"" << to_lower(TestString) << "\"" << " contains "
	  << TestString.length() << " characters." << endl;

	// we are done
	return 0;
}
