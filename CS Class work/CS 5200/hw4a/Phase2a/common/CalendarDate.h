/*****************************************************************************
*
*  File:          CalendarDate.h
*  Class:         CalendarDate
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*     Sep 5, 2001  Initial version
*
*  Description:
*     A CalendarDate is a simple date used to indicate which day an
*	  event occurs.
*
*/

#pragma once

#include <stdlib.h>
#include <string.h>

#include <afx.h>

class CalendarDate
{
protected:
	unsigned short	year;
	unsigned short	month;
	unsigned short	day;
	BOOL			valid;

	static int		max_day[13];

public:
	// Inherited constructors
    CalendarDate(int y=0, int m=0, int d=0):
	    year(y), month(m), day(d)
		{ validate(); }

    // Buffer-based constructor
    CalendarDate(const char* buffer, unsigned short& buffer_lng)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	CalendarDate(const CalendarDate &orig) :
		year(orig.year), month(orig.month), day(orig.day)
		{ validate(); }

	// Destructor
	~CalendarDate() {}

	// Load and save methods
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short& buffer_lng) const;
	unsigned short getPackLng()
		{ return sizeof(unsigned short)*3; }

    // Member set functions
	BOOL setYear(int y) { year=y; return validate(); }
	BOOL setMonth(int m) { month=m; return validate(); }
	BOOL setDay(int d) { day=d; return validate(); }

	// Member retrieve functions
	unsigned short getYear(void) const { return year; }
	unsigned short getMonth(void) const { return month; }
	unsigned short getDay(void) const { return day; }

	// Validation functions
	BOOL validate();
	BOOL getValid(void) const { return valid; }
	static BOOL isLeapYear(int year);

	// Comparison function and operators
	int compare(const CalendarDate& a) const
		{	int tmp = compareYear(a);
			if (tmp==0) tmp = compareMonth(a);
			if (tmp==0) tmp = compareDay(a);
			return tmp; }
	int compareYear(const CalendarDate& a) const
		{	return (year<a.year) ? -1 : ((year>a.year) ? 1 : 0); }
	int compareMonth(const CalendarDate& a) const
		{	return (month<a.month) ? -1 : ((month>a.month) ? 1 : 0); }
	int compareDay(const CalendarDate& a) const
		{	return (day<a.day) ? -1 : ((day>a.day) ? 1 : 0); }

	BOOL operator == (const CalendarDate& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const CalendarDate& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const CalendarDate& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const CalendarDate& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const CalendarDate& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const CalendarDate& a) const
	    { return (compare(a)>=0) ? TRUE : FALSE; }



#ifdef TESTING
public:
	static void test1(void);
	static void test2(void);
	static void test3(void);
	static void test4(void);
	static void test5(void);
	static void run_tests(void);
#endif

};
