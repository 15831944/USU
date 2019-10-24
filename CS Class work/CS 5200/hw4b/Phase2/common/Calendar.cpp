/*****************************************************************************
*
*	File:          Calendar.cpp
*	Class:         Calendar
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
*	This file contains the implementation and test cases for Calendar.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "Calendar.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/*****************************************************************************
*
*   load(const char* buffer, int buffer_lng)
*
*/
BOOL Calendar::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	valid=FALSE;
	unsigned short lng;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;

	valid=FALSE;
    if (unmarshall(ptr, end_ptr, id)==TRUE)
	{
		lng = end_ptr - ptr;
	    if (day_start_time.load(ptr, lng)==TRUE)
		{
			ptr += lng;
			lng = end_ptr - ptr;
			if (day_end_time.load(ptr, lng)==TRUE)
			{
				ptr += lng;
				result = validate();
			}
		}
	}

	buffer_lng = ptr - buffer;

	return result;
}

/*****************************************************************************
*
*   save(char* buffer, int buffer_lng)
*
*/
BOOL Calendar::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;
	unsigned short lng;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (marshall(ptr, end_ptr, id)==TRUE)
	{
		lng = end_ptr - ptr;
	    if (day_start_time.save(ptr, lng)==TRUE)
		{
			ptr += lng;
			lng = end_ptr - ptr;
            result = day_end_time.save(ptr, lng);
			ptr += lng;
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
void Calendar::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	unsigned short lng;

	Calendar c1;
	assert(c1.getId()==-1);
	assert(c1.day_start_time==TimeOfDay(8,0));
	assert(c1.day_end_time==TimeOfDay(17,0));
	assert(c1.valid==FALSE);

	lng = 12;
	Calendar c2("\0\0\0\1\0\7\0\36\0\20\0\17",lng);
	assert(c2.getId()==1);
	assert(c2.day_start_time==TimeOfDay(7,30));
	assert(c2.day_end_time==TimeOfDay(16,15));
	assert(c2.valid==TRUE);
	assert(lng==12);

	lng = 12;
	Calendar c3("\0\0\0\1\1\7\0\36\0\20\0\17",lng);
	assert(c3.getId()==1);
	assert(c3.day_start_time==TimeOfDay(263,30));
	assert(c3.day_end_time==TimeOfDay(0,0));
	assert(c3.valid==FALSE);
	assert(lng==4);

	Calendar c4(c2);
	assert(c4.getId()==1);
	assert(c4.day_start_time==TimeOfDay(7,30));
	assert(c4.day_end_time==TimeOfDay(16,15));
	assert(c4.valid==TRUE);

	app->DisplayMessage("Calendar Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void Calendar::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Calendar c1;
	assert(c1.getId()==-1);
	assert(c1.day_start_time==TimeOfDay(8,0));
	assert(c1.day_end_time==TimeOfDay(17,0));
	assert(c1.valid==FALSE);

	assert(c1.setId(30)==TRUE);
	assert(c1.getId()==30);
	assert(c1.setStartTime(TimeOfDay(9,30))==TRUE);
	assert(c1.getStartTime()==TimeOfDay(9,30));
	assert(c1.setEndTime(TimeOfDay(19,50))==TRUE);
	assert(c1.getEndTime()==TimeOfDay(19,50));
	assert(c1.getValid()==TRUE);

	assert(c1.setId(-1)==FALSE);
	assert(c1.getId()==-1);
	assert(c1.setStartTime(TimeOfDay(25,30))==FALSE);
	assert(c1.getStartTime()==TimeOfDay(25,30));
	assert(c1.setEndTime(TimeOfDay(19,60))==FALSE);
	assert(c1.getEndTime()==TimeOfDay(19,60));
	assert(c1.getValid()==FALSE);

	app->DisplayMessage("Calendar Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void Calendar::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Calendar c1;
	c1.setId(300);
	c1.setStartTime(TimeOfDay(8,0));
	c1.setEndTime(TimeOfDay(18,30));
	
	char buffer[1024];
	unsigned short lng=1024;

	c1.save(buffer, lng);
	assert(lng==12);
	assert(c1.getPackLng()==12);

	Calendar c2(buffer, lng);
	assert(c2.getId()==300);
	assert(c2.getStartTime()==TimeOfDay(8,0));
	assert(c2.getEndTime()==TimeOfDay(18,30));
	assert(c2.getValid()==TRUE);

	app->DisplayMessage("Calendar Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void Calendar::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Calendar c1(300);
	assert(c1.getId()==300);
	assert(c1.getValid()==TRUE);

	Calendar c2(340);
	assert(c2.getId()==340);
	assert(c1.getValid()==TRUE);

	Calendar c3(390);
	assert(c3.getId()==390);
	assert(c1.getValid()==TRUE);

	Calendar c5(c1);
	assert(c5.getId()==300);
	assert(c1.getValid()==TRUE);

	assert(c1<c2);
	assert(c2>c1);
	assert(c1<=c2);
	assert(c2>=c1);
	assert(c2!=c1);
	assert(c5==c1);
	assert(c5<=c1);
	assert(c5>=c1);

	app->DisplayMessage("Calendar Test 4 complete\r\n");
}

// Test case Dispatcher
void Calendar::run_tests(void)
{
	Calendar::test1();
	Calendar::test2();
	Calendar::test3();
	Calendar::test4();
}


#endif
