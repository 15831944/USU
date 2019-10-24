//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  Problems for Sequential Algorithms #3
//  This program calculates tax and total

#include <iostream.h>
#include <math.h>

void main() {

float TaxRate = 0.00;
cout << "Enter the taxrate (as a percentage): " << flush;
cin >> TaxRate;
float ItemOne = 0.00;
float ItemTwo = 0.00;
float ItemThree = 0.00;
cout << "Enter the cost of item #1: " << flush;
cin >> ItemOne;
cout << "Enter the cost of item #2: " << flush;
cin >> ItemTwo;
cout << "Enter the cost of item #3: " << flush;
cin >> ItemThree;
float SubTotal = ItemOne + ItemTwo + ItemThree;
cout << "The subtotal of the three items is: "
<< SubTotal << endl;
cout << "The amount of tax due is: "
<< SubTotal * (TaxRate/100.00) << endl;
cout << "The total is: " << SubTotal * (TaxRate / 100.00 +1);
}
