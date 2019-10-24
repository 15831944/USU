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

class MeetingPreference
{
public:
	typedef enum
				{	NO_DAY_OF_WEEK,
					SUNDAY,
					MONDAY,
					TUESDAY,
					WEDNESDAY,
					THURSDAY,
					FRIDAY,
					SATURDAY
				} DAY_OF_WEEK;

protected:
	int				id;
	TimeBlock		timeslot;
	DAY_OF_WEEK		day_of_week;
	int				week_of_month;
	int				preference;

public:
	// default constructor - creates an empty event object
	MeetingPreference(void) :
			id(0),
			timeslot(),
		    day_of_week(NO_DAY_OF_WEEK),
		    week_of_month(0),
		    preference(0)
			{}

	// Parameterized constructor
	MeetingPreference(const TimeBlock& tb, DAY_OF_WEEK d=NO_DAY_OF_WEEK, int w=0, int p=0) :
			id(0),
			timeslot(tb),
			day_of_week(d),
			week_of_month(w),
			preference(p) {}

    // String-based constructor - creates an event object using the
	// information found in a marshalled string representation of an
	// event object.
    MeetingPreference(const DString &data) { load(data); }

	// Copy constructor
	MeetingPreference(const MeetingPreference &orig) :
			 id(orig.id),
             timeslot(orig.timeslot),
		     day_of_week(orig.day_of_week),
		     week_of_month(orig.week_of_month),
		     preference(orig.preference)
			 {}

	// input stream constructor
	MeetingPreference(istream& in)	{ load(in); }

	// Destructor
	~MeetingPreference() {}

    // Marshall and unmarshalling functions
	BOOL load(const DString &data);
    BOOL load(istream& in);
	BOOL save(DString &data) const;	
	BOOL save(ostream& out);

    // Member set functions
	BOOL setId(long i) { id=i; }
    BOOL setTimeslot(const TimeBlock& t) { timeslot = t; }
    BOOL setDayOfWeek(DAY_OF_WEEK d) { day_of_week = d; }
    BOOL setWeekOfMonth(int w) { week_of_month = w; }
    BOOL setPreference(int p) { preference = p; }

	// Member retrieve functions
	long getId(void) const { return id; }
	const TimeBlock& getTimeslot(void) const { return timeslot; }
	DAY_OF_WEEK getDayOfWeek(void) const { return day_of_week; }
	int getWeekOfMonth(void) const { return week_of_month; }
	int getPreference(void) const { return preference; }

	// Comparison function and operators
	int compare(const MeetingPreference& a) const
		{ return (id==a.id) ? 0 : ((id<a.id) ? < -1 : 1); }
	BOOL operator == (const Event& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const Event& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const Event& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const Event& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const Event& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const Event& a) const
	    { return (compare(a)>=0) ? TRUE : FALSE; }

#ifdef TESTING

public:
	static void test1(void);
	static void test2(void);
	static void test3(void);
	static void test4(void);
	static void test5(void);
#endif

};
