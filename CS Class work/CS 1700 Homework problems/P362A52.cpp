// 362
// marks
// Mark Salisbury
// P362A52.cpp
/*A52. Let n be a positive integer consisting of up to nine digits. 
The digits are d9, d8,.....,d1. Write a program to list in one column 
each of the digits in the number n.  The rightmost digit, d1, should 
be listed at the top of the column.  Hint, if n is 3407, what is the
value of the digit as computed according to the formula: digit = n % 10;
What is n = n/10 or n/=10?  Use alternating % and / to do this problem.
This must be done inside a while loop. 
What is the condition for the while loop?

The number 3407 would be printed:

7
0
4
3
*/

#include <iostream.h>

void main()
{
	int n;
	
	cout << "Enter a value for n (up to nine digits): ";
	cin >> n;

	while (n > 0)
	{
		cout << n % 10 << endl;
		n /= 10;
	}
}
