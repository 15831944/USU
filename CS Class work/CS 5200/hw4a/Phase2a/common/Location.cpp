/*****************************************************************************
*
*	File:          Location.cpp
*	Class:         Location
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
*	This file contains the implementation and test cases for Building.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "Location.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/******************************************************************************
*
*  Method:  Location::load
*
*  This function loads a Location object from string data.
*
*  After you load a Location object, the validity of the object can be checked
*  with the isValid() method.
*/
BOOL Location::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	valid=FALSE;
	char  tmp;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;
    if (unmarshall(ptr, end_ptr, id)==TRUE)
	  if (unmarshall(ptr, end_ptr, tmp)==TRUE)
	  {
		location_type = (LOCATION_TYPE) tmp;
		if (unmarshall(ptr, end_ptr, name)==TRUE)
		  if (unmarshall(ptr, end_ptr, directions)==TRUE)
            result=validate();
	  }

	buffer_lng = ptr - buffer;

	return result;
}

/******************************************************************************
*
*  Method:  Location::save
*
*  This function save a Location object into a string.
*
*/
BOOL Location::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;
	char tmp;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (marshall(ptr, end_ptr, id)==TRUE)
	{
	  tmp = (char) location_type;
	  if (marshall(ptr, end_ptr, tmp)==TRUE)
		if (marshall(ptr, end_ptr, name)==TRUE)
		  if (marshall(ptr, end_ptr, directions)==TRUE)
            result = TRUE;
	}

	buffer_lng = ptr - buffer;
	return result;
}

#ifdef TESTING
/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <fstream.h>
#include <assert.h>

// Test 1 - Constructor
void Location::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Location e1;
	assert(e1.id==-1);
	assert(e1.location_type==PHYSICAL);
	assert(e1.name=="");
	assert(e1.directions=="");

	char *tmp = "\0\0\0\3"
				"V"
				"\0\10Old Main"
				"\0\20Testing Testing";

	unsigned short lng = 33;
    Location e2(tmp, lng);
	assert(lng==33);

	assert(e2.id==3);
	assert(e2.location_type==VIDEO_CALL);
	assert(e2.name=="Old Main");
	assert(e2.directions=="Testing Testing");

	Location e3(e2);
	assert(e3.id==3);
	assert(e3.location_type==VIDEO_CALL);
	assert(e3.name=="Old Main");
	assert(e3.directions=="Testing Testing");

	app->DisplayMessage("Location Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void Location::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Location e1;

	BOOL result;

	result=e1.setId(2532);
	assert(e1.getId()==2532);
	result=e1.setId(0);
	assert(e1.getId()==0);
	result=e1.setId(6436);
	assert(e1.getId()==6436);
	result=e1.setId(-1);
	assert(e1.getId()==-1);
	result=e1.setId(-2364);
	assert(e1.getId()==-2364);

	result=e1.setLocationType(VOICE_CALL);
	assert(e1.getLocationType()==VOICE_CALL);

	result=e1.setLocationType('P');
	assert(e1.getLocationType()==PHYSICAL);

	result=e1.setName(DString("Old Main"));
	assert(e1.getName()=="Old Main");

	result=e1.setDirections(DString("Testing"));
	assert(e1.getDirections()=="Testing");
	result=e1.setDirections(DString(""));
	assert(e1.getDirections()=="");
	result=e1.setDirections(DString("Testing Testing"));
	assert(e1.getDirections()=="Testing Testing");

	app->DisplayMessage("Location Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void Location::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	BOOL result;

	Location e0;
	unsigned tmp_lng = e0.getPackLng();
	assert(tmp_lng==9);

	Location e1;
	result=e1.setId(2532);
	result=e1.setLocationType(VOICE_CALL);
	result=e1.setName(CString("Old Main"));
	result=e1.setDirections(CString("Go up the hill"));

	unsigned short lng = e1.getPackLng();
	char *tmp = new char[lng];
	e1.save(tmp, lng);
	assert(lng==e1.getPackLng());

	Location e2(tmp, lng);
	assert(lng==e1.getPackLng());

	assert(e2.getId()==2532);
	assert(e2.getLocationType()==VOICE_CALL);
	assert(e2.getName()=="Old Main");
	assert(e2.getDirections()=="Go up the hill");

	delete tmp;

	app->DisplayMessage("Location Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void Location::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Location e1;
	e1.setId(0);
	Location e2;
	e2.setId(3);
	Location e3;
	e3.setId(10);
	Location e4;
	e4.setId(10);

	assert(e1<e2);
	assert(e2>e1);
	assert(e1<=e2);
	assert(e2>=e1);
	assert(e1!=e2);
	assert(e2<e3);
	assert(e3>e2);
	assert(e2<=e3);
	assert(e3>=e2);
	assert(e3!=e2);
	assert(e3==e4);
	assert(e3<=e4);
	assert(e4>=e4);

	app->DisplayMessage("Location Test 4 complete\r\n");
}

// Test 5 - Validation functions
void Location::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	BOOL result;

	Location e1;
	result=e1.setId(2532);
	result=e1.setLocationType(VOICE_CALL);
	result=e1.setName(CString("Old Main"));
	result=e1.setDirections(CString("Up to the hill"));

	assert(e1.getValid()==TRUE);
	result=e1.setId(-1);
	assert(result==FALSE);
	assert(e1.getValid()==FALSE);
	result=e1.setId(3);
	assert(result==TRUE);
	assert(e1.getValid()==TRUE);

	app->DisplayMessage("Location Test 5 complete\r\n");
}

// Test case Dispatcher
void Location::run_tests(void)
{
	Location::test1();
	Location::test2();
	Location::test3();
	Location::test4();
	Location::test5();
}

#endif



