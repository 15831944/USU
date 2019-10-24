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
// Test default constructors and some of the set functions
//

void SocketAddress::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("SocketAddress Test 1 complete\r\n");
}

// Test 2
// Test second constructor, copy constructor, and comparison
// functions and operators
//

void SocketAddress::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("SocketAddress Test 2 complete\r\n");
}

// Test 3
// Test get function, assignment operator, length function,
// and void * typecasting
//

void SocketAddress::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("SocketAddress Test 3 complete\r\n");
}

// Test 4
// Test setHost() and setLocalBroadcast functions
//

void SocketAddress::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("SocketAddress Test 4 complete\r\n");
}

// Test 5
// Test bind functions
//

void SocketAddress::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

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
