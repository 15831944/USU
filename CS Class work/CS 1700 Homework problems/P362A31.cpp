// 362
// marks
// Mark Salisbury
// P362A31.cpp

#include <fstream.h>

ifstream ifile1;  
ofstream ofile1;

void main(void){
	
	int total = 0, 
		 inum,
		 items = 0,
		 smallest,
		 largest;
	float average;

	ifile1.open("A34.dat", ios::in);   // filebuf::sh_read);
	ofile1.open("A31.out", ios::out);

   ifile1 >> inum;
	smallest = inum;
	largest = inum;

	while (inum != EOF)
	{
		items++;
		total += inum;
		if (inum < smallest)
			smallest = inum;
		if (inum > largest)
			largest = inum;
		ifile1 >> inum;
	}
	
	average = total / items;

	ofile1 << "The smallest integer is: " << smallest << endl;
	ofile1 << "The largest integer is: " << largest << endl;
	ofile1 << "The average of these 5 integers: " << average << endl;

	ifile1.close();
	ofile1.close();

}
