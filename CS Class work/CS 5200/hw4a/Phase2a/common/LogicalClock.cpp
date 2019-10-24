// LogicalClock.cpp: implementation of the LogicalClock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogicalClock.h"
#include <stdlib.h>
#include <assert.h>
#include "marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define HALF_MAX_INT 0x10000000
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LogicalClock::LogicalClock()
{
	m_clock = 0;
}

LogicalClock::~LogicalClock()
{

}


LogicalClock::LogicalClock(const LogicalClock & orig)
{
	m_clock = orig.m_clock;
}

void LogicalClock::Merge(const LogicalClock & right)
{
	// compare the two logical clocks.. if the right is greater, than merge the clocks
	if (right > *this)
	{
		m_clock = right.m_clock;
	}
}

LogicalClock & LogicalClock::operator++()
{
	m_clock++;
	return *this;
}

LogicalClock & LogicalClock::operator++(int arg2)
{
	m_clock++;
	return *this;
}


LogicalClock & LogicalClock::operator=(const LogicalClock & right)
{
	m_clock = right.m_clock;
	return *this;
}

bool LogicalClock::operator<(const LogicalClock & right) const
{
	return (!(*this > right) && *this != right);
}

bool LogicalClock::operator>(const LogicalClock & right) const
{
	if (m_clock > right.m_clock)
	{
		if (m_clock - right.m_clock <= HALF_MAX_INT)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (m_clock < right.m_clock)
	{
		if (right.m_clock - m_clock <= HALF_MAX_INT)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool LogicalClock::operator<=(const LogicalClock & right) const
{
	return (*this < right || *this == right);
}

bool LogicalClock::operator>=(const LogicalClock & right) const
{
	return (*this > right || *this == right);
}

bool LogicalClock::operator==(const LogicalClock & right) const
{
	return m_clock == right.m_clock;
}

bool LogicalClock::operator!=(const LogicalClock & right) const
{
	return m_clock != right.m_clock; 
}

/*****************************************************************************
*
*   load(const char* buffer, int buffer_lng)
*
*/
BOOL LogicalClock::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;
    result = unmarshall(ptr, end_ptr, m_clock);
	buffer_lng = ptr - buffer;
	return result;
}

/*****************************************************************************
*
*   save(char* buffer, int buffer_lng)
*
*/
BOOL LogicalClock::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;
    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;
	result = marshall(ptr, end_ptr, m_clock);
	buffer_lng = ptr - buffer;
	return result;
}

// TEST CASES

void LogicalClock::test1(void)
{
	//test constructors
	LogicalClock l1;
	assert(l1.m_clock == 0);
	LogicalClock l2(l1);
	assert(l2.m_clock == 0);
	assert(l2 == l1);
}

void LogicalClock::test2(void)
{
	// test increment operator
	LogicalClock l1;
	l1++;
	assert(l1.m_clock == 1);
	// test wrap around;
	l1.m_clock = 0xFFFFFFFF;
	l1++;
	assert(l1.m_clock == 0);
}

void LogicalClock::test3(void)
{
	// test comparison operators
	LogicalClock l1, l2;
	l1++;
	assert(l1 > l2);
	assert(l2 < l1);
	assert(l1 >= l2);
	assert(l2 <= l1);
	assert(l1 != l2);
	l2++;
	assert(l1 == l2);
	assert(l1 >= l2);
	assert(l2 <= l1);
}

void LogicalClock::test4(void)
{
	// test merge function
	LogicalClock l1, l2;
	l1++;
	l1++;
	assert(l1 > l2);
	l1.Merge(l2);
	assert(l1 != l2); // if l1 is greater than l2, than l1 should not change
	l2.Merge(l1);
	assert(l1 == l2); // now they should be the same

}

void LogicalClock::test5(void)
{
	// test all the functions together...
	LogicalClock l1, l2;
	l1++;
	LogicalClock l3(l1);
	assert(l3 > l2 && l1 > l2);
	l3++;
	assert(l3 > l1 && l1 > l2);
	// l3, l1, l2
	l2.Merge(l3);
	assert(l3 > l1);
	assert(l3 == l2);
	// test prefix and postfix operators
	l1 = l2;
	//assert(++l3 != l2++);
	l3++;
	++l2;
	assert(l3 == l2);
	assert(l3 > l1 && l2 > l1);
}

void LogicalClock::run_tests(void)
{
	LogicalClock::test1();
	LogicalClock::test2();
	LogicalClock::test3();
	LogicalClock::test4();
	LogicalClock::test5();
}
