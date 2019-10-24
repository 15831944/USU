//Lab 8
#include <fstream.h>
#include <iomanip.h>

ifstream infile("grades.dat");

void main()
{
	const int DataItems = 6;
	int StudentInfo[DataItems];
	int Sum = 0;
	float Average;
	int j = 0;
	
	cout << setprecision(2) << setiosflags( ios::left | ios::fixed | ios::showpoint );
	cout << setw(7) << "PIN" 
		  << setw(7) << "TEST1"
		  << setw(7) << "TEST2" 
		  << setw(7) << "TEST3"
		  << setw(7) << "TEST4" 
		  << setw(7) << "FINAL"
		  << setw(7) << "TOTAL"
		  << setw(7) << "AVERAGE"
		  << endl;

	while (infile >> StudentInfo[j])
	{
		if (j == 0)
			Sum = 0;
		else 
			Sum += StudentInfo[j];
		
		cout << setw(7) << StudentInfo[j];
		j++;
		
		if (j == DataItems)
		{
			cout << setw(7) << Sum;
			Average = float(Sum) / (DataItems - 1);
			cout << setw(7) << Average << endl; 	
			j = 0;
		}
	}
}