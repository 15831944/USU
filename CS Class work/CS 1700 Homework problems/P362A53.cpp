// 362
// marks
// Mark Salisbury
// P362A53.cpp

/*A53. Write and test a function mysqrt that will calculate the square root of a number in the following way. The square root of a number n can be approximated by
repeated calculation using the formula:
        ng = 0.5(pg + n/pg)
                where ng is the next guess, pg is the previous guess. For example if you want to calculate the square root of 2.0, n = 2.0 and if you start pg at 1.0 then ng
= 0.5(1.0 + 2.0/1.0) = 1.5.
now pg becomes 1.5 and
ng = 0.5(1.5 + 2.0/1.5) = 1.41666667.
Continue this process until |ng - pg| < epsilon where epsilon is a small constant such as 10-8.
Have your function start with pg = n/2
*/

#include <iostream.h>
#include <math.h>
#include <iomanip.h> 

double mysqrt(double n);

void main(void)
{
	double n;
			
	cout << "Enter a number: ";
	cin >> n;
	
	cout << setprecision(8) << "Square root by approximation method is: " << mysqrt(n) << endl;
	cout << setprecision(15) << "Square root by sqrt fuction in math.h: " << sqrt(n) << endl;

}

double mysqrt(double n)
{
	double pg,
			 ng = n / 2.0;
	
	while (fabs(ng - pg) > 1e-8)
	{
		pg = ng;
		ng = 0.5 * (pg + n / pg);
	}
	
	return ng;
}