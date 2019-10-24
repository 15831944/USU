// 362
// marks
// Mark Salisbury
// P362A42.cpp


#include <iostream.h>

char LetterPortion(double Grade);
char PlusOrMinusPortion(double Grade);

void main(void)
{
	double Grade;
	cout << "Enter a double please which represents a student's grade: ";
	cin >> Grade;
	cout << "This grade receives a letter grade of: " << LetterPortion(Grade) << PlusOrMinusPortion(Grade) << endl;
}

char LetterPortion(double Grade)
{	
	switch (int(Grade) / 10)
	{
		case 10:
		case 9: return 'A';
		case 8: return 'B';
		case 7: return 'C';
		case 6: return 'D';
		default: return 'F';
	}
}

char PlusOrMinusPortion(double Grade)
{
	if (int(Grade) < 60) 
		return ' ';
	else
	{
		switch (int(Grade) % 10)
		{
			case 9: case 8: case 7:
				return '+';
			case 0: case 1: case 2:
				if (int(Grade) == 100)
					return '+'; 
				else
					return '-';
			default:
				return ' ';
		}
	}
}






