// 362
// marks
// Mark Salisbury
// P362A34.cpp

#include <iostream.h>

void main(void){
	
	int n,
		 sum = 0,
		 i = 1;
	
	cout << "This program computes the sum of 1 to n integers." << endl;
	cout << "Enter n: ";

	cin >> n;

	while (i <= n)
	{
		sum += i;
		i++;
	}
	
	cout << "The sum is: " << sum << endl;
		
}
