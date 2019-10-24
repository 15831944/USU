#include <iostream.h>
#include <cstring.h>  // cstring.h defines what a string is, since
                      // C++ by iteself doesn't come with built-in strings.
	                    
int main() {
	cout << "Enter test string 1: " << flush;
	string TestString1;
	cin >> TestString1;
	cout << "Enter test string 2: " << flush;
	string TestString2;
	cin >> TestString2;
	cout << "Enter test string 3: " << flush;
	string TestString3;
	cin >> TestString3;

	// insert your code here
cout << "Combined string is " << "\""
	  << TestString3 + ' ' + TestString2 + ' ' + TestString1
	  << "\"" << endl;

	// we are done
	return 0;
}
