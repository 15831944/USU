// 362
// marks
// Mark Salisbury
// P362A14.cpp

#include <iostream.h>

void main(void) {
  int a, b, c;
  cout << "Enter three integers: ";
  cin >> a >> b >> c;
  
  cout << "Sum is " << a + b + c << endl;
  cout << "Average is " << (a + b + c) / 3 << endl;
  cout << "Product is " << a * b * c << endl;

  if ((a == b) & (b == c))
	cout << "These numbers are equal." << endl;
  else {
	if ((a < b) & (a < c)) 
		cout << a << " is the smallest " << endl;
	else if (b < c)
		cout << b << " is the smallest " << endl;
	else 
		cout << c << " is the smallest " << endl;
  
	if ((a > b) & (a > c)) 
		cout << a << " is the largest " << endl;
	else if (b > c)
		cout << b << " is the largest " << endl;
	else 
		cout << c << " is the largest " << endl;}
}