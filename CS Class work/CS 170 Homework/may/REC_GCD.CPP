//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  5-DD-97
//  Chapter x, Problem x.xx
//  Program description

#include <iostream.h>
long GCD(long N1,long N2);

void main() {
long n1;
long n2;
long temp;
do {
cout << "Enter the first long integer (greater than 0): " << flush;
cin >> n1;
} while (n1 < 1);
do {
cout << "Enter the second long integer (greater than 0): " << flush;
cin >> n2;
} while (n2 < 1);
if (n1 < n2) {
temp = n1;
n1 = n2;
n2 = temp;
}
cout << "The GCD is: " << GCD(n1,n2) << endl;
}

long GCD(long n1,long n2) {

if (n1 % n2 == 0)
	return n2;
else
	return GCD(n2, n1 % n2);
}
