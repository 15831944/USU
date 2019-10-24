// This is Version 1.0 PLEASE DOCUMENT CHANGES
// Checkout.cpp: implementation of the CCheckout class.
//
//////////////////////////////////////////////////////////////////////

// This class is used to store, display, and output to a file, the information gathered from Checkout

#include "stdafx.h"
#include "lada control module.h"
#include "Checkout.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//This function sets into the array what data is being collected
CCheckout::CCheckout()
{
	data[0][0]="Date (day,month,year)";
	data[1][0]="Time(hour,minute)";
	data[2][0]="Fixed (threshold) moisture level of the root environing medium";
	data[3][0]="Substrate moisture level at point KS1";
	data[4][0]="Substrate moisture level at point KS2";
	data[5][0]="Substrate moisture level at point KS3";
	data[6][0]="Substrate moisture level at point KS4";
	data[7][0]="Substrate moisture level at point KS5";
	data[8][0]="Substrate moisture level at point KS6";
	data[9][0]="Substrate moisture level at point KS7";
	data[10][0]="Substrate moisture level at point KS8";
	data[11][0]="Substrate temperature at point KS1";
	data[12][0]="Substrate temperature at point KS2";
	data[13][0]="Substrate temperature at point KS3";
	data[14][0]="Substrate temperature at point KS4";
	data[15][0]="Substrate temperature at point KS5";
	data[16][0]="Substrate temperature at point KS6";
	data[17][0]="Substrate temperature at point KS7";
	data[18][0]="Substrate temperature at point KS8";
	data[19][0]="Substrate oxygen concentration at point KS1";
	data[20][0]="Substrate oxygen concentration at point KS2";
	data[21][0]="Substrate oxygen concentration at point KS3";
	data[22][0]="Substrate oxygen concentration at point KS4";
	data[23][0]="Fixed time interval of programmed moisturization";
	data[24][0]="Volume of pumped water (pumped by pumps 1 & 2)";
	data[25][0]="Leaf chamber air temperature at point LC1";
	data[26][0]="Leaf chamber air temperature at point LC2";
	data[27][0]="Leaf chamber air temperature at point LC3";
	data[28][0]="Leaf chamber air temperature at point LC4";
	data[29][0]="Leaf surface temperature";
	data[30][0]="Leaf chamber air outlet humidity";
	data[31][0]="Operating time of leaf chamber fans";
	data[32][0]="Leaf chamber light intensity at point LC1";
	data[33][0]="Leaf chamber light intensity at point LC2";
	data[34][0]="Leaf chamber light intensity at point LC3";
	data[35][0]="Operating time of the lamp";
	data[36][0]="Cabin air temperature";
	data[37][0]="Cabin abosulte pressure";
	data[38][0]="Cabin humidity";
	data[39][0]="Cabin air oxygen concentration";
	data[40][0]="Cabin air carbon dioxide concentration";
	data[41][0]="Fixed frequency of photography of the leaf chamber";
	data[42][0]="Comments";
	for (int x=2;x<11;x++) // x is used as a counter
		units[x]="(%)";
	for (x=11;x<19;x++)
		units[x]="(C)";
	for (x=19;x<23;x++)
		units[x]="(%)";
	units[23]="(hour)";
	units[24]="(ml)";
	for (x=25;x<30;x++)
		units[x]="(C)";
	units[30]="(%)";
	units[31]="(min.)";
	units[32]="(umol m^-1 s^-1)";
	units[33]="(umol m^-1 s^-1)";
	units[34]="(umol m^-1 s^-1)";
	units[35]="(min.)";
	units[36]="(C)";
	units[37]="(mm rt.st.)";
	units[38]="(%)";
	units[39]="(%)";
	units[40]="(%)";
	units[41]="(shots/24hr)";
}

CCheckout::~CCheckout()
{
}

// This function outputs the data to a file
void CCheckout::output(ofstream fout)
{
	for (int x=0;x<44;x++) // x is used as a counter
		fout << data[x][0].GetBuffer(0) <<"\t" << data[x][1].GetBuffer(0) << "\t" << data[x][2].GetBuffer(0) << "\t" << units[x].GetBuffer(0) << endl;
}

