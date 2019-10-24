/*****************************************************************************
*
*  File:          Location.h
*  Class:         Location
*  Version:       1.0
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*     An Location object represents something on someone's calender.
*/

#pragma once

#include <afx.h>
#include <iostream.h>
#include "DString.h"
#include "CalendarDate.h"
#include "TimeBlock.h"
#include "PersistentObject.h"

class Location : public PersistentObject
{
public:
	typedef enum { PHYSICAL='P', VOICE_CALL='C', VIDEO_CALL='V', ONLINE='O' } LOCATION_TYPE;

protected:
	LOCATION_TYPE	location_type;
	DString			name;
	DString			directions;

public:
	// default constructor - creates an empty Location object
	Location(int init_id = -1) :
	    PersistentObject(init_id),
		location_type(PHYSICAL),
		name(""),
		directions("")
		{ validate(); }

    // Buffer-based constructor
    Location(const char* buffer, unsigned short& buffer_lng)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	Location(const Location &orig) :
        PersistentObject(orig),
		location_type(orig.location_type),
		name(orig.name),
		directions(orig.directions)
		{ validate(); }

	// Destructor
	~Location() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short& buffer_lng) const;	
	unsigned short getPackLng()
		{ return sizeof(long) + 1 +
				 name.GetLength() + 2 +
				 directions.GetLength() + 2; }

    // Member set functions
    BOOL setLocationType(LOCATION_TYPE new_location_type)
		{ location_type = new_location_type; return TRUE; }
    BOOL setLocationType(char new_location_type)
		{ return setLocationType((LOCATION_TYPE) new_location_type); }
    BOOL setLocationType(const CString& new_location_type)
		{  return setLocationType(new_location_type[0]); }
    BOOL setName(const CString& new_name)
		{ name=new_name; name.TrimRight(); return validate(); }
    BOOL setDirections(const CString& new_directions)
		{ directions=new_directions; directions.TrimRight(); return validate(); }

	// Member retrieve functions
	LOCATION_TYPE getLocationType(void) { return location_type; }
	const DString& getName(void) { return name; }
	const DString& getDirections(void) { return directions; }

	// Validity check
	BOOL validate() { valid = (id>0) ? TRUE : FALSE; return valid; }

	// Comparison function and operators
	int compare(const Location& a) const
		{ return (id<a.id) ? -1 : (id>a.id) ? 1 : 0; }

	BOOL operator == (const Location& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const Location& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const Location& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const Location& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const Location& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const Location& a) const
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
