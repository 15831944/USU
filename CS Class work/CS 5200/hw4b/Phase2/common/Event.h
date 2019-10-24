/*****************************************************************************
*
*  File:          Event.h
*  Class:         Event
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
#include "CalendarDate.h"
#include "TimeBlock.h"
#include "PersistentObject.h"

class Event : public PersistentObject
{
public:
	typedef enum { UNKNOWN='N', UNSCHEDULED='U', SCHEDULED='S' } STATUS;
	typedef enum { FACE2FACE='F', VOICE_CALL='C', VIDEO_CALL='V', ONLINE='O' } EVENT_TYPE;

protected:
	EVENT_TYPE		event_type;
	DString			name;
	DString         description;
	DString			note;
	CalendarDate	event_date;
	TimeBlock		event_time;
	long			location_id;
    STATUS          status;

public:
	// default constructor - creates an empty event object
	Event(long init_id = -1) :
	    PersistentObject(init_id),
		event_type(FACE2FACE),
		name(""),
		description(""),
		note(""),
		event_date(),
		event_time(),
		location_id(0),
		status(UNKNOWN)
		{ validate(); }

    // Buffer-based constructor
    Event(const char* buffer, unsigned short& buffer_lng)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	Event(const Event &orig) :
        PersistentObject(orig),
		event_type(orig.event_type),
		name(orig.name),
		description(orig.description),
		note(orig.note),
		event_date(orig.event_date),
		event_time(orig.event_time),
		location_id(orig.location_id),
		status(orig.status)
		{ validate(); }

	// Destructor
	~Event() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short& buffer_lng) const;	
	unsigned short getPackLng()
		{ return sizeof(long) +
				 1 + 
				 name.GetLength()+2+
				 description.GetLength()+2+
				 note.GetLength()+2+
				 event_date.getPackLng()+ 
				 event_time.getPackLng()+
				 sizeof(long)+
				 1; }

    // Member set functions
    BOOL setEventType(EVENT_TYPE new_event_type)
		{ event_type = new_event_type; return TRUE; }
    BOOL setEventType(char new_event_type)
		{ return setEventType((EVENT_TYPE) new_event_type); }
    BOOL setEventType(const CString& new_event_type)
		{  return setEventType(new_event_type[0]); }
    BOOL setName(const DString& new_name)
		{ name=new_name; name.TrimRight(); return validate(); }
    BOOL setDescription(const DString& new_description)
        { description=new_description; description.TrimRight(); return validate(); }
    BOOL setNote(const DString& new_note)
		{ note=new_note; note.TrimRight(); return validate(); }
    BOOL setDate(const CalendarDate& new_date)
        { event_date=new_date; return validate(); }
    BOOL setTime(const TimeBlock& new_time)
		{ event_time=new_time; return validate(); }
    BOOL setLocationId(long new_location_id)
		{ location_id=new_location_id; return TRUE; }
    BOOL setStatus(STATUS new_status)
		{ status = new_status; return TRUE; }
    BOOL setStatus(const DString& new_status);

	// Member retrieve functions
	EVENT_TYPE getEventType(void) { return event_type; }
	const DString& getName(void) { return name; }
	const DString& getDescription(void) const { return description; }
	const DString& getNote(void) const { return note; }
	const CalendarDate& getDate(void) const { return event_date; }
	const TimeBlock& getTime(void) const { return event_time; }
    long getLocationId(void) const { return location_id; }
    STATUS getStatus(void) const { return status; }
    STATUS getStatus(CString& str) const;

	// Validity check
	BOOL validate()
		{ valid = (id>0 && event_date.getValid()==TRUE &&
				   event_time.getValid()==TRUE) ? TRUE : FALSE; 
		  return valid; }

	// Comparison function and operators
	int compare(const Event& a) const
		{ return (id<a.id) ? -1 : (id>a.id) ? 1 : 0; }

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
	static void run_tests(void);
#endif

};
