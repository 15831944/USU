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

class Event
{
public:
	typedef enum { UNKNOWN, UNSCHEDULED, SCHEDULED } STATUS;
	typedef enum { FACE2FACE='F', VOICE_CALL='C', VIDEO_CALL='V', ONLINE='O' } EVENT_TYPE;

protected:
	long            id;
	EVENT_TYPE		event_type;
	DString			name;
	DString         description;
	DString			note;
	CTime			date_time;
	short			duration;
	long			location_id;
    STATUS          status;

	static int		max_day[13];

public:
	// The following constant define the length of various fields in the
	// data string used in the load and save operations.

	static const int ID_LNG;
	static const int EVENT_TYPE_LNG;
	static const int NAME_LNG;
	static const int DESCRIPTION_LNG;
	static const int NOTE_LNG;
	static const int DATE_TIME_LNG;
	static const int DURATION_LNG;
	static const int LOCATION_ID_LNG;
	static const int STATUS_LNG;
	static const int LNG;  

public:
	// default constructor - creates an empty event object
	Event(void) :
	         id(0),
		     event_type(FACE2FACE),
		     name(""),
		     description(""),
		     note(""),
		     date_time(),
		     duration(0),
		     location_id(0),
		     status(UNKNOWN)
			 {}

    // String-based constructor - creates an event object using the
	// information found in a marshalled string representation of an
	// event object.
    Event(const DString &data) { load(data); }

	// Copy constructor
	Event(const Event &orig) :
             id(orig.id),
		     event_type(orig.event_type),
		     name(orig.name),
		     description(orig.description),
		     note(orig.note),
		     date_time(orig.date_time),
		     duration(orig.duration),
		     location_id(orig.location_id),
			 status(orig.status) {}

	// input stream constructor
	Event(istream& in)	{ load(in); }

	// Destructor
	~Event() {}

    // Marshall and unmarshalling functions
	BOOL load(const DString &data);
    BOOL load(istream& in);
	BOOL save(DString &data) const;	
	BOOL save(ostream& out);

    // Member set functions
    BOOL setId(long new_id)
		{ if (new_id>=0)
          {
		    id=new_id;
            return TRUE;
          }
          else 
            return FALSE;
	    }
    BOOL setEventType(EVENT_TYPE new_event_type)
		{ event_type = new_event_type;
          return TRUE;
		}
    BOOL setEventType(char new_event_type)
		{ return setEventType((EVENT_TYPE) new_event_type); }
    BOOL setEventType(const CString& new_event_type)
		{  return setEventType(new_event_type[0]); }
    BOOL setName(const CString& new_name)
        { name=new_name.Left(NAME_LNG);
		  name.TrimRight();
          return TRUE; }
    BOOL setDescription(const CString& new_description)
        { description=new_description.Left(DESCRIPTION_LNG);
		  description.TrimRight();
          return TRUE; }
    BOOL setNote(const CString& new_note)
        { note=new_note.Left(NOTE_LNG);
		  note.TrimRight();
          return TRUE; }
    BOOL setDateTime(const CTime& new_date_time)
        { date_time=new_date_time;
          return TRUE; }
    BOOL setDateTime(int nYear, int nMonth, int nDay, int nHour=0, int nMin=0, int nSec=0, int nDST = -1)
        { 
		  BOOL result=FALSE;
		  if (checkDate(nYear,nMonth,nDay) && checkTime(nHour, nMin, nSec))
		  {
			date_time=CTime(nYear, nMonth, nDay, nHour, nMin, nSec, nDST);
			result=TRUE;
		  }
          return result;
		}
	BOOL setDateTime(const CString& new_date_time);
    BOOL setDuration(short new_duration)
		{
		  if (new_duration>=0)
		  {
		    duration = new_duration;
            return TRUE;
		  }
	      else
			return FALSE;
		}
    BOOL setDuration(const CString& new_duration)
		{ DString tmp(new_duration);
		  return setDuration((short) tmp); }
    BOOL setLocationId(long new_location_id)
		{
		  if (new_location_id>=0)
          {
		    location_id=new_location_id;
            return TRUE;
          }
          else 
            return FALSE;
        }
	BOOL setLocationId(const CString& new_location_id)
		{ DString tmp(new_location_id);
		  return setLocationId((short) tmp); }
    BOOL setStatus(STATUS new_status)
		{ status = new_status;
          return TRUE; }
    BOOL setStatus(const CString& new_status);

	// Member retrieve functions
	long getId(void) const { return id; } 
	EVENT_TYPE getEventType(void) { return event_type; }
	const DString& getName(void) { return name; }
	const DString& getDescription(void) const { return description; }
	const DString& getNote(void) const { return note; }
	const CTime& getDateTime(void) const { return date_time; }
	const CTime& getDateTime(CString& str) const;
    short getDuration(void) const { return duration; }
    long getLocationId(void) const { return location_id; }
    STATUS getStatus(void) const { return status; }
    STATUS getStatus(CString& str) const;
	static const char * GetEventTypeName(EVENT_TYPE event_type)
	{
		switch(event_type)
		{
		case FACE2FACE: return "Face to face";
		case VOICE_CALL: return "Voice call";
		case VIDEO_CALL: return "Video call";
		case ONLINE: return "Online";
		default: return NULL;
		}
	}
	static const char * GetStatusName(STATUS status)
	{
		switch(status)
		{
		case UNKNOWN: return "Unknown";
		case UNSCHEDULED: return "Unscheduled";
		case SCHEDULED: return "Scheduled";
		default: return NULL;
		} 
	}
	// Validity check
	BOOL isValid(void) const
	    { return (status!=UNKNOWN) ? TRUE : FALSE; }
	static BOOL checkTime(int hours, int minutes, int seconds);
	static BOOL checkDate(int year, int month, int day);
	static BOOL isLeapYear(int year);
	
	// Comparison function and operators
	int compare(const Event& a) const;
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
	static void test6(void);
#endif

};
