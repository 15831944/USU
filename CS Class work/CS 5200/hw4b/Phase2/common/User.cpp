/*****************************************************************************
*
*	File:          User.cpp
*	Class:         User
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
*	This file contains the implementation and test cases for User.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "User.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/*****************************************************************************
*
*   load(const char* buffer, int buffer_lng)
*
*/
BOOL User::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	valid=FALSE;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;
    if (unmarshall(ptr, end_ptr, id)==TRUE)
	  if (unmarshall(ptr, end_ptr, first_name)==TRUE)
		if (unmarshall(ptr, end_ptr, last_name)==TRUE)
          if (unmarshall(ptr, end_ptr, middle_names)==TRUE)
            if (unmarshall(ptr, end_ptr, email_address)==TRUE)
              if (unmarshall(ptr, end_ptr, office_phone)==TRUE)
                if (unmarshall(ptr, end_ptr, username)==TRUE)
                  if (unmarshall(ptr, end_ptr, password)==TRUE)
					  result=validate();

	buffer_lng = ptr - buffer;

	return result;
}

/*****************************************************************************
*
*   save(char* buffer, int buffer_lng)
*
*/
BOOL User::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (marshall(ptr, end_ptr, id)==TRUE)
	  if (marshall(ptr, end_ptr, first_name)==TRUE)
	    if (marshall(ptr, end_ptr, last_name)==TRUE)
	      if (marshall(ptr, end_ptr, middle_names)==TRUE)
            if (marshall(ptr, end_ptr, email_address)==TRUE)
              if (marshall(ptr, end_ptr, office_phone)==TRUE)
                if (marshall(ptr, end_ptr, username)==TRUE)
                  result = marshall(ptr, end_ptr, password);

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
void User::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	unsigned short lng;

	User u1;
	assert(u1.id==-1);
	assert(u1.first_name=="");
	assert(u1.last_name=="");
	assert(u1.middle_names=="");
	assert(u1.email_address=="");
	assert(u1.office_phone=="");
	assert(u1.username=="");
	assert(u1.password=="");

	lng=46;
	User u2("\0\0\0\2\0\4aaaa\0\4bbbb\0\4cccc\0\4dddd\0\4eeee\0\4ffff\0\4gggg", lng);
	assert(lng==46);
	assert(u2.id==2);
	assert(u2.first_name=="aaaa");
	assert(u2.last_name=="bbbb");
	assert(u2.middle_names=="cccc");
	assert(u2.email_address=="dddd");
	assert(u2.office_phone=="eeee");
	assert(u2.username=="ffff");
	assert(u2.password=="gggg");

	lng=18;
	User u3("\0\0\2\2\0\0\0\0\0\0\0\0\0\0\0\0\0\0", lng);
	assert(lng==18);
	assert(u3.id==514);
	assert(u3.first_name=="");
	assert(u3.last_name=="");
	assert(u3.middle_names=="");
	assert(u3.email_address=="");
	assert(u3.office_phone=="");
	assert(u3.username=="");
	assert(u3.password=="");

	User u5(u2);
	assert(u5.id==2);
	assert(u5.first_name=="aaaa");
	assert(u5.last_name=="bbbb");
	assert(u5.middle_names=="cccc");
	assert(u5.email_address=="dddd");
	assert(u5.office_phone=="eeee");
	assert(u5.username=="ffff");
	assert(u5.password=="gggg");

	app->DisplayMessage("User Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void User::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	User u1;
	assert(u1.id==-1);
	assert(u1.first_name=="");
	assert(u1.last_name=="");
	assert(u1.middle_names=="");
	assert(u1.email_address=="");
	assert(u1.office_phone=="");
	assert(u1.username=="");
	assert(u1.password=="");

	u1.setId(45);
	assert(u1.getId()==45);
	u1.setFirstName("Jack");
	assert(u1.getFirstName()=="Jack");
	u1.setLastName("Anjill");
	assert(u1.getLastName()=="Anjill");
	u1.setMiddleNames("");
	assert(u1.getMiddleNames()=="");
	u1.setEmailAddress("jj@test.com");
	assert(u1.getEmailAddress()=="jj@test.com");
	u1.setOfficePhone("435-533-2353");
	assert(u1.getOfficePhone()=="435-533-2353");
	u1.setUsername("jj");
	assert(u1.getUsername()=="jj");
	u1.setPassword("test");
	assert(u1.getPassword()=="test");

	app->DisplayMessage("User Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void User::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	User u1;
	u1.setId(45);
	u1.setFirstName("Jack");
	u1.setLastName("Anjill");
	u1.setMiddleNames("");
	u1.setEmailAddress("jj@test.com");
	u1.setOfficePhone("435-533-2353");
	u1.setUsername("jj");
	u1.setPassword("test");

	char buffer[1024];
	unsigned short buffer_lng=1024;

	u1.save(buffer, buffer_lng);
	assert(buffer_lng>0);
	assert(u1.getPackLng()==buffer_lng);

	User u2;
	u2.load(buffer, buffer_lng);
	
	assert(u2.getId()==45);
	assert(u2.getFirstName()=="Jack");
	assert(u2.getLastName()=="Anjill");
	assert(u2.getMiddleNames()=="");
	assert(u2.getEmailAddress()=="jj@test.com");
	assert(u2.getOfficePhone()=="435-533-2353");
	assert(u2.getUsername()=="jj");
	assert(u2.getPassword()=="test");

	app->DisplayMessage("User Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void User::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	User u1;
	u1.setId(0);
	User u2;
	u2.setId(4);
	User u3;
	u3.setId(6);
	User u4;
	u4.setId(6);


	assert(u1<u2);
	assert(u2>u1);
	assert(u1<=u2);
	assert(u2>=u1);
	assert(u1!=u2);
	assert(u2<u3);
	assert(u3>u2);
	assert(u2<=u3);
	assert(u3>=u2);
	assert(u2!=u3);

	assert(u4==u3);
	assert(u4<=u3);
	assert(u4>=u3);

	app->DisplayMessage("User Test 4 complete\r\n");
}

// Test case Dispatcher
void User::run_tests(void)
{
	User::test1();
	User::test2();
	User::test3();
	User::test4();
}

#endif