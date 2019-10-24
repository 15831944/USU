/*****************************************************************************
*
*  File:          Calendar.h
*  Class:         Calendar
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
#include "TimeOfDay.h"
#include "PersistentObject.h"

class Calendar : public PersistentObject
{
protected:
	TimeOfDay		day_start_time;
	TimeOfDay		day_end_time;

public:
	// default constructor - creates an empty event object
	Calendar(long calendar_id = -1) :
			 PersistentObject(calendar_id),
		     day_start_time(8,0),
		     day_end_time(17,0)
			 { validate(); }

    // Buffer-based constructor
    Calendar(const char* buffer, unsigned short& buffer_lng)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	Calendar(const Calendar &orig) :
			 PersistentObject(orig),
             day_start_time(orig.day_start_time),
             day_end_time(orig.day_end_time)
			 { validate(); }

	// Destructor
	~Calendar() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short& buffer_lng) const;	
	unsigned short getPackLng()
		{ return sizeof(unsigned long) +
				 day_start_time.getPackLng() +
				 day_end_time.getPackLng(); }

    // Member set functions
    BOOL setStartTime(TimeOfDay t) { day_start_time = t; return validate(); }
    BOOL setEndTime(TimeOfDay t) { day_end_time = t; return validate(); }

	// Member retrieve functions
	const TimeOfDay& getStartTime(void) const { return day_start_time; }
	const TimeOfDay& getEndTime(void) const { return day_end_time; }

	// Validation functions
	BOOL validate()
		{ valid = (id>0 && day_start_time.getValid()==TRUE &&
				   day_end_time.getValid()==TRUE) ? TRUE : FALSE; return valid; }

	// Comparison function and operators
	int compare(const Calendar& a) const
		{ return (id==a.id) ? 0 : ((id<a.id) ? -1 : 1); }
	BOOL operator == (const Calendar& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const Calendar& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const Calendar& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const Calendar& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const Calendar& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const Calendar& a) const
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
