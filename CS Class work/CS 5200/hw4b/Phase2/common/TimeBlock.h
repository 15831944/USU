/*****************************************************************************
*
*	File:          TimeBlock.h
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
*	A time block object include a starting time and a duration.  The
*	duration is defined in minutes.
*
*/

#pragma once

#include <afx.h>
#include <iostream.h>
#include "TimeOfDay.h"

class TimeBlock
{
protected:
	TimeOfDay		starting_time;
	unsigned short	duration;
	BOOL			valid;

public:
	// default constructor - creates an empty event object
	TimeBlock(unsigned short h=0, unsigned short m=0, unsigned short d=0) :
		starting_time(h, m),
		duration(d)
		{ validate(); }

    // Buffer-based constructor
    TimeBlock(const char* buffer, unsigned short& buffer_lng)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	TimeBlock(const TimeBlock &orig) :
		starting_time(orig.starting_time),
        duration(orig.duration)
		{ validate(); }

	// Destructor
	~TimeBlock() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short&  buffer_lng) const;	
	unsigned short getPackLng()
		{ return starting_time.getPackLng() +
				 sizeof(unsigned short); }

    // Member set functions
	BOOL setStartingTime(const TimeOfDay &t) { starting_time=t; return validate(); }
    BOOL setDuration(unsigned short d) { duration = d; return validate(); }

	// Member retrieve functions
	const TimeOfDay& getStartingTime(void) const { return starting_time; }
	unsigned short getDuration(void) const { return duration; }

	// Validation functions
	BOOL validate(void) { valid = starting_time.getValid(); return valid; }
	BOOL getValid(void) const { return valid; }

	// Assignment operator
	operator = (const TimeBlock& t)
		{
			starting_time = t.starting_time;
			duration = t.duration;
			validate();
		}

	// Comparison function and operators
	int compare(const TimeBlock& a) const
		{	int tmp = starting_time.compare(a.getStartingTime());
			if (tmp==0) tmp = compareDuration(a);
			return tmp; }
	int compareDuration(const TimeBlock& a) const
		{	return (duration<a.duration) ? -1 : ((duration>a.duration) ? 1 : 0); }
	BOOL operator == (const TimeBlock& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const TimeBlock& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const TimeBlock& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const TimeBlock& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const TimeBlock& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const TimeBlock& a) const
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
