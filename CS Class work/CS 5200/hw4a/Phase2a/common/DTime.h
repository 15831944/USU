/*****************************************************************************
*
*  File:          DTime.h
*  Class:         DTime
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

class DTime : public CTime
{
public:
	// Inherited constructors
    DTime(void) : CTime() {}
	DTime(const DTime& orig) : CTime(orig) {}
	DTime(time_t time) : CTime(time) {}
	DTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST = -1 ) :
		CTime(nYear, nMonth, nDay, nHour, nMin, nSec, nDST ) {}
	DTime(WORD wDosDate, WORD wDosTime, int nDST = -1 ) :
		CTime(wDosDate, wDosTime, nDST) {}
	DTime(const SYSTEMTIME& sysTime, int nDST = -1 ) :
		CTime(sysTime, nDST) {}
	DTime(const FILETIME& fileTime, int nDST = -1 ) :
		CTime(fileTime, nDST);

	// Additional constructors
	DTime(const CString& char_str) : CTime() { loadFromChar(char_str); }

	// Load methods
	void loadFromChar(const DString& char_str);

	// Save methods
	BOOL saveToChar(DString& char_str);

#ifdef TESTING
public:
	static void test1(void);
	static void test2(void);
	static void test3(void);
	static void test4(void);
	static void test5(void);
	static void test6(void);
#endif

};
