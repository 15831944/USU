/*****************************************************************************
*
*	File:          MeetingPreference.cpp
*	Class:         MeetingPreference
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
*	This file contains the implementation and test cases for MeetingPreference.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "Event.h"

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

// Test 1 - Constructor
void MeetingPreference::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


	app->DisplayMessage("MeetingPreference Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void MeetingPreference::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


	app->DisplayMessage("MeetingPreference Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void MeetingPreference::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();


	app->DisplayMessage("MeetingPreference Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void MeetingPreference::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("MeetingPreference Test 4 complete\r\n");
}

// Test 5 - Validation functions
void MeetingPreference::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("MeetingPreference Test 5 complete\r\n");
}

#endif



