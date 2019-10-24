/*****************************************************************************
*
*	File:          TimeBlock.cpp
*	Class:         TimeBlock
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
*	This file contains the implementation and test cases for TimeBlock.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "TimeBlock.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/*****************************************************************************
*
*   load(const char* buffer, int buffer_lng)
*
*/
BOOL TimeBlock::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	valid=FALSE;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;

	unsigned short lng = buffer_lng;
	if (starting_time.load(ptr, lng)==TRUE)
	{
		ptr += lng;
		if (unmarshall(ptr, end_ptr, duration)==TRUE)
			result = validate();
	}

	buffer_lng = ptr - buffer;

	return result;
}

/*****************************************************************************
*
*   save(char* buffer, int buffer_lng)
*
*/
BOOL TimeBlock::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	unsigned short lng = buffer_lng;
	if (starting_time.save(ptr, lng)==TRUE)
	{
		ptr += lng;
	    result = marshall(ptr, end_ptr, duration);
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
void TimeBlock::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TimeBlock b1;
	assert(b1.starting_time==TimeOfDay(0,0));
	assert(b1.duration==0);
	assert(b1.valid==TRUE);

	TimeBlock b2(10,30,60);
	assert(b2.starting_time==TimeOfDay(10,30));
	assert(b2.duration==60);
	assert(b2.valid==TRUE);

	TimeBlock b3(24,30,60);
	assert(b3.starting_time==TimeOfDay(24,30));
	assert(b3.duration==60);
	assert(b3.valid==FALSE);

	TimeBlock b4(12,60,60);
	assert(b4.starting_time==TimeOfDay(12,60));
	assert(b4.duration==60);
	assert(b4.valid==FALSE);

	unsigned short lng=6;
	TimeBlock b5("\0\20\0\36\0\36", lng);
	assert(b5.starting_time==TimeOfDay(16,30));
	assert(b5.duration==30);
	assert(b5.valid==TRUE);

	app->DisplayMessage("TimeBlock Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void TimeBlock::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TimeBlock b1;
	assert(b1.getStartingTime()==TimeOfDay(0,0));
	assert(b1.getDuration()==0);
	assert(b1.getValid()==TRUE);

	TimeBlock b2(10,30,60);
	assert(b2.getStartingTime()==TimeOfDay(10,30));
	assert(b2.getDuration()==60);
	assert(b2.getValid()==TRUE);

	TimeBlock b3(24,30,60);
	assert(b3.getStartingTime()==TimeOfDay(24,30));
	assert(b3.getDuration()==60);
	assert(b3.getValid()==FALSE);

	TimeBlock b4(12,60,60);
	assert(b4.getStartingTime()==TimeOfDay(12,60));
	assert(b4.getDuration()==60);
	assert(b4.getValid()==FALSE);

	app->DisplayMessage("TimeBlock Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void TimeBlock::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TimeBlock b1(11, 15, 45);
	
	char buffer[6];
	unsigned short lng=6;
	b1.save(buffer, lng);
	assert(lng==6);

	TimeBlock b2(buffer, lng);
	assert(b2.starting_time==TimeOfDay(11, 15));
	assert(b2.duration==45);

	app->DisplayMessage("TimeBlock Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void TimeBlock::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TimeBlock b1(10, 15, 30);
	TimeBlock b2(10, 15, 45);
	TimeBlock b3(10, 30, 30);
	TimeBlock b4(11, 30, 30);
	TimeBlock b5(b4);

	assert(b1<b2);
	assert(b2>b1);
	assert(b1<=b2);
	assert(b2>=b1);
	assert(b1!=b2);
	assert(b2!=b1);

	assert(b2<b3);
	assert(b3>b2);
	assert(b2<=b3);
	assert(b3>=b2);
	assert(b2!=b3);
	assert(b3!=b2);

	assert(b3<b4);
	assert(b4>b3);
	assert(b3<=b4);
	assert(b4>=b3);
	assert(b3!=b4);
	assert(b4!=b3);

	assert(b4==b5);
	assert(b5==b4);
	assert(b5>=b4);
	assert(b5<=b4);

	app->DisplayMessage("TimeBlock Test 4 complete\r\n");
}

// Test case Dispatcher
void TimeBlock::run_tests(void)
{
	TimeBlock::test1();
	TimeBlock::test2();
	TimeBlock::test3();
	TimeBlock::test4();
}

#endif



