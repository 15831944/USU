//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  5-7-97
//  Recursive problem #2
// Write a recursive function that returns the value of the following
// recursive definition:
//  f(x,y) = x-y                 if x or y < 0
//  f(x,y) = f(x-1,y)+f(x,y-1)   otherwise
#include <iostream.h>
int f(int x, int y) {
if (x < 0 || y < 0)
	return (x-y);
else
	return (f(x-1,y) + f(x, y-1));
}

void main() {
cout << "Write a recursive function that returns the value" << endl
	  << "of the following recursive definition:           " << endl
	  << "   f(x,y) = x - y                   if x or y < 0" << endl
	  << "   f(x,y) = f(x-1,y) + f(x,y-1)     otherwise    " << endl
	  << " Enter the number 'x': " << flush;
int x;
cin >> x;
cout << " Enter the number 'y': " << flush;
int y;
cin >> y;
cout << "The value of f(x,y) is: " << f(x,y);
}
