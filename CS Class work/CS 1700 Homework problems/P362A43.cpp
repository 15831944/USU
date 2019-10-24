// 362
// marks
// Mark Salisbury
// P362A43.cpp

/*A43. Write a program that will call the function pi() and output the value of pi to the screen. The function pi() will calculate pi using the formula:

        pi = 4(1/1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + .... + (-1)i+1/2i-1)

Because you want pi to be accurate, continue the loop while the  absolute value of a term is greater than 10-8.
I've left out a few details for you to work out.*/
#include <math.h>
#include <iostream.h>
#include <iomanip.h>

double pi(void);

void main(void)
{
	cout.precision(7);
	cout << "The value of pi is: " << pi() << endl;
}

double pi(void)
{
	double i = 1;
	double term,
		    sum = 0;
	
	term = pow(-1, i+1)/(2*i-1);
    
	while(fabs(term) > 1e-6)
   {
		sum += term;
      i++;      
		term = pow(-1, i+1)/(2*i-1);
   }
	
	return 4*(sum);
}