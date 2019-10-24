/* Mark Salisbury
529-71-8265
2nd hour
Temperature Conversion assignment */

#include <iostream.h>

void main() {
float Ftemp;
float Ctemp;
cout << "Enter farenheit temperature: ";
cin >> Ftemp;
Ctemp = (Ftemp-32.0)*5/9;
cout << "Celcius temperature is: " << Ctemp;
}
