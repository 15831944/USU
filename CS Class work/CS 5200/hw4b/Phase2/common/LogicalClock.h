// LogicalClock.h: interface for the LogicalClock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICALCLOCK_H__647F5321_E0EB_11D5_B023_0002E3059EB4__INCLUDED_)
#define AFX_LOGICALCLOCK_H__647F5321_E0EB_11D5_B023_0002E3059EB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
a constructor
		something to increment the clock
		something that compares and merges another logical clock
		a save method to package up a clock's value into a character buffer
		a load method that restore a clock's value from a character buffer

	You may also find it useful to implement  following optional methods and operators:

		a copy constructor
		the ++ operator
		all the comparison operators
		the = operator

	Pattern you test cases after the test cases for all of the other classes.  The call to LogicalClock::run_tests is already in TestPackageDlg.cpp.

	Be sure that your test cases are thorough.

*/
#include <afx.h>

class LogicalClock  
{
public:	
	void clear();
	unsigned short getPackLng() const;
	LogicalClock(unsigned int clock = 0);
	LogicalClock(const LogicalClock & orig);
	void Merge(const LogicalClock & right);
	BOOL load(const char* buffer, unsigned short& buffer_lng);
	BOOL save(char* buffer, unsigned short& buffer_lng) const;
	LogicalClock & operator++();
	LogicalClock & operator++(int);
	LogicalClock & operator=(const LogicalClock & right);
	bool operator<(const LogicalClock & right) const;
	bool operator>(const LogicalClock & right) const;
	bool operator<=(const LogicalClock & right) const;
	bool operator>=(const LogicalClock & right) const;
	bool operator==(const LogicalClock & right) const;
	bool operator!=(const LogicalClock & right) const;
	virtual ~LogicalClock();

	// Testing methods
#ifdef TESTING
    static void test1(void);
    static void test2(void);
    static void test3(void);
    static void test4(void);
    static void test5(void);
	static void run_tests(void);
#endif

private:
	UINT m_clock;
};

#endif // !defined(AFX_LOGICALCLOCK_H__647F5321_E0EB_11D5_B023_0002E3059EB4__INCLUDED_)
