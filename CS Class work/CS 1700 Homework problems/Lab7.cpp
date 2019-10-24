
#include <fstream.h>
#include <iomanip.h>

ifstream infile("grades.dat");
ofstream ofile("averages.out");

void main()
{
	const int Students = 5;
	const int DataItems = 4;
	int StudentInfo[Students][DataItems];
	float Sum = 0;
	float Average[Students];
	int j;

	ofile << "PIN Test1 Test2 Final Average" << endl;

	ofile << setprecision(1) << setiosflags( ios::left | ios::fixed | ios::showpoint );

	for (int i = 0; i < Students; i++)
	{
		for (j = 0; j < DataItems; j++)
		{
			infile >> StudentInfo[i][j];
			if (j == 0)
			{
				Sum = 0;
				ofile << setw(4);
			}
			else 
			{
				Sum += StudentInfo[i][j];
				ofile << setw(6);
			}
			ofile << StudentInfo[i][j];
		}
		
		Average[i] = Sum / (DataItems - 1);
		ofile << setw(4) << Average[i] << endl; 	
		
	}
	infile.close();
	ofile.close();
}

/*Part 2: While loops 

Modify the previous program to use a while loop instead of a for loop. 
*/

#include <fstream.h>
#include <iomanip.h>

ifstream infile("grades.dat");
ofstream ofile("averages.out");

void main()
{
	const int DataItems = 4;
	int StudentInfo[DataItems];
	float Sum = 0;
	float Average;
	int j = 0;

	ofile << "PIN Test1 Test2 Final Average" << endl;

	ofile << setprecision(1) << setiosflags( ios::left | ios::fixed | ios::showpoint );

	while (infile >> StudentInfo[j])
	{
		if (j == 0)
		{
			Sum = 0;
			ofile << setw(4);
		}
		else 
		{
			Sum += StudentInfo[j];
			ofile << setw(6);
		}
		
		ofile << StudentInfo[j];
		j++;
		
		if (j == DataItems)
		{
			Average = Sum / (DataItems - 1);
			ofile << setw(4) << Average << endl; 	
			j = 0;
		}
	}
	infile.close();
	ofile.close();
}