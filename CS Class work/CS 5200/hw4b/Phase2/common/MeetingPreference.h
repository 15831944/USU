/*****************************************************************************
*
*  File:          MeetingPreference.h
*  Class:         MeetingPreference
*  Version:       1.0
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*
*	Sep. 5, 2001	Initial version
*
*  Description:
*
*	A MeetingPreference object is particular time when a person prefers
*	or doesn't prefers to have things scheduled.
*
*	A MeeetingPreference is defined with the following:
*
*		timeslot		- the starting time and duration of the time
*						  slot for which preferences are being defined.
*						  A timeslot must be given for an MeetingPreference
*		day_of_week		- a preference for a particular day of week.  See
*						  DAY_OF_WEEK date type for possible values.
*		week_of_month	- a preference for a particular day of the month,
*						  between 0 and 5.  A 0 means no week of month
*						  preference.
*
*	The id field contains a unique identify for the timeslot.  The value
*	is assigned and maintained by the calendar manager.
*
*/

#pragma once

#include <afx.h>
#include <iostream.h>
#include "DString.h"
#include "TimeBlock.h"
#include "PersistentObject.h"

class MeetingPreference : public PersistentObject
{
public:
	typedef enum { NO_PREF_FOR_DAY_OF_WEEK=0, SUNDAY=1, MONDAY=2, TUESDAY=3, WEDNESDAY=4, THURSDAY=5, FRIDAY=6, SATURDAY=7 } DAY_OF_WEEK;
	typedef enum { NO_PREF_FOR_WEEK_OF_MONTH=0, FIRST=1, SECOND=2, THIRD=3, FOURTH=4, FIFTH=5} WEEK_OF_MONTH;

protected:
	TimeBlock		timeslot;
	DAY_OF_WEEK		day_of_week;
	WEEK_OF_MONTH	week_of_month;
	unsigned short	preference;

public:
	// default constructor - creates an empty event object
	MeetingPreference(long init_id = -1) :
			PersistentObject(init_id),
			timeslot(),
		    day_of_week(NO_PREF_FOR_DAY_OF_WEEK),
		    week_of_month(NO_PREF_FOR_WEEK_OF_MONTH),
		    preference(0)
			{ valid = validate(); }

	// Parameterized constructor
	MeetingPreference(const TimeBlock& tb, DAY_OF_WEEK d=NO_PREF_FOR_DAY_OF_WEEK, WEEK_OF_MONTH w=NO_PREF_FOR_WEEK_OF_MONTH, unsigned short p=0) :
			PersistentObject(),
			timeslot(tb),
			day_of_week(d),
			week_of_month(w),
			preference(p)
			{ valid = validate(); }

    // String-based constructor - creates an event object using the
	// information found in a marshalled string representation of an
	// event object.
    MeetingPreference(const char* buffer, unsigned short buffer_lng)
			{ load(buffer, buffer_lng); }

	// Copy constructor
	MeetingPreference(const MeetingPreference &orig) :
			 PersistentObject(orig),
             timeslot(orig.timeslot),
		     day_of_week(orig.day_of_week),
		     week_of_month(orig.week_of_month),
		     preference(orig.preference)
			 { valid = validate(); }

	// Destructor
	~MeetingPreference() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short& buffer_lng) const;
	unsigned short getPackLng()
		{ return sizeof(unsigned long) +
				 timeslot.getPackLng()+
				 sizeof(char) +
				 sizeof(unsigned char) + 
				 sizeof(unsigned short); }


    // Member set functions
    BOOL setTimeslot(const TimeBlock& t) { timeslot = t; return validate(); }
    BOOL setDayOfWeek(DAY_OF_WEEK d) { day_of_week = d; return validate(); }
    BOOL setWeekOfMonth(WEEK_OF_MONTH w) { week_of_month = w; return validate(); }
    BOOL setPreference(unsigned short p) { preference = p; return validate(); }

	// Member retrieve functions
	long getId(void) const { return id; }
	const TimeBlock& getTimeslot(void) const { return timeslot; }
	DAY_OF_WEEK getDayOfWeek(void) const { return day_of_week; }
	WEEK_OF_MONTH getWeekOfMonth(void) const { return week_of_month; }
	int getPreference(void) const { return preference; }

	// Validity check
	BOOL validate()
		{ valid = (id>0 && timeslot.getValid()==TRUE &&
				   day_of_week>=0 && day_of_week<=7 &&
				   week_of_month>=0 && week_of_month<=5) ? TRUE : FALSE; 
		  return valid; }

	// Comparison function and operators
	int compare(const MeetingPreference& a) const
		{ return (id==a.id) ? 0 : ((id<a.id) ? -1 : 1); }
	BOOL operator == (const MeetingPreference& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const MeetingPreference& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const MeetingPreference& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const MeetingPreference& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const MeetingPreference& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const MeetingPreference& a) const
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
