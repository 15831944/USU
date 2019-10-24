/*****************************************************************************
*
*	File:          ReservedTime.cpp
*	Class:         ReservedTime
*	Version:       1.0
*	Project:       Distributed Calendar System
*	Author:        Stephen W. Clyde
*	Last Modified: September 5, 2001
*
*	Modification History:
*
*  	Sep. 5, 2001	Initial version
*
*	Description:
*
*	This file contains the implementation and test cases for Building.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "ReservedTime.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/******************************************************************************
*
*  Method:  ReservedTime::load
*
*  This function loads a ReservedTime object from string data.
*
*  After you load a ReservedTime object, the validity of the object can be checked
*  with the isValid() method.
*/
BOOL ReservedTime::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	unsigned short lng;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;
    if (unmarshall(ptr, end_ptr, id)==TRUE)
	  if (unmarshall(ptr, end_ptr, label)==TRUE)
	  {
		lng = end_ptr - ptr;
		if (ReservedTime_date.load(ptr, lng)==TRUE)
		{
		  ptr += lng;
		  lng = end_ptr - ptr;
		  if (ReservedTime_time.load(ptr, lng)==TRUE)
		  {
			  ptr += lng;
			  result=validate();
		  }
		}
	  }

	buffer_lng = ptr - buffer;

	return result;
}

/******************************************************************************
*
*  Method:  ReservedTime::save
*
*  This function save a ReservedTime object into a string.
*
*/
BOOL ReservedTime::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;
	unsigned short lng;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (marshall(ptr, end_ptr, id)==TRUE)
	  if (marshall(ptr, end_ptr, label)==TRUE)
	    lng = end_ptr - ptr;
	    if (ReservedTime_date.save(ptr, lng)==TRUE)
		{
		  ptr += lng;
		  lng = end_ptr - ptr;
		  if (ReservedTime_time.save(ptr, lng)==TRUE)
		  {
		    ptr += lng;
			result = TRUE;
		  }
		}

	buffer_lng = ptr - buffer;
	return result;
}

#ifdef TESTING
/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <fstream.h>
#include <assert.h>

// Test 1 - Constructor
void ReservedTime::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	ReservedTime e1;
	assert(e1.id==-1);
	assert(e1.label=="");
	assert(e1.ReservedTime_date<=CalendarDate());
	assert(e1.ReservedTime_time==TimeBlock());

	char *tmp = "\0\0\0\3"
				"\0\15Research Time"
				"\7\321\0\1\0\2"
				"\0\12\0\36\0\36";

	unsigned short lng = 31;
    ReservedTime e2(tmp, lng);
	assert(lng==31);

	assert(e2.id==3);
	assert(e2.label=="Research Time");
	assert(e2.ReservedTime_date==CalendarDate(2001,1,2));
	assert(e2.ReservedTime_time==TimeBlock(10,30,30));

	ReservedTime e3(e2);
	assert(e3.id==3);
	assert(e3.label=="Research Time");
	assert(e3.ReservedTime_date==CalendarDate(2001,1,2));
	assert(e3.ReservedTime_time==TimeBlock(10,30,30));

	app->DisplayMessage("ReservedTime Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void ReservedTime::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	ReservedTime e1;

	BOOL result;

	result=e1.setId(2532);
	assert(e1.getId()==2532);
	result=e1.setId(0);
	assert(e1.getId()==0);
	result=e1.setId(6436);
	assert(e1.getId()==6436);
	result=e1.setId(-1);
	assert(e1.getId()==-1);
	result=e1.setId(-2364);
	assert(e1.getId()==-2364);

	result=e1.setlabel(DString("Reserved"));
	assert(e1.getlabel()=="Reserved");
	result=e1.setlabel(DString(""));
	assert(e1.getlabel()=="");
	result=e1.setlabel(DString("Private Time"));
	assert(e1.getlabel()=="Private Time");

	result=e1.setDate(CalendarDate(2001,5,30));
	assert(e1.getDate()==CalendarDate(2001,5,30));

	result=e1.setTime(TimeBlock(10,30,45));
	assert(e1.getTime()==TimeBlock(10,30,45));

	app->DisplayMessage("ReservedTime Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void ReservedTime::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	BOOL result;

	ReservedTime e0;
	unsigned tmp_lng = e0.getPackLng();
	assert(tmp_lng==18);

	ReservedTime e1;
	result=e1.setId(2532);
	result=e1.setlabel(CString("Reserved"));
	result=e1.setDate(CalendarDate(2001,5,30));
	result=e1.setTime(TimeBlock(10,0,60));

	unsigned short lng = e1.getPackLng();
	char *tmp = new char[lng];
	e1.save(tmp, lng);
	assert(lng==e1.getPackLng());

	ReservedTime e2(tmp, lng);
	assert(lng==e1.getPackLng());

	assert(e2.getId()==2532);
	assert(e2.getlabel()=="Reserved");
	assert(e2.getDate()==CalendarDate(2001,5,30));
	assert(e2.getTime()==TimeBlock(10,0,60));

	delete tmp;

	app->DisplayMessage("ReservedTime Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void ReservedTime::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	ReservedTime e1;
	e1.setId(0);
	ReservedTime e2;
	e2.setId(3);
	ReservedTime e3;
	e3.setId(10);
	ReservedTime e4;
	e4.setId(10);

	assert(e1<e2);
	assert(e2>e1);
	assert(e1<=e2);
	assert(e2>=e1);
	assert(e1!=e2);
	assert(e2<e3);
	assert(e3>e2);
	assert(e2<=e3);
	assert(e3>=e2);
	assert(e3!=e2);
	assert(e3==e4);
	assert(e3<=e4);
	assert(e4>=e4);

	app->DisplayMessage("ReservedTime Test 4 complete\r\n");
}

// Test 5 - Validation functions
void ReservedTime::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	BOOL result;

	ReservedTime e1;
	result=e1.setId(2532);
	result=e1.setlabel(CString("No Meetings"));
	result=e1.setDate(CalendarDate(2001,5,30));
	result=e1.setTime(TimeBlock(10,0,60));

	assert(e1.getValid()==TRUE);
	result=e1.setDate(CalendarDate(2001,14,30));
	assert(result==FALSE);
	assert(e1.getValid()==FALSE);
	result=e1.setTime(TimeBlock(24,0,0));
	assert(result==FALSE);
	assert(e1.getValid()==FALSE);

	app->DisplayMessage("ReservedTime Test 5 complete\r\n");
}

// Test case Dispatcher
void ReservedTime::run_tests(void)
{
	ReservedTime::test1();
	ReservedTime::test2();
	ReservedTime::test3();
	ReservedTime::test4();
	ReservedTime::test5();
}


#endif



