/*****************************************************************************
*
*  File:          ParcelAddress.h
*  Class:         ParcelAddress
*  Project:       Parcel Tracker
*  Author:        Stephen W. Clyde
*  Last Modified: August 14, 1997
*
*  Modification History:
*     Aug 14, 97  Initial version
*
*  Description:
*     A ParcelAddress is a postal address.
*
*/

#ifndef  __PARCELADDRESS_H__
#define  __PARCELADDRESS_H__


#ifndef _MSC_VER
#include "bool.h"
#endif

#include "iostream.h"
#include "DString.h"

class ParcelAddress
{
private:
	DString          name;
	DString          org;
	DString          street; 
	DString          city; 
	DString          state;
	DString          zip;

public:
	// The following constant define the length of various fields in the
	// data string used in the load and save operations.
	static const int NAME_LNG;
	static const int ORG_LNG;
	static const int STREET_LNG;
	static const int CITY_LNG;
	static const int STATE_LNG;
	static const int ZIP_LNG;
	static const int LNG;  

public:
	// default constructor - creates an empty parcel address object
	ParcelAddress(void) {}

    // String-based constructor - creates a parcel address using the
	// information found in a marshalled string representation of a
	// parcel address.
    ParcelAddress(const DString &data) { load(data); }

	// Copy constructor
	ParcelAddress(const ParcelAddress &orig) :
             name(orig.name),
             org(orig.org),
			 street(orig.street),
		     city(orig.city),
		     state(orig.state),
		     zip(orig.zip) {}

	// input stream constructor
	ParcelAddress::ParcelAddress(istream& in){ load(in); }

	// Destructor
	~ParcelAddress() {}

    // Marshall and unmarshalling functions
	BOOL load(const DString& data);
	BOOL load(istream& in);
	BOOL save(DString &data) const;	
	BOOL save(ostream& out) const;
	
    // Member set functions
    BOOL setName(const DString& new_name)
		{ name=new_name.Left(NAME_LNG); return TRUE; }
    BOOL setOrg(const DString& new_org)
		{ org=new_org.Left(ORG_LNG); return TRUE; }
    BOOL setStreet(const DString& new_street)
		{ street=new_street.Left(STREET_LNG); return TRUE; }
    BOOL setCity(const DString& new_city)
		{ city=new_city.Left(CITY_LNG); return TRUE; }
    BOOL setState(const DString& new_state)
		{ state=new_state.Left(STATE_LNG); return TRUE; }
    BOOL setZip(const DString& new_zip)
		{ zip=new_zip.Left(ZIP_LNG); return TRUE; }


	// Member retrieve functions
	const DString& getName(void) const { return name; }
	const DString& getOrg(void) const { return org; }
	const DString& getStreet(void) const { return street; }
	const DString& getCity(void) const { return city; }
	const DString& getState(void) const { return state; }
	const DString& getZip(void) const { return zip; }

	// Validity check
	BOOL isValid(void) const
	    { return ( !name.IsEmpty() &&
	               !city.IsEmpty() &&
	               !state.IsEmpty() && 
                       !zip.IsEmpty()) ? TRUE : FALSE; }

	// Comparison function and operators
	int compare(const ParcelAddress& a) const;
	BOOL operator == (const ParcelAddress& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const ParcelAddress& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const ParcelAddress& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const ParcelAddress& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const ParcelAddress& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const ParcelAddress& a) const
	    { return (compare(a)>=0) ? TRUE : FALSE; }

#ifdef TESTING_PARCEL_ADDRESS
public:
	static void test1(void);
	static void test2(void);
	static void test3(void);
	static void test4(void);
	static void test5(void);
	static void test6(void);
#endif

};

#endif
