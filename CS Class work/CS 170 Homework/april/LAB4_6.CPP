// computes the value 1 by summing the fraction 1/n, n times

#include <iostream.h>

int main() {

	float Total = 0.0;        // running sum of the fraction total
	int n = 10;            // number of fraction units
	float Fraction = 1.0/n;     // will be 1/n;
	int LoopCounter = 0;  // number of times for loop has executed so far

	for (Total = 0.0; Total < 1; Total += Fraction)
		++LoopCounter;

	cout << "The total is " << Total << "\n" ;
	cout << "The loop counter is " << LoopCounter << endl;

	return 0;
}
