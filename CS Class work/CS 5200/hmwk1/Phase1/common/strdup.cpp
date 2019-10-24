////////////////////////////////////////////////////////////////////////////
//
// File:			strdup.c
// Project:     	Distributed Calendering System
// Version:     	2.0
// Programmer:		Stephen W. Clyde
// Last Modified:	Sep. 5, 2001
//
// Modified History:
//
// Sep. 5, 2001		Copied from the Storage Facility
//
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <string.h>

char *strDuplicate(const char *orig)
{
  char *result=NULL;
  if (orig)
  {
	 result = new char[strlen(orig)+1];
	 if (result)
		strcpy(result,orig);
  }
  return result;
}

#ifdef TESTING
#include "../TestPackage/TestPackage.h"


/*****************************************************************************
*
*   Test cases
*
*/

#include <assert.h>

// Test 1 - Basic Constructors
void strdup_test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	char* tmp1 = "Testing1234 abcdef 4567";
    char* tmp2 = strDuplicate(tmp1);
	assert(strcmp(tmp2,"Testing1234 abcdef 4567")==0);

	char* tmp3 = strDuplicate("");
	assert(strcmp(tmp3,"")==0);

	char* tmp4 = strDuplicate(NULL);
	assert(tmp4==NULL);

	delete tmp2;
	delete tmp3;
	delete tmp4;

    app->DisplayMessage("strdup Test 1 complete\r\n");
}

#endif

