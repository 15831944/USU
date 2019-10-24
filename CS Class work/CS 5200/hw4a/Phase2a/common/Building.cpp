/*****************************************************************************
*
*	File:          Building.cpp
*	Class:         Building
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
#include "Building.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/*****************************************************************************
*
*   load(const char* buffer, int buffer_lng)
*
*/
BOOL Building::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	valid = FALSE;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;
    if (unmarshall(ptr, end_ptr, id)==TRUE)
	    if (unmarshall(ptr, end_ptr, name)==TRUE)
		    if (unmarshall(ptr, end_ptr, street_address)==TRUE)
                if (unmarshall(ptr, end_ptr, city)==TRUE)
                    if (unmarshall(ptr, end_ptr, state)==TRUE)
                        if (unmarshall(ptr, end_ptr, zip)==TRUE)
							result = validate();

	buffer_lng = ptr - buffer;

	return result;
}

/*****************************************************************************
*
*   save(char* buffer, int buffer_lng)
*
*/
BOOL Building::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (marshall(ptr, end_ptr, id)==TRUE)
	    if (marshall(ptr, end_ptr, name)==TRUE)
            if (marshall(ptr, end_ptr, street_address)==TRUE)
                if (marshall(ptr, end_ptr, city)==TRUE)
                    if (marshall(ptr, end_ptr, state)==TRUE)
                        result = marshall(ptr, end_ptr, zip);

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
void Building::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	unsigned short lng;

	Building b1;
	assert(b1.getId()==-1);
	assert(b1.name=="");
	assert(b1.street_address=="");
	assert(b1.city=="");
	assert(b1.state=="");
	assert(b1.zip=="");

	lng=38;
	Building b2("\0\0\0\2\0\3aaa\0\4bbbb\0\5ccccc\0\2UT\0\01212345-6789", lng);
	assert(b2.getId()==2);
	assert(b2.name=="aaa");
	assert(b2.street_address=="bbbb");
	assert(b2.city=="ccccc");
	assert(b2.state=="UT");
	assert(b2.zip=="12345-6789");
	assert(lng==38);

	lng=14;
	Building b3("\0\0\2\2\0\0\0\0\0\0\0\0\0\0", lng);
	assert(b3.getId()==514);
	assert(b3.name=="");
	assert(b3.street_address=="");
	assert(b3.city=="");
	assert(b3.state=="");
	assert(b3.zip=="");
	assert(lng==14);

	lng=10;
	Building b4("\0\0\0\2\0\3aaa\0\4bbbb\0\5ccccc\0\2UT\0\01212345-6789", lng);
	assert(b4.getId()==2);
	assert(b4.name=="aaa");
	assert(b4.street_address=="");
	assert(b4.city=="");
	assert(b4.state=="");
	assert(b4.zip=="");
	assert(lng==9);

	Building b5(b2);
	assert(b5.getId()==2);
	assert(b5.name=="aaa");
	assert(b5.street_address=="bbbb");
	assert(b5.city=="ccccc");
	assert(b5.state=="UT");
	assert(b5.zip=="12345-6789");

	app->DisplayMessage("Building Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void Building::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Building b1;
	assert(b1.getId()==-1);
	assert(b1.name=="");
	assert(b1.street_address=="");
	assert(b1.city=="");
	assert(b1.state=="");
	assert(b1.zip=="");

	b1.setId(45);
	assert(b1.getId()==45);
	b1.setName("Old Main");
	assert(b1.getName()=="Old Main");
	b1.setAddress("600 North 800 East");
	assert(b1.getAddress()=="600 North 800 East");
	b1.setCity("Logan");
	assert(b1.getCity()=="Logan");
	b1.setState("UT");
	assert(b1.getState()=="UT");
	b1.setZip("84322-4205");
	assert(b1.getZip()=="84322-4205");

	b1.setId(0);
	assert(b1.getId()==0);
	b1.setName("");
	assert(b1.getName()=="");
	b1.setAddress("");
	assert(b1.getAddress()=="");
	b1.setCity("");
	assert(b1.getCity()=="");
	b1.setState("");
	assert(b1.getState()=="");
	b1.setZip("");
	assert(b1.getZip()=="");

	b1.setId(-1);
	assert(b1.getId()==-1);
	b1.setName("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	assert(b1.getName()=="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	b1.setAddress("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	assert(b1.getAddress()=="bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	b1.setCity("cccccccccccc");
	assert(b1.getCity()=="cccccccccccc");
	b1.setState("ddddddddddddddd");
	assert(b1.getState()=="ddddddddddddddd");
	b1.setZip("eeeeeeeeeee");
	assert(b1.getZip()=="eeeeeeeeeee");

	app->DisplayMessage("Building Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void Building::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Building b1;
	b1.setId(-1);
	b1.setName("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	b1.setAddress("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	b1.setCity("cccccccccccc");
	b1.setState("ddddddddddddddd");
	b1.setZip("eeeeeeeeeee");

	char buffer[1024];
	unsigned short buffer_lng=1024;

	b1.save(buffer, buffer_lng);
	assert(buffer_lng>0);
	assert(b1.getPackLng()==buffer_lng);

	Building b2;
	b2.load(buffer, buffer_lng);
	
	assert(b2.getId()==-1);
	assert(b2.getName()=="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	assert(b2.getAddress()=="bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	assert(b2.getCity()=="cccccccccccc");
	assert(b2.getState()=="ddddddddddddddd");
	assert(b2.getZip()=="eeeeeeeeeee");

	app->DisplayMessage("Building Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void Building::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	unsigned short lng;

	Building b1;

	lng=38;
	Building b2("\0\0\0\2\0\3aaa\0\4bbbb\0\5ccccc\0\2UT\0\01212345-6789", lng);

	lng=14;
	Building b3("\0\0\2\2\0\0\0\0\0\0\0\0\0\0", lng);

	lng=10;
	Building b4("\0\0\0\4\0\3aaa\0\4bbbb\0\5ccccc\0\2UT\0\01212345-6789", lng);

	Building b5(b2);

	assert(b1<b2);
	assert(b2>b1);
	assert(b1!=b2);
	assert(b5==b2);
	assert(b2<b3);
	assert(b3>b2);
	assert(b2<=b3);
	assert(b3>=b2);
	assert(b5>=b2);
	assert(b5<=b2);

	app->DisplayMessage("Building Test 4 complete\r\n");
}

// Test case Dispatcher
void Building::run_tests(void)
{
	Building::test1();
	Building::test2();
	Building::test3();
	Building::test4();
}

#endif