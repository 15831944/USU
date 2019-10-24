/*****************************************************************************
*
*	File:          TimeOfDay.cpp
*	Class:         TimeOfDay
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
*	This file contains the implementation and test cases for TimeOfDay.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "TimeOfDay.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/*****************************************************************************
*
*   load(const char* buffer, int buffer_lng)
*
*/
BOOL TimeOfDay::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	valid=FALSE;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;

    if (unmarshall(ptr, end_ptr, hours)==TRUE)
	    if (unmarshall(ptr, end_ptr, minutes)==TRUE)
			result = validate();

	buffer_lng = ptr - buffer;

	return result;
}

/*****************************************************************************
*
*   save(char* buffer, int buffer_lng)
*
*/
BOOL TimeOfDay::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (marshall(ptr, end_ptr, hours)==TRUE)
	    result = marshall(ptr, end_ptr, minutes);

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
void TimeOfDay::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	unsigned short lng;

	TimeOfDay b1;
	assert(b1.hours==0);
	assert(b1.minutes==0);
	assert(b1.valid==TRUE);

	TimeOfDay b2(10,30);
	assert(b2.hours==10);
	assert(b2.minutes==30);
	assert(b2.valid==TRUE);

	TimeOfDay b3(24,30);
	assert(b3.hours==24);
	assert(b3.minutes==30);
	assert(b3.valid==FALSE);

	TimeOfDay b4(23,60);
	assert(b4.hours==23);
	assert(b4.minutes==60);
	assert(b4.valid==FALSE);

	lng=4;
	TimeOfDay b5("\0\1\0\2", lng);
	assert(b5.hours==1);
	assert(b5.minutes==2);
	assert(b5.valid==TRUE);
	assert(lng==4);

	lng=4;
	TimeOfDay b6("\0\14\0\20", lng);
	assert(b6.hours==12);
	assert(b6.minutes=16);
	assert(b6.valid==TRUE);
	assert(lng==4);

	lng=2;
	TimeOfDay b7("\0\14\0\20", lng);
	assert(b7.hours==12);
	assert(b7.minutes==0);
	assert(b7.valid==FALSE);
	assert(lng==2);

	app->DisplayMessage("TimeOfDay Test 1 complete\r\n");
}

// Test 2 - Get and set methods and validate method
void TimeOfDay::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TimeOfDay b1;
	assert(b1.hours==0);
	assert(b1.minutes==0);
	assert(b1.getValid()==TRUE);

	b1.setHours(15);
	assert(b1.getHours()==15);
	assert(b1.getValid()==TRUE);

	b1.setHours(24);
	assert(b1.getHours()==24);
	assert(b1.getValid()==FALSE);

	b1.setHours(0);
	assert(b1.getHours()==0);
	assert(b1.getValid()==TRUE);

	b1.setMinutes(20);
	assert(b1.getMinutes()==20);
	assert(b1.getValid()==TRUE);

	b1.setMinutes(60);
	assert(b1.getMinutes()==60);
	assert(b1.getValid()==FALSE);

	b1.setMinutes(0);
	assert(b1.getMinutes()==0);
	assert(b1.getValid()==TRUE);

	app->DisplayMessage("TimeOfDay Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void TimeOfDay::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TimeOfDay b1(10,15);
	char buffer[4];
	unsigned short buffer_lng=4;

	b1.save(buffer, buffer_lng);
	assert(buffer_lng==4);

	TimeOfDay b2;
	b2.load(buffer, buffer_lng);
	
	assert(b2.getHours()==10);
	assert(b2.getMinutes()==15);

	assert(b2.getPackLng()==4);

	TimeOfDay b3(4, 30);
	assert(b3.getHours()==4);
	assert(b3.getMinutes()==30);

	b2 = b3;
	assert(b2.getHours()==4);
	assert(b2.getMinutes()==30);

	app->DisplayMessage("TimeOfDay Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void TimeOfDay::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TimeOfDay b1(10,15);
	TimeOfDay b2(11,15);
	TimeOfDay b3(11,30);
	TimeOfDay b5(11,30);

	assert(b1<b2);
	assert(b2>b1);
	assert(b1!=b2);
	assert(b5==b3);
	assert(b2<b3);
	assert(b3>b2);
	assert(b2<=b3);
	assert(b3>=b2);
	assert(b5>=b3);
	assert(b5<=b3);

	app->DisplayMessage("TimeOfDay Test 4 complete\r\n");
}

// Test case Dispatcher
void TimeOfDay::run_tests(void)
{
	TimeOfDay::test1();
	TimeOfDay::test2();
	TimeOfDay::test3();
	TimeOfDay::test4();
}

#endif



