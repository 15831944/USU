/*****************************************************************************
*
*  File:          DString.cpp
*  Class:         DString
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*     A DString is a dynamic string that combines common features
*     of MFC's CString with Unix's String.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include "DString.h"


#ifdef TESTING
#include "../TestPackage/TestPackage.h"

/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <assert.h>

// Test 1 - Basic Constructors
void DString::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

    DString s1;
    assert(s1.IsEmpty()==TRUE);

    s1="This is a test";
    assert(s1=="This is a test");

    DString s2(s1);
    assert(s2=="This is a test");

    DString s3("Testing 1234");
    assert(s3=="Testing 1234");

    app->DisplayMessage("DString Test 1 complete\r\n");
}

// Test 2 - fillRight, Left, Mid, TrimRight
void DString::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	DString s3("Testing 1234");
	s3.fillRight(15,'x');
	assert(s3=="Testing 1234xxx");

	s3.fillRight(15,'y');
	assert(s3=="Testing 1234xxx");

	s3.fillRight(10,'z');
	assert(s3=="Testing 12");

	s3.fillRight(15,'z');
	assert(s3=="Testing 12zzzzz");

	DString s1 = s3.Left(4);
	assert(s1=="Test");

	s1.fillRight(10,' ');
	assert(s1=="Test      ");

	DString s2 = s1.Mid(3,3);
	assert(s2=="t  ");

	s1.TrimRight();
	assert(s1=="Test");

	app->DisplayMessage("DString Test 2 complete\r\n");
}

// Test 3 - Fixed-length constructor
void DString::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	DString s1("Testing 1234",15,'x');
	assert(s1=="Testing 1234xxx");

	app->DisplayMessage("DString Test 3 complete\r\n");
}

// Test 4 - Conversion functions and operators
void DString::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	DString s1("1234");

	short tmp2 = (short) s1;
	assert(tmp2==1234);
	long tmp3 = (long) s1;
	assert(tmp3==1234);

	s1 = 3456;
	tmp2 = (short) s1;
	assert(tmp2==3456);

	app->DisplayMessage("DString Test 4 complete\r\n");
}

// Test 5 - GetLength, Empty, and isEmpty
void DString::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	DString s1("abcdefgh");
	assert(s1.GetLength()==8);

	s1.Empty();
	assert(s1.GetLength()==0);
	assert(s1.IsEmpty()==TRUE);

	app->DisplayMessage("DString Test 5 complete\r\n");
}

// Test 6 - Nothing right now
void DString::test6(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("DString Test 6 complete\r\n");
}

#endif
