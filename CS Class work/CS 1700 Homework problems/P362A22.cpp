// 362
// marks
// Mark Salisbury
// P362A22.cpp

#include <iostream.h>

void main(void){
	
	int a, 
		 b, 
		 c, 
		 d, 
		 e,
		 smallest,
		 largest;
		
	cout << "Enter 5 integers: ";
	cin >> a >> b >> c >> d >> e;

	smallest = a;
	largest = a;
	
	if (b < smallest) 
		smallest = b;
	if (c < smallest) 
		smallest = c;
	if (d < smallest) 
		smallest = d;
	if (e < smallest) 
		smallest = e;

	if (b > largest) 
		largest = a;
	if (c > largest) 
		largest = c;
	if (d > largest) 
		largest = d;
	if (e > largest) 
		largest = e;

	cout << "The smallest integer is: " << smallest << endl;
	cout << "The largest integer is: " << largest << endl;

}
