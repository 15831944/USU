

// Program 3.2: Compute number of molecules in
// a hydrocarbon
#include <iostream.h>
int main() {
	cout << "This program calculates the number of molecules   \n"
			  "in a sugar, based on its weight, and the number of\n"
			  "hydrogen, carbon, and oxygen atoms in it's formula.\n"
			  "Example: in 180 grams of glucose, C6H12O6, there   \n"
			  "would be 6.02 x 10^23 molecules.                   \n";
	cout << "Enter mass of the sugar (in grams): " << flush;
	float Mass = 0.0;
	cin >> Mass;
	cout << "Enter the number of carbon atoms: " << flush;
	int Carbon = 0;
	cin >> Carbon;
	cout << "Enter the number of hydrogen atoms: " << flush;
	int Hydrogen = 0;
	cin >> Hydrogen;
	cout << "Enter the number of oxygen atoms: " << flush;
	int Oxygen = 0;
	cin >> Oxygen;
   cout << endl;
	const int CarbonAMU = 12;
	const int HydrogenAMU = 1;
	const int OxygenAMU = 16;
	long FormulaWght = (Carbon * CarbonAMU)
	 + (Hydrogen * HydrogenAMU) + (Oxygen * OxygenAMU);

	const double AvogadroNmbr = 6.02e23;
	double Molecules = (Mass / FormulaWght) *
	 AvogadroNmbr;
	cout << Mass << " grams of a sugar\nwith "
	 << Carbon << " carbon atom(s) and \n"
	 << Hydrogen << " hydrogen atom(s) and \n"
	 << Oxygen << " oxygen atom(s)\ncontains "
	 << Molecules << " molecules" << endl;

	return 0;
}
