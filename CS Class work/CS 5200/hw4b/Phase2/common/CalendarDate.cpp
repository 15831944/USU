/*****************************************************************************
*
*  File:          CalendarDate.cpp
*  Class:         CalendarDate
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
#include "CalendarDate.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

int CalendarDate::max_day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*****************************************************************************
*
*   load(const char* buffer, int buffer_lng)
*
*/
BOOL CalendarDate::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	valid = FALSE;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;

    if (unmarshall(ptr, end_ptr, year)==TRUE)
	    if (unmarshall(ptr, end_ptr, month)==TRUE)
		    if (unmarshall(ptr, end_ptr, day)==TRUE)
				result = validate();

	buffer_lng = ptr - buffer;

	return result;
}

/*****************************************************************************
*
*   save(char* buffer, int buffer_lng)
*
*/
BOOL CalendarDate::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (marshall(ptr, end_ptr, year)==TRUE)
		if (marshall(ptr, end_ptr, month)==TRUE)
			result = marshall(ptr, end_ptr, day);

   buffer_lng = ptr - buffer;
   return result;
}

/******************************************************************************
*
*  Method:  CalendarDate::validate
*
*  This function checks to see if a date is valid for a given month
*
*/
BOOL CalendarDate::validate()
{
	valid=FALSE;
	if (year<=9999 && month>=1 && month<=12)
	{
		int tmp = max_day[month];
		if (month==2 && isLeapYear(year)) tmp = 29;
		if (day>=1 && day<=tmp)
			valid=TRUE;
	}
	return valid;
}

/******************************************************************************
*
*  Method:  CalendarDate::isLeapYear
*
*  This function checks to see if the year is a leap year.
*
*/
BOOL CalendarDate::isLeapYear(int year)
{
	BOOL result;
	if (year%4 != 0)
		result=FALSE;
    else if (year%400 == 0)
		result=TRUE;
	else if (year%100 == 0)
		result=FALSE;
    else
		result=TRUE;

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
void CalendarDate::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	unsigned short lng;

	CalendarDate b1;
	assert(b1.year==0);
	assert(b1.month==0);
	assert(b1.day==0);
	assert(b1.valid==FALSE);

	CalendarDate b2(1999,10,30);
	assert(b2.year==1999);
	assert(b2.month==10);
	assert(b2.day==30);
	assert(b2.valid==TRUE);

	CalendarDate b3(1999,24,30);
	assert(b3.year==1999);
	assert(b3.month==24);
	assert(b3.day==30);
	assert(b3.valid==FALSE);

	CalendarDate b4(23000,12,10);
	assert(b4.year==23000);
	assert(b4.month==12);
	assert(b4.day==10);
	assert(b4.valid==FALSE);

	lng=6;
	CalendarDate b5("\7\321\0\1\0\2", lng);
	assert(b5.year== 2001);
	assert(b5.month==1);
	assert(b5.day==2);
	assert(b5.valid==TRUE);
	assert(lng==6);

	lng=4;
	CalendarDate b6("\0\14\0\20", lng);
	assert(b6.year==12);
	assert(b6.month=16);
	assert(b6.valid==FALSE);
	assert(lng==4);

	app->DisplayMessage("CalendarDate Test 1 complete\r\n");
}

// Test 2 - Get and set methods and validate method
void CalendarDate::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	CalendarDate b1;

	b1.setYear(2000);
	assert(b1.getYear()==2000);
	assert(b1.getValid()==FALSE);

	b1.setMonth(11);
	assert(b1.getMonth()==11);
	assert(b1.getValid()==FALSE);

	b1.setDay(10);
	assert(b1.getDay()==10);
	assert(b1.getValid()==TRUE);

	b1.setDay(20);
	assert(b1.getDay()==20);
	assert(b1.getValid()==TRUE);

	b1.setDay(31);
	assert(b1.getDay()==31);
	assert(b1.getValid()==FALSE);

	b1.setDay(0);
	assert(b1.getDay()==0);
	assert(b1.getValid()==FALSE);

	assert(CalendarDate::isLeapYear(1996)==TRUE);
	assert(CalendarDate::isLeapYear(1997)==FALSE);
	assert(CalendarDate::isLeapYear(1998)==FALSE);
	assert(CalendarDate::isLeapYear(1999)==FALSE);
	assert(CalendarDate::isLeapYear(2000)==TRUE);
	assert(CalendarDate::isLeapYear(2001)==FALSE);
	assert(CalendarDate::isLeapYear(2100)==FALSE);

	app->DisplayMessage("CalendarDate Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void CalendarDate::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	CalendarDate b1(2000,10,15);
	char buffer[6];
	unsigned short buffer_lng=6;

	b1.save(buffer, buffer_lng);
	assert(buffer_lng==6);

	CalendarDate b2;
	b2.load(buffer, buffer_lng);
	
	assert(b2.getYear()==2000);
	assert(b2.getMonth()==10);
	assert(b2.getDay()==15);

	assert(b2.getPackLng()==6);

	app->DisplayMessage("CalendarDate Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void CalendarDate::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	CalendarDate b1(2000,10,15);
	CalendarDate b2(2000,11,15);
	CalendarDate b3(2001,11,19);
	CalendarDate b4(2001,11,30);
	CalendarDate b5(b4);

	assert(b1<b2);
	assert(b1<=b2);
	assert(b2>b1);
	assert(b2>=b1);
	assert(b1!=b2);
	assert(b2<b3);
	assert(b2<=b3);
	assert(b3>b2);
	assert(b3>=b2);
	assert(b2!=b3);
	assert(b3<b4);
	assert(b3<=b4);
	assert(b4>b3);
	assert(b4>=b3);
	assert(b3!=b4);

	assert(b5==b4);
	assert(b5<=b4);
	assert(b5>=b4);

	app->DisplayMessage("CalendarDate Test 4 complete\r\n");
}

// Test 5 - Test isLeapYear methog
void CalendarDate::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	assert(CalendarDate::isLeapYear(1996)==TRUE);
	assert(CalendarDate::isLeapYear(1997)==FALSE);
	assert(CalendarDate::isLeapYear(1998)==FALSE);
	assert(CalendarDate::isLeapYear(1999)==FALSE);
	assert(CalendarDate::isLeapYear(2000)==TRUE);
	assert(CalendarDate::isLeapYear(2001)==FALSE);
	assert(CalendarDate::isLeapYear(2100)==FALSE);

	CalendarDate b1(1999,2,29);
	assert(b1.valid==FALSE);

	CalendarDate b2(2000,2,29);
	assert(b2.valid==TRUE);

	app->DisplayMessage("CalendarDate Test 5 complete\r\n");
}

// Test case Dispatcher
void CalendarDate::run_tests(void)
{
	CalendarDate::test1();
	CalendarDate::test2();
	CalendarDate::test3();
	CalendarDate::test4();
	CalendarDate::test5();
}

#endif