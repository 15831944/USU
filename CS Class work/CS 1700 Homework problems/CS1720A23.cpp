
#include <iostream.h>
#include <math.h>
#include "Complex.h"

void main(void)
{
  Complex c1, c2, c3, c4, c5;
  double mag;

			// testing input operator overload
  cout << "Enter two complex numbers c1 and c2 as a+bi c+di : ";
  cin >> c1 >> c2;

			// testing output operator overload
  cout << "The two complex numbers you entered were : " << c1 << " and "
			<< c2 << endl << endl;

			// testing + operator overload
  c3 = c1 + c2;
  cout << "The sum of c1 and c2 is : " << c3 << endl << endl;

			// testing - operator overload
  c3 = c1 - c2;
	cout << "c1 - c2 = " << c3 << endl << endl;

			// testing * operator overload
  c3 = c1 * c2;
	cout << "c1*c2 = " << c3 << endl << endl;

			// testing / operator overload
  c3 = c1 / c2;
	cout << "c1/c2 = " << c3 << endl << endl;

  mag = c3.Magnitude();
  cout << "The magnitude of " << c3 << " is " << mag << endl << endl;

			// testing = operator overload and chaining
	c4 = c5 = c1;
	cout << "c4, c5 and c1 should all be the same: ";
	cout << c4 << "   " << c5 << "   " << c1 << endl << endl;

			// testing comparsion operators
	cout   << "Testing == " << c4 << " == " << c1 << " is " << (c4 == c1) << endl
			<<"           " << c1 << " == " << c3 << " is " << (c1 == c3) << endl 
			<<"Testing != " << c4 << " != " << c1 << " is " << (c4 != c1) << endl
			<<"           " << c1 << " != " << c3 << " is " << (c1 != c3) << endl
			<<"Testing <  " << c1 << " < " << c3 << " is " << (c1 < c3) << endl
			<<"Testing >  " << c1 << " > " << c3 << " is " << (c1 > c3) << endl
			<<"Testing <= " << c1 << " <= " << c3 << " is " << (c1 <= c3) << endl
			<<"           " << c4 << " <= " << c1 << " is " << (c4 <= c1) << endl
			<<"Testing >= " << c1 << " >= " << c3 << " is " << (c1 >= c3) << endl
			<<"           " << c4 << " >= " << c1 << " is " << (c4 >= c1) << endl;
}


