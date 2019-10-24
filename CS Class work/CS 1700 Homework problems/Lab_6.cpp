#include <iostream.h>

double getTax (double);

void main ()
{
  double income;
  cout << "Please enter your anual income: ";
  cin >> income;

  double tax = getTax (income);
  cout << "The tax on " << income << " dollars is " << tax << " dollars.\n";
}

double getTax (double I)
{
	if (I >= 35000.00)
		return (I * .235);
	else if (I >= 20000.00)
		return (I * .206);
	else if (I >= 10000.00)
		return (I * .182);
	else 
		return (I * .12);
}

//Income					Tax Rate		
//> 35,000            23.5%      
//20,000 - 34,999.99  20.6%                        
//10,000 - 19,999.99  18.2%                                       
//< 10,000				12.0% 
                                                      
                                                               
                                                                             
                                     
                                                      
                                                               
                                                                               