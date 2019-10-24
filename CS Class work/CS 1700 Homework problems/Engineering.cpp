//Problem for Engineering 1010
//November 11, 1999

#include <fstream.h>
#include <iomanip.h>
#include <math.h>

double TotalCost(int n, double, double diameterFeet[], double purchaseCost[], double installCost[], double &, double &, double &, double &);
double PipePrice(double, double, double);
int GetPipeInfo(int, double [], double [], double [], double[]);
double ElectricityCost(int n, double, double pipeLength, double diameterFeet[], double &);

ifstream fin("pipes.dat");

void main(){
	int n;
	fin >> n;
	double *diameterInches;
	diameterInches = new double[n]; 
	//double diameterInches[n];
	double *purchaseCost;
	purchaseCost = new double[n];
	//double purchaseCost[9];
	double *installCost;
	installCost = new double[n];
	//double installCost[9];
	double *diameterFeet;
	diameterFeet = new double[n];
	//double diameterFeet[9];
	double hp, pcost, icost, ecost;

	GetPipeInfo(n, diameterInches, purchaseCost, installCost, diameterFeet);
	
	double years;
	char response;
	
	do {
		cout << "For how many years would you like to compute the electricity cost of pumping? ";
		cin >> years;
		double mincost = TotalCost(0, years, diameterFeet, purchaseCost, installCost, hp, pcost, icost, ecost);
		double mindiameter = diameterInches[0];
		double cost = mincost;
		cout << "Total Cost for the emergency water supply system over a period of " << years << " years:" << endl;
		cout << "Pipe   Horsepower   Total Pipe   Interest   Total Pumping   Total Cost $" << endl
			 << "size   required     & Pump cost  cost       cost                        " << endl; 
		cout << setiosflags(ios::left) << setiosflags(ios::fixed) 
			  << setprecision(2) << setw(7) << diameterInches[0] 
			  << resetiosflags(ios::left) << setw(10) << hp
			  << setw(12) << pcost
			  << " +"
			  << setw(11) << icost
			  << " +"
			  << setw(13) << ecost
			  << " = " 
			  << setw(12) << cost << endl;	
		
		for (int i = 1; i < n; i++){
			cost = TotalCost(i, years, diameterFeet, purchaseCost, installCost, hp, pcost, icost, ecost);
			cout << setiosflags(ios::left) << setiosflags(ios::fixed) 
				 << setprecision(2) << setw(7) << diameterInches[i] 
				 << resetiosflags(ios::left) << setw(10) << hp
				  << setw(12) << pcost
				  << " +"
				  << setw(11) << icost
				  << " +"
				  << setw(13) << ecost
				  << " = " 
				  << setw(12) << cost << endl;
			if (cost < mincost){
				mincost = cost;
				mindiameter = diameterInches[i];
			}
		}
		cout << endl << "The lowest cost is " << mincost << " using a pipe diameter of " 
				  << mindiameter << " inches." << endl << endl;
		
		cout << "Would you like to run the program again? (y/n) ";
		cin >> response;
	}
	while ((response == 'y') || (response == 'Y'));
}

int GetPipeInfo(int n, double diameterInches[], double purchaseCost[], double installCost[], double diameterFeet[]){
	
	for(int i = 0; i < n; i++){
		fin >> diameterInches[i] >> purchaseCost[i] >> installCost[i];
		diameterFeet[i] = diameterInches[i] / 12.0;
	}
	return n;
}

double TotalCost(int n, double years, double diameterFeet[], double purchaseCost[], double installCost[], double & hp, double &pcost, double &icost, double &ecost){
	//total cost = pump cost + price of pipe (including installation costs) + electricity cost for ten years
	double pumpCost = 70000;
	double pipeLength = 5280 * 3;
	       pcost = pumpCost + PipePrice(pipeLength, purchaseCost[n], installCost[n]);
		   icost = pcost * (pow(1.09, 10) - 1);
		   ecost = ElectricityCost(n, years, pipeLength, diameterFeet, hp);
	return pcost + icost + ecost;
}

double PipePrice(double pipeLength, double pcost, double icost){
	return (pipeLength * (pcost + icost));
}

double ElectricityCost(int n, double years, double pipeLength, double diameterFeet[], double &hp){
	double NumOfHomes = 1500;	  //number of homes currently in North Logan
	double AveHomeUse = 15000;   //gallons of water per month
	double ExpectedDemand = 2.0; //plan for a future use of 2.0 times the current demand
	double PumpUse = 0.25;       //pump should be used 25% of the time in a year
	double PumpEfficiency = 0.80;//pump is 80% energy efficient
	double flowRateGallons = NumOfHomes * AveHomeUse * ExpectedDemand * 12 / (365 * 24 * 60 * 60); 
	//gallons per second.  while the pump is in use, this is the flow rate.  
	double flowRate = flowRateGallons / 7.5;  //number of gallons in a cubic foot...true conversion
	
	double CrossArea = (diameterFeet[n] / 2) * (diameterFeet[n] / 2) * 3.14159265359;
	double flowVelocity = flowRate / CrossArea; //ft^3/s /ft^2
	double G = 32.0; //gravitational constant
	double CostPerHour = 0.10;
	double H = (0.015 * pipeLength * flowVelocity * flowVelocity) / (2 * G * diameterFeet[n]) + 400; //ft * ft/s * ft/s /(32 ft/s^2 * ft
	
	double ftlbpersecond = H  * flowRate * 62.4;	//(ft) * (ft^3 / s) * (lb / ft^3) = ftlb / s
	       hp = ftlbpersecond / 550;				//true conversion
	double hours = years * PumpUse * 365 * 24;
	double kilowatthours = hp * 0.7457 * hours;		//true conversion
	return kilowatthours / PumpEfficiency * CostPerHour;
}
/*
For how many years would you like to compute the electricity cost of pumping? 10

Total Cost for the emergency water supply system over a period of 10 years:
Pipe   Horsepower   Total Pipe   Interest   Total Pumping   Total Cost $
size   required     & Pump cost  cost       cost
4.00      2078.27   218896.00 +  299310.44 +   4242489.21 =   4760695.65
5.00       750.67   236478.40 +  323351.97 +   1532379.68 =   2092210.05
6.00       363.65   257228.80 +  351725.32 +    742336.49 =   1351290.60
7.00       223.92   274811.20 +  375766.85 +    457103.23 =   1107681.28
8.00       165.32   308075.20 +  421250.84 +    337475.81 =   1066801.85
9.00       137.86   333894.40 +  456555.07 +    281411.02 =   1071860.50
10.00      123.83   365891.20 +  500306.34 +    252784.89 =   1118982.42
11.00      116.17   398363.20 +  544707.37 +    237137.56 =   1180208.13
12.00      111.74   432260.80 +  591057.72 +    228096.04 =   1251414.55

The lowest cost is 1066801.85 using a pipe diameter of 8.00 inches.


*/

