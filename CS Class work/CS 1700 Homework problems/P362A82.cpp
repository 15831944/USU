//P362
//marks
//Mark Salisbury
//P362A82.cpp
/*CS1700 Assignment 8 Functions 
/*A82. Write a complete C++ program will prompt for a number of seconds 
(an unsigned long) and will call a function named convert that will convert 
the number of seconds to years, days, hours, minutes and seconds, and will 
then output to the screen, the years, days, hours, minutes and seconds. The 
function convert must have six parameters, the first is a value parameter 
seconds, the rest of the parameters are references parameters representing 
years, days, hours, minutes and seconds.  The function convert must use 
integer / and % to analyze the value parameter seconds. For example 
45000075 seconds is 1 year, 155 days, 14 hours, 1 minutes, 15 seconds. use 
365.25 days in a year.*/
#include <iostream.h>

void Convert(unsigned int &, int &, int &, int &,
			 int &, int &);

void main(void){
	unsigned int TotalSeconds;
	int Years, Days, Hours, Minutes, Seconds;

	cout << "Enter seconds: ";
	cin >> TotalSeconds;
	
	Convert(TotalSeconds, Years, Days, Hours, Minutes, Seconds);
	
	cout << "That is:" << endl
		 << Years << " Years" << endl
		 << Days << " Days" << endl
		 << Hours << " Hours" << endl
		 << Minutes << " Minutes" << endl
		 << Seconds << " Seconds" << endl;
}

void Convert(unsigned int &I, int &Years, int &Days, 
			 int &Hours, int &Minutes, 
			 int &Seconds){
	Seconds = I % 60;
	I -= Seconds;
	I /= 60; // i = total minutes (- seconds)
	Minutes = I % 60;
	I -= Minutes;
	I /= 60; // i = total Hours (- minutes)
	Hours = I % 24;
	I -= Hours;
	I /= 24; // i = total Days (- hours)
	Days = I % 365;
	I -= Days;
	I /= 365; // i = total Years (- Days)
	Years = I;
}



