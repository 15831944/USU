// 362
// marks
// Mark Salisbury
// P362A51.cpp
/*A51. Write a program to read in a collection of exam scores from the file A51.dat. The scores 
will range in value from 0.0 to 100.0 and will be stored one per line in the file. Your program
should count and output to the screen the number of outstanding scores (90 to 100), the number 
of good scores (80 to 89), the number of satisfactory scores (70 to 79) and the number of 
unsatisfactory scores (0 to 69). Have your program disregard invalid scores. Have your program 
read from the file to the end of file. You must create A51.dat. Do not submit this data file. 
*/

#include <fstream.h>

ifstream infile("A51.dat");

static int NumOfOutstanding = 0;
static int NumOfGood = 0;
static int NumOfSatisfactory = 0;
static int NumOfUnSatisfactory = 0;

void CountScores(); 
void main(void)
{
	
	
	CountScores();

	cout << "Number of outstanding scores: " << NumOfOutstanding << endl;
	cout << "Number of good scores: " << NumOfGood << endl;
	cout << "Number of satisfactory scores: " << NumOfSatisfactory << endl;
	cout << "Number of unsatisfactory scores: " << NumOfUnSatisfactory << endl;
	infile.close();
}

void CountScores()
{
	double score;
	
	while (infile >> score)
	{
		if ((score <= 100.0) && (score >= 0.0))
		switch (int(score)/10)
		{
			case 10: case 9:
				NumOfOutstanding++; break;
			case 8:
				NumOfGood++; break;
			case 7:
				NumOfSatisfactory++; break;
			default:
				NumOfUnSatisfactory++;
		}
	}	
	return;
}



