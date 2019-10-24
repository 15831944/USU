/*****************************************************************************
*
*  File:          DString.h
*  Class:         DString
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*     Sep 5, 2001  Initial version
*
*  Description:
*     A DString is a dynamic string that combines common features
*     of MFC's CString with Unix's String.
*
*/

#pragma once

#include <stdlib.h>
#include <string.h>

#include <afx.h>

class DString : public CString
{
public:
    DString(void) : CString() {}
    DString(const CString& orig) : CString(orig) {}
    DString(const char *data) : CString(data) {}
    DString(const CString &orig, int desired_length, char fill_char=' ') :
	       CString(orig)
        { fillRight(desired_length, fill_char); }

    // Fill string to the right to a specified length,
    // with a fill character.  If the data is longer than
    // the specified length, then the data is truncated
    // to the specified length
    void fillRight(int desired_length, char fill_char=' ')
        {   int lng = GetLength();
	    if (lng>desired_length)
                GetBufferSetLength(desired_length);
            else if (lng<desired_length)
                *this += CString(fill_char,desired_length-lng);
        }

	// Compatible GetBuffer function
	const char *getData(void)
		{ return GetBuffer(0); }
    const char *getData(void) const
        { DString* tmp = (DString *) this;
          return tmp->GetBuffer(0); }


    // Convert to a short integer
    operator short(void) const
        { return (short) atoi((const char *) *this); }

    // Convert to a long integer
    operator long(void) const
        { return (short) atol((const char *) *this); }

    // Replace string's value with a numeric string for an
    // integer
    DString& operator = (short a)
        {  char buffer[7];
	   *this = itoa(a,buffer,10);
	   return *this;
        }
    DString& operator = (int a)
        {  char buffer[7];
	   *this = itoa(a,buffer,10);
	   return *this;
       	}
    DString& operator = (long a)
        {  char buffer[34];
	   *this = _ltoa(a,buffer,10);
	   return *this;
        }

#ifdef TESTING
public:
	static void test1(void);
	static void test2(void);
	static void test3(void);
	static void test4(void);
	static void test5(void);
	static void test6(void);
	static void run_tests(void);
#endif

};
