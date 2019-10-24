// 362
// marks
// Mark Salisbury
// P362A13.cpp

#include <iostream.h>

void main(void) {
  int a, b;
  cout << "Enter two integers: ";
  cin >> a >> b;
  
  if (a > b) 
	  cout << a << " is larger than " << b << endl;
  else if (b > a)
	  cout << b << " is larger than " << a << endl;
  else if (b == a)
	  cout << "These numbers are equal." << endl;
  
}