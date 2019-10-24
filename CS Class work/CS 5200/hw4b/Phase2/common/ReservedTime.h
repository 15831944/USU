/*****************************************************************************
*
*  File:          ReservedTime.h
*  Class:         ReservedTime
*  Version:       1.0
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*     An ReservedTime object represents something on someone's calender.
*/

#pragma once

#include <afx.h>
#include <iostream.h>
#include "DString.h"
#include "CalendarDate.h"
#include "TimeBlock.h"
#include "PersistentObject.h"

class ReservedTime : public PersistentObject
{
protected:
	DString			label;
	CalendarDate	ReservedTime_date;
	TimeBlock		ReservedTime_time;

public:
	// default constructor - creates an empty ReservedTime object
	ReservedTime(int init_id = -1) :
	    PersistentObject(init_id),
		label(""),
		ReservedTime_date(),
		ReservedTime_time()
		{ validate(); }

    // Buffer-based constructor
    ReservedTime(const char* buffer, unsigned short& buffer_lng)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	ReservedTime(const ReservedTime &orig) :
        PersistentObject(orig),
		label(orig.label),
		ReservedTime_date(orig.ReservedTime_date),
		ReservedTime_time(orig.ReservedTime_time)
		{ validate(); }

	// Destructor
	~ReservedTime() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short& buffer_lng) const;	
	unsigned short getPackLng()
		{ return sizeof(long) +
				 label.GetLength()+2+
				 ReservedTime_date.getPackLng()+ 
				 ReservedTime_time.getPackLng(); }

    // Member set functions
    BOOL setlabel(const DString& new_label)
		{ label=new_label; label.TrimRight(); return validate(); }
    BOOL setDate(const CalendarDate& new_date)
        { ReservedTime_date=new_date; return validate(); }
    BOOL setTime(const TimeBlock& new_time)
		{ ReservedTime_time=new_time; return validate(); }

	// Member retrieve functions
	const DString& getlabel(void) { return label; }
	const CalendarDate& getDate(void) const { return ReservedTime_date; }
	const TimeBlock& getTime(void) const { return ReservedTime_time; }

	// Validity check
	BOOL validate()
		{ valid = (id>0 && ReservedTime_date.getValid()==TRUE &&
				   ReservedTime_time.getValid()==TRUE) ? TRUE : FALSE; 
		  return valid; }

	// Comparison function and operators
	int compare(const ReservedTime& a) const
		{ return (id<a.id) ? -1 : (id>a.id) ? 1 : 0; }

	BOOL operator == (const ReservedTime& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const ReservedTime& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const ReservedTime& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const ReservedTime& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const ReservedTime& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const ReservedTime& a) const
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
