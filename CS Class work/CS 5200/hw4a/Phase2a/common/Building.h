/*****************************************************************************
*
*  File:          Building.h
*  Class:         Building
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
#include "PersistentObject.h"
#include "DString.h"

class Building : public PersistentObject
{
protected:
	DString			name;
	DString			street_address;
	DString         city;
	DString			state;
	DString			zip;

public:
	// default constructor - creates an empty event object
	Building(long init_id = -1) :
			PersistentObject(init_id),
			name(""),
			street_address(""),
			city(""),
			state(""),
			zip("")
			{}

    // Buffer-based constructor
    Building(const char* buffer, unsigned short& buffer_lng)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	Building(const Building &orig) :
			 PersistentObject(orig),
             name(orig.name),
		     street_address(orig.street_address),
		     city(orig.city),
		     state(orig.state),
		     zip(orig.zip)
			 {}

	// Destructor
	~Building() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short&  buffer_lng) const;	
	unsigned short getPackLng()
		{ return sizeof(unsigned long) +
				 name.GetLength()+
				 street_address.GetLength() +
				 city.GetLength() + 
				 state.GetLength() +
				 zip.GetLength() +
				 5*sizeof(unsigned short); }

    // Member set functions
    BOOL setName(const DString& n) { name = n; return validate(); }
    BOOL setAddress(const DString& a) { street_address = a; return validate(); }
    BOOL setCity(const DString& c) { city = c; return validate(); }
    BOOL setState(const DString& s) { state = s; return validate(); }
    BOOL setZip(const DString& z) { zip = z; return validate(); }

	// Member retrieve functions
	const DString& getName(void) const { return name; }
	const DString& getAddress(void) const { return street_address; }
	const DString& getCity(void) const { return city; }
	const DString& getState(void) const { return state; }
	const DString& getZip(void) const { return zip; }

	// Validation methods
	BOOL validate() { valid = (id>=0) ? TRUE : FALSE; return valid; }

	// Comparison function and operators
	int compare(const Building& a) const
		{ return (id<a.id) ? -1 : ((id>a.id) ? 1 : 0); }
	BOOL operator == (const Building& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const Building& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const Building& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const Building& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const Building& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const Building& a) const
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
