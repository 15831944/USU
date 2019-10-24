// 362
// marks
// Mark Salisbury
// P362A23.cpp

#include <iostream.h>

void main(void){
	
	int num,
		 i1,
		 i2,
		 i3,
		 i4,
		 i5;
		
	cout << "Enter one 5 digit number: ";
	cin >> num;

	i1 = (num % 10);
	i2 = (num % 100) / 10;
	i3 = (num % 1000) / 100;
	i4 = (num % 10000) / 1000;
	i5 = (num % 100000) / 10000;

	cout << i5 << " " << i4 << " " << i3 << " " << i2 << " " << i1 << endl;

}
