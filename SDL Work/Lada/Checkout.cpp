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
	int line = 0;
	data[line++][0]="Date (day,month,year)";
	data[line++][0]="Time(hour,minute)";
	data[line++][0]="Fixed (threshold) moisture level of the root environing medium";
	data[line++][0]="Maximum dose for water injection";
	data[line++][0]="Substrate temperature at point KS1";
	data[line++][0]="Substrate temperature at point KS2";
	data[line++][0]="Substrate temperature at point KS3";
	data[line++][0]="Substrate temperature at point KS4";
	data[line++][0]="Substrate temperature at point KS5";
	data[line++][0]="Substrate temperature at point KS6";
	data[line++][0]="Substrate temperature at point KS7";
	data[line++][0]="Substrate temperature at point KS8";
	data[line++][0]="Substrate differential temperature at point KS1";
	data[line++][0]="Substrate differential temperature at point KS2";
	data[line++][0]="Substrate differential temperature at point KS3";
	data[line++][0]="Substrate differential temperature at point KS4";
	data[line++][0]="Substrate differential temperature at point KS5";
	data[line++][0]="Substrate differential temperature at point KS6";
	data[line++][0]="Substrate differential temperature at point KS7";
	data[line++][0]="Substrate differential temperature at point KS8";
	data[line++][0]="Substrate moisture level at point KS1";
	data[line++][0]="Substrate moisture level at point KS2";
	data[line++][0]="Substrate moisture level at point KS3";
	data[line++][0]="Substrate moisture level at point KS4";
	data[line++][0]="Substrate moisture level at point KS5";
	data[line++][0]="Substrate moisture level at point KS6";
	data[line++][0]="Substrate moisture level at point KS7";
	data[line++][0]="Substrate moisture level at point KS8";
	data[line++][0]="Volume of pumped water for Pump 1";
	data[line++][0]="Volume of pumped water for Pump 2";
	data[line++][0]="Leaf chamber air temperature at point LC1";
	data[line++][0]="Leaf chamber air temperature at point LC2";
	data[line++][0]="Leaf chamber air temperature at point LC3";
	data[line++][0]="Leaf chamber air temperature at point LC4";
	data[line++][0]="Leaf surface temperature";
	data[line++][0]="Leaf chamber air outlet humidity";
	data[line++][0]="Operating time of leaf chamber fans";
	data[line++][0]="Leaf chamber light intensity at point LC1";
	data[line++][0]="Leaf chamber light intensity at point LC2";
	data[line++][0]="Leaf chamber light intensity at point LC3";
	data[line++][0]="Operating time of the lamp";
	data[line++][0]="Cabin air temperature";
	data[line++][0]="Cabin abosulte pressure";
	data[line++][0]="Cabin humidity";
	data[line++][0]="Cabin air oxygen concentration";
	data[line++][0]="Cabin air carbon dioxide concentration";
	data[line++][0]="Fixed frequency of photography of the leaf chamber";
	data[line++][0]="Comments";
	units[2]="%";
	units[3]="ml";
	for (int x=4;x<20;x++) // x is used as a counter
		units[x]="(C)";
	for (x=20;x<28;x++)
		units[x]="(%)";
	units[28]="(ml)";
	units[29]="(ml)";
	for (x=30;x<35;x++)
		units[x]="(C)";
	units[35]="(%)";
	units[36]="(sec.)";
	units[37]="(umol m^-1 s^-1)";
	units[38]="(umol m^-1 s^-1)";
	units[39]="(umol m^-1 s^-1)";
	units[40]="(sec.)";
	units[41]="(C)";
	units[42]="(mm rt.st.)";
	units[43]="(%)";
	units[44]="(mm Hg.)";
	units[45]="(um Hg.)"; //Partial Pressure
	units[46]="(shots/24hr)";
}

CCheckout::~CCheckout()
{
}

// This function outputs the data to a file
void CCheckout::output(ofstream fout)
{
	for (int x=0;x<47;x++) // x is used as a counter
		fout << data[x][0].GetBuffer(0) <<"\t" << data[x][1].GetBuffer(0) << "\t" << data[x][2].GetBuffer(0) << "\t" << units[x].GetBuffer(0) << endl;
}

