/*****************************************************************************
*
*	File:          MeetingPreference.cpp
*	Class:         MeetingPreference
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
*	This file contains the implementation and test cases for MeetingPreference.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "MeetingPreference.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif


/******************************************************************************
*
*	Method:  MeetingPreference::load
*
*	This function loads a Meeting Preference object from a buffer
*
*	After you load a Meeting Preference object, the validity of the object can
*	be checked with the isValid() method.
*/
BOOL MeetingPreference::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	unsigned short lng;
	unsigned char tmp;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;
    if (::unmarshall(ptr, end_ptr, id)==TRUE)
	{
		lng = end_ptr - ptr;
		if (timeslot.load(ptr, lng)==TRUE)
		{
			ptr += lng;
			if (::unmarshall(ptr, end_ptr, tmp)==TRUE)
			{
				day_of_week = (DAY_OF_WEEK) tmp;
				if (::unmarshall(ptr, end_ptr, tmp)==TRUE)
				{
					week_of_month = (WEEK_OF_MONTH) tmp;
					if (::unmarshall(ptr, end_ptr, preference)==TRUE)
					result=validate();
				}
			}
		}
	}

	buffer_lng = ptr - buffer;

	return result;
}

/******************************************************************************
*
*  Method:  MeetingPreference::save
*
*  This function save a MeetingPreference object into a string.
*
*/
BOOL MeetingPreference::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;
	char tmp;
	unsigned short lng;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (::marshall(ptr, end_ptr, id)==TRUE)
	{
		lng = end_ptr - ptr;
		if (timeslot.save(ptr, lng)==TRUE)
		{
			ptr += lng;
			tmp = (char) day_of_week;
			if (::marshall(ptr, end_ptr, tmp)==TRUE)
			{
				tmp = (char) week_of_month;
				if (::marshall(ptr, end_ptr, tmp)==TRUE)
					if (::marshall(ptr, end_ptr, preference)==TRUE)
						result = TRUE;
			}
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
void MeetingPreference::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	MeetingPreference e1;
	assert(e1.id==-1);
	assert(e1.timeslot==TimeBlock());
	assert(e1.day_of_week==NO_PREF_FOR_DAY_OF_WEEK);
	assert(e1.week_of_month==NO_PREF_FOR_WEEK_OF_MONTH);
	assert(e1.preference==0);
	assert(e1.valid==FALSE);

	char *tmp = "\0\0\0\3"
				"\0\12\0\36\0\36"
				"\1\2\0\3";

	unsigned short lng = 14;
    MeetingPreference e2(tmp, lng);
	assert(lng==14);

	assert(e2.id==3);
	assert(e2.timeslot==TimeBlock(10,30,30));
	assert(e2.day_of_week==SUNDAY);
	assert(e2.week_of_month==SECOND);
	assert(e2.preference==3);
	assert(e2.valid==TRUE);

	MeetingPreference e3(e2);
	assert(e3.id==3);
	assert(e3.timeslot==TimeBlock(10,30,30));
	assert(e3.day_of_week==SUNDAY);
	assert(e3.week_of_month==SECOND);
	assert(e3.preference==3);
	assert(e3.valid==TRUE);

	app->DisplayMessage("MeetingPreference Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void MeetingPreference::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	char *tmp = "\0\0\0\3"
				"\0\12\0\36\0\36"
				"\1\2\0\3";

	unsigned short lng = 14;
    MeetingPreference m1(tmp, lng);
	assert(lng==14);

	assert(m1.id==3);
	assert(m1.timeslot==TimeBlock(10,30,30));
	assert(m1.day_of_week==SUNDAY);
	assert(m1.week_of_month==SECOND);
	assert(m1.preference==3);
	assert(m1.valid==TRUE);

	m1.setId(-1);
	assert(m1.getId()==-1);
	assert(m1.getValid()==FALSE);
	m1.setId(0);
	assert(m1.getId()==0);
	assert(m1.getValid()==FALSE);
	m1.setId(1);
	assert(m1.getId()==1);
	assert(m1.getValid()==TRUE);

	m1.setTimeslot(TimeBlock(8,0,60));
	assert(m1.getTimeslot()==TimeBlock(8,0,60));
	assert(m1.getValid()==TRUE);

	m1.setDayOfWeek(MONDAY);
	assert(m1.getDayOfWeek()==MONDAY);
	m1.setDayOfWeek(FRIDAY);
	assert(m1.getDayOfWeek()==FRIDAY);
	assert(m1.getValid()==TRUE);

	m1.setWeekOfMonth(NO_PREF_FOR_WEEK_OF_MONTH);
	assert(m1.getWeekOfMonth()==NO_PREF_FOR_WEEK_OF_MONTH);
	assert(m1.getValid()==TRUE);
	m1.setWeekOfMonth(FIRST);
	assert(m1.getWeekOfMonth()==FIRST);
	assert(m1.getValid()==TRUE);

	app->DisplayMessage("MeetingPreference Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void MeetingPreference::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	MeetingPreference m1;
	unsigned tmp_lng = m1.getPackLng();
	assert(tmp_lng==14);

	char *tmp = "\0\0\0\3"
				"\0\12\0\36\0\36"
				"\1\2\0\3";

	unsigned short lng = 14;
    MeetingPreference m2(tmp, lng);
	assert(lng==14);

	assert(m2.id==3);
	assert(m2.timeslot==TimeBlock(10,30,30));
	assert(m2.day_of_week==SUNDAY);
	assert(m2.week_of_month==SECOND);
	assert(m2.preference==3);
	assert(m2.valid==TRUE);

	lng = m2.getPackLng();
	tmp = new char[lng];
	m2.save(tmp, lng);
	assert(lng==m2.getPackLng());

	MeetingPreference m3(tmp, lng);
	assert(lng==m3.getPackLng());

	assert(m3.id==3);
	assert(m3.timeslot==TimeBlock(10,30,30));
	assert(m3.day_of_week==1);
	assert(m3.week_of_month==2);
	assert(m3.preference==3);
	assert(m3.valid==TRUE);

	delete tmp;

	app->DisplayMessage("MeetingPreference Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void MeetingPreference::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	MeetingPreference m1;
	m1.setId(0);
	MeetingPreference m2;
	m2.setId(3);
	MeetingPreference m3;
	m3.setId(10);
	MeetingPreference m4;
	m4.setId(10);

	assert(m1<m2);
	assert(m2>m1);
	assert(m1<=m2);
	assert(m2>=m1);
	assert(m1!=m2);
	assert(m2<m3);
	assert(m3>m2);
	assert(m2<=m3);
	assert(m3>=m2);
	assert(m3!=m2);
	assert(m3==m4);
	assert(m3<=m4);
	assert(m4>=m4);

	app->DisplayMessage("MeetingPreference Test 4 complete\r\n");
}

// Test 5 - Validation functions
void MeetingPreference::test5(void)
{
	BOOL result;

	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


	MeetingPreference m1;
	m1.setId(2532);
	m1.setTimeslot(TimeBlock(14, 45, 15));
	m1.setDayOfWeek(WEDNESDAY);
	m1.setWeekOfMonth(THIRD);
	m1.setPreference(10);
	assert(m1.getValid()==TRUE);

	result=m1.setTimeslot(TimeBlock(25,0,0));
	assert(result==FALSE);
	assert(m1.getValid()==FALSE);
	result=m1.setTimeslot(TimeBlock(20,30,15));
	assert(result==TRUE);
	assert(m1.getValid()==TRUE);
	result=m1.setDayOfWeek(TUESDAY);
	assert(result==TRUE);
	assert(m1.getValid()==TRUE);
	result=m1.setWeekOfMonth(SECOND);
	assert(result==TRUE);
	assert(m1.getValid()==TRUE);
	result=m1.setWeekOfMonth(FIRST);
	assert(result==TRUE);
	assert(m1.getValid()==TRUE);

	app->DisplayMessage("MeetingPreference Test 5 complete\r\n");
}

// Test case Dispatcher
void MeetingPreference::run_tests(void)
{
	MeetingPreference::test1();
	MeetingPreference::test2();
	MeetingPreference::test3();
	MeetingPreference::test4();
	MeetingPreference::test5();
}


#endif



