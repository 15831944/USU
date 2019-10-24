// 362
// marks
// Mark Salisbury
// P362A61.cpp

#include <iostream.h>
#include <iomanip.h>

void main(){

	const int NumOfCars = 3;
	double CHours[NumOfCars], THours = 0;
	double Charge[NumOfCars], TCharge = 0.0;
	
	for (int i = 0; i < NumOfCars; i++){
		cout << endl << "How many hours was car" << i + 1 << " parked in the garage? ";
		cin >> CHours[i];
		
		if (CHours[i] <= 3.0)
			Charge[i] = 3.0;
		else
			Charge[i] = 3.0 + (CHours[i] - 3.0) * 0.5;
		
		if (Charge[i] > 10.0)
			Charge[i] = 10.0;
		
		THours += CHours[i];
		TCharge += Charge[i];
	}
   cout << setiosflags( ios::left | ios::fixed )
	     << setw(5) 
		  << "Car" 
		  << resetiosflags( ios::left )
		  << setw(8) 
		  << "Hours" 
		  << setw(8) 
		  << "Charge" 
		  << endl;
	
	for (i = 0; i < NumOfCars; i++)
		cout << setiosflags( ios::left )
		     << setw(5) 
		     << i + 1 
			  << resetiosflags( ios::left )
			  << setprecision(1) 
			  << setw(8)
			  << CHours[i] 
			  << setprecision(2) 
			  << setw(8)
			  << Charge[i] 
			  << endl;
	
	cout << setiosflags( ios::left ) 
		  << setw(5) 
		  << "TOTAL" 
		  << resetiosflags( ios::left )
		  << setw(8) 
		  << setprecision(1) 
		  << THours 
		  << setw(8) 
		  << setprecision(2) 
		  << TCharge 
		  << endl;

}

