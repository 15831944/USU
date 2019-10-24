// 362
// marks
// Mark Salisbury
// P362A33.cpp

#include <fstream.h>

ifstream ifile1;  
ofstream ofile1;

void main(void){
	
	double n,
			 largest,
			 largest2;

	ifile1.open("a33.dat", ios::in);   

   ifile1 >> n;
	largest = n;

	while (n != EOF)
	{
		if (n > largest)
		{
			largest2 = largest;
			largest = n;
		}
		ifile1 >> n;
	}
	
	cout << "The largest number from the given data is: " << largest << endl;
	cout << "The second largest number from the given data is: " << largest2 << endl;
	
	ifile1.close();
	
}
