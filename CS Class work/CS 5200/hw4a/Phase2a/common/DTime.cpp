/*****************************************************************************
*
*  File:          DTime.cpp
*  Class:         DTime
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*     A DString is a dynamic string that combines common features
*     of MFC's CString with Unix's String.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include "DTime.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"

/****************************************************************************
*
*	loadFromChar
*
*	This method loads the date/time from a string in the following format:
*
*		YYYYMMDD HH:MM
*/
void Dtime::loadFromChar(const DString& char_str)
{
	DString d, t, h, m;

	int pos=char_str.find(' ');
	if (pos<0)
		d=char_str;
	else
	{
		d = char_str.Left(pos);
		t = char_str.Mid(pos+1);
		pos=t.find(':');
		if (pos<0)
			h=t;
		else
		{
			h=char_str.Left(pos);
			m=char_str.Mid(pos+1);
		}
	}
	d.fillRight(8,'0');
	h.fillRight(2,'0');
	m.fillRight(2,'0');
	
	int year, month, day, hour, minute;

	DString tmp;
	tmp=d.Mid(0,4);
	year = (short) tmp;
	tmp=d.Mid(4,2);
	month = (short) tmp;
	tmp=d.Mid(6,2);
	day = (short) tmp;
	hours = (short) h;
	minutes = (short) m;

	*this = CTime(year, month, day, hours, minutes, 0);
}

/****************************************************************************
*
*	saveToChar
*/
BOOL Dtime::saveToChar(DString& char_str)
{
	char_str = Format("%Y%m%d %H:%M");
}


/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <assert.h>

// Test 1 - Basic Constructors
void DTime::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


    app->DisplayMessage("DTime Test 1 complete\r\n");
}

// Test 2 - fillRight, Left, Mid, TrimRight
void DTime::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


	app->DisplayMessage("DTime Test 2 complete\r\n");
}

// Test 3 - 
void DTime::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("DTime Test 3 complete\r\n");
}

// Test 4 - 
void DTime::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


	app->DisplayMessage("DSTime Test 4 complete\r\n");
}

// Test 5 - 
void DTime::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


	app->DisplayMessage("Time Test 5 complete\r\n");
}

// Test 6 - 
void DTime::test6(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();



	app->DisplayMessage("DTime Test 6 complete\r\n");
}

#endif
