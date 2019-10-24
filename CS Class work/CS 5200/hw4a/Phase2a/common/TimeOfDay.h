/*****************************************************************************
*
*  File:          TimeOfDay.h
*  Class:         TimeOfDay
*  Version:       1.0
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*     An event object represents something on someone's calender.
*/

#pragma once

#include <afx.h>
#include <iostream.h>
#include "DString.h"

const int MAX_MINUTES_PER_HOURS = 60;
const int MAX_HOURS_PER_DAYS =24;

class TimeOfDay
{
protected:
	unsigned short	hours;
	unsigned short	minutes;
	BOOL			valid;

public:
	// Basic constructor - creates an empty event object
	TimeOfDay(unsigned short h=0, unsigned short m=0) :
		hours(h), minutes(m), valid(FALSE) { validate(); }

    // String-based constructor
	TimeOfDay(const char* buffer, unsigned short& buffer_lng) :
		hours(0), minutes(0), valid(FALSE)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	TimeOfDay(const TimeOfDay &orig) :
		hours(orig.hours), minutes(orig.minutes)
		{ validate(); }

	// Destructor
	~TimeOfDay() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short&  buffer_lng) const;
	unsigned short getPackLng() { return sizeof(unsigned short)*2; }

    // Member set functions
	BOOL setHours(unsigned short h) { hours=h; return validate(); }
    BOOL setMinutes(unsigned short m)  { minutes=m; return validate(); }
	BOOL validate()
		{ valid = (hours<24 && minutes<60) ? TRUE : FALSE; return valid; }

	// Member retrieve functions
	unsigned short getHours(void) const { return hours; }
	unsigned short getMinutes(void) const { return minutes; }
	BOOL getValid(void) const { return valid; }

	// Comparison function and operators
	int compare(const TimeOfDay& a) const
		{	int tmp = compareHours(a);
			if (tmp==0) tmp = compareMinutes(a);
			return tmp; }
	int compareHours(const TimeOfDay& a) const
		{	return (hours<a.hours) ? -1 : ((hours>a.hours) ? 1 : 0); }
	int compareMinutes(const TimeOfDay& a) const
		{	return (minutes<a.minutes) ? -1 : ((minutes>a.minutes) ? 1 : 0); }

	BOOL operator == (const TimeOfDay& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const TimeOfDay& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const TimeOfDay& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const TimeOfDay& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const TimeOfDay& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const TimeOfDay& a) const
	    { return (compare(a)>=0) ? TRUE : FALSE; }

#ifdef TESTING

public:
	static void test1(void);
	static void test2(void);
	static void test3(void);
	static void test4(void);
	static void run_tests(void);
#endif

};
