// 362
// marks
// Mark Salisbury
// P362A41.cpp

/*Use functions where possible!

A41. Write a program that determines the day number (1 to 366) in a year for a date that is provided as input data. As an example, January 1, 1994 is day 1.
December 31, 1993 is day 365. December 31, 1996 is day 366 since 1996 is a leap year. A year is a leap year if it is divisible by four, except that any year divisible
by 100 is a leap year only if it is divisible by 400. Your program should prompt for and accept the month, day, and year as integers. The output will consist of the
day number. Use a function to analyze the days in a month. This function should use a switch statement.
*/

//as a side note: this program does not check for invalid dates.  
#include <iostream.h>

enum MonthsofYear {January = 1, February = 2, March = 3, April = 4, May = 5, June = 6, July = 7, 
August = 8, September = 9, October = 10, November = 11, December = 12};

int DayNumber (int Day, int Month, int Year);

void main(void)
{
	int Day, 
		 Month,
		 Year;

	cout << "Enter a date (mm dd yyyy): ";
	cin >> Month >> Day >> Year;
	cout << "That is day number " << DayNumber(Day,Month,Year) << endl;
}

int DayNumber (int Day, int Month, int Year)
{
	int DaySum = 0;
	int DaysInMonth;
	
	for (int i = 1; (i < Month); i++)
	{
		switch (i) {
			case January: 
			case March: 
			case May: 
			case July: 
			case August: 
			case October: 
			case December:
				DaysInMonth = 31;
				break;
			case April:
			case June:
			case September:
			case November:
				DaysInMonth = 30;
				break;
			case February:
				if ((Year % 400) == 0)
					DaysInMonth = 29;
				else if ((Year % 100) == 0)
					DaysInMonth = 28;
				else if ((Year % 4) == 0)
					DaysInMonth = 29;
				else
					DaysInMonth = 28;
				}
		DaySum += DaysInMonth;
	}
	return (DaySum + Day);
}					
						



