// 362
// marks
// Mark Salisbury
// P362A104.cpp
//A104. (compound interest) do problem 2.65 from your text. 
// Fig. 2.21: fig02_21.cpp
// Calculating compound interest
#include <iostream.h>
#include <iomanip.h>
#include <math.h>

void main()
{
   double amount,              // amount on deposit
          principal = 24.0,    // starting principal
          rate = .10;          // interest rate
	int years = 372;

	cout << "Watch $" << setiosflags(ios::fixed) << setprecision(2) << principal << " grow for " << years << " years at " 
		  << rate * 100 << "% interest, compounded annually." << endl;
   cout << "Year" << setw( 21 ) 
        << "Amount on deposit" << endl;

   for ( int year = 1; year <= years; year++ ) {
      if (year % 20 == 0 || year == years){
			amount = principal * pow( 1.0 + rate, year );
    		cout << setw( 4 ) << year
				  << setiosflags( ios::fixed | ios::showpoint )
				  << setw( 21 ) << setprecision( 2 ) 
				  << amount << endl;
		}
   }
}
