/*****************************************************************************
*
*   File:                sockaddr.cpp
*   Project:             Parcel Tracker
*   Class:               SocketAddress
*   Version:             1.0
*   Programmer:          Stephen W. Clyde
*   Last Modified:       Nov. 6, 1995
*
*   Modified History:
*
*   Apr. 25, 1995  Initial version
*
*****************************************************************************/

#include "stdafx.h"
#include "SockAddr.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

#ifdef TESTING
/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <fstream.h>
#include <assert.h>

// Test 1
//
void SocketAddress::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	// TO DO: Complete
	// test constructors and isEmpty function
	SocketAddress s1;
	assert(s1.host == CString(""));
	assert(s1.port == 0);
	assert(s1.isEmpty() == TRUE);
	
	SocketAddress s2("127.0.0.1",1250);
	assert(s2.host == CString("127.0.0.1") && s2.port == 1250);

	SocketAddress s3(s2);
	assert(s2.host == s3.host && s2.port == s3.port);
	app->DisplayMessage("SocketAddress Test 1 complete\r\n");
}

// Test 2
//
void SocketAddress::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	// TO DO: Complete
	// test get and set member functions
	SocketAddress s1;
	s1.setHost("192.0.3.89");
	s1.setPort(21);
	assert(s1.host == CString("192.0.3.89"));
	assert(s1.port == 21);

	assert(s1.host == s1.getHost());
	assert(s1.port == s1.getPort());
	app->DisplayMessage("SocketAddress Test 2 complete\r\n");
}

// Test 3
//
void SocketAddress::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	// TO DO: Complete
	// test isEmpty()
	SocketAddress s1;
	assert(s1.host == CString(""));
	assert(s1.port == 0);
	assert(s1.isEmpty() == TRUE);
	s1.setHost("126.3.4.54");
	assert(s1.isEmpty() == FALSE);

	app->DisplayMessage("SocketAddress Test 3 complete\r\n");
}

// Test 4
//
void SocketAddress::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	// TO DO: Complete
	// test comparison operator
	SocketAddress s1;
	SocketAddress s2("127.0.0.1",1250);
	assert(s2.host == CString("127.0.0.1") && s2.port == 1250);

	SocketAddress s3(s2);
	assert(s2 == s3);
	assert((s2 == s1) == FALSE);

	app->DisplayMessage("SocketAddress Test 4 complete\r\n");
}

// Test 5
//
void SocketAddress::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	// TO DO: Complete
	// test multiple functions together
	SocketAddress s1;
	SocketAddress s2("192.0.3.89",21);
	assert(s1.isEmpty() == TRUE);
	s1.setHost("192.0.3.89");
	s1.setPort(21);
	assert(s1==s2);
	SocketAddress s3(s2.getHost(),s2.getPort());
	assert(s3==s2);
	SocketAddress s4(s1);
	assert(s1==s4);
	app->DisplayMessage("SocketAddress Test 5 complete\r\n");
}

void SocketAddress::run_tests(void)
{
	SocketAddress::test1();
	SocketAddress::test2();
	SocketAddress::test3();
	SocketAddress::test4();
	SocketAddress::test5();
}

#endif
