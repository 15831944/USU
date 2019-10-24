/*****************************************************************************
*
*	File:          User.h
*	Class:         User
*	Version:       1.0
*	Project:       Distributed Calendar System
*	Author:        Stephen W. Clyde
*	Last Modified: September 5, 2001
*
*	Modification History:
*  	Sep. 5, 2001	Initial version
*
*	Description:
*	
*	A user object is an abstraction of a real-world user.
*
*/

#pragma once

#include <afx.h>
#include <iostream.h>
#include "DString.h"
#include "PersistentObject.h"

class User : PersistentObject
{
protected:
	DString			first_name;
	DString			last_name;
	DString			middle_names;
	DString			email_address;
	DString			office_phone;
	DString         username;
	DString			password;

public:
	// default constructor - creates an empty event object
	User(int init_id = -1) :
			 PersistentObject(init_id),
		     first_name(""),
		     last_name(""),
		     middle_names(""),
		     email_address(""),
		     office_phone(""),
			 username(""),
			 password("")
			 { validate(); }

    // Buffer-based constructor
    User(const char* buffer, unsigned short& buffer_lng)
		{ load(buffer, buffer_lng); }

	// Copy constructor
	User(const User &orig) :
			 PersistentObject(orig),
             first_name(orig.first_name),
             last_name(orig.last_name),
		     middle_names(orig.middle_names),
		     email_address(orig.email_address),
		     office_phone(orig.office_phone),
		     username(orig.username),
			 password(orig.password)
			 { validate(); }

	// Destructor
	~User() {}

    // Marshall and unmarshalling functions
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short&  buffer_lng) const;	
	unsigned short getPackLng()
		{ return sizeof(unsigned long) +
				 first_name.GetLength() + 
				 last_name.GetLength()+ 
				 middle_names.GetLength() + 
				 email_address.GetLength() + 
				 office_phone.GetLength() +
				 username.GetLength() +
				 password.GetLength() +
				 7*sizeof(short); }

    // Member set functions
    BOOL setFirstName(const DString& n) { first_name = n; return TRUE; }
    BOOL setLastName(const DString& n) { last_name = n; return TRUE; }
    BOOL setMiddleNames(const DString& n) { middle_names = n; return TRUE; }
    BOOL setEmailAddress(const DString& a) { email_address = a; return TRUE; }
    BOOL setOfficePhone(const DString& p) { office_phone = p; return TRUE; }
    BOOL setUsername(const DString& u) { username = u; return TRUE; }
    BOOL setPassword(const DString& p) { password = p; return TRUE; }

	// Member retrieve functions
	const DString& getFirstName(void) const { return first_name; }
	const DString& getLastName(void) const { return last_name; }
	const DString& getMiddleNames(void) const { return middle_names; }
	const DString& getEmailAddress(void) const { return email_address; }
	const DString& getOfficePhone(void) const { return office_phone; }
	const DString& getUsername(void) const { return username; }
	const DString& getPassword(void) const { return password; }

	// Validity check
	BOOL validate() { valid = (id>0) ? TRUE : FALSE; return valid; }

	// Comparison function and operators
	int compare(const User& a) const
		{ return (id<a.id) ? -1 : ((id>a.id) ? 1 : 0); }
	BOOL operator == (const User& a) const
	    { return (compare(a)==0) ? TRUE : FALSE; }
	BOOL operator != (const User& a) const
	    { return (compare(a)!=0) ? TRUE : FALSE; }
	BOOL operator < (const User& a) const
	    { return (compare(a)<0) ? TRUE : FALSE; }
	BOOL operator <= (const User& a) const
	    { return (compare(a)<=0) ? TRUE : FALSE; }
	BOOL operator > (const User& a) const
	    { return (compare(a)>0) ? TRUE : FALSE; }
	BOOL operator >= (const User& a) const
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
