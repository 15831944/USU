////////////////////////////////////////////////////////////////////////////
//
// File:			strdup.c
// Project:     	Distributed Calendaring System
// Version:     	2.0
// Programmer:		Stephen W. Clyde
// Last Modified:	Sep. 5, 2001
//
// Modified History:
//
// Sep. 5, 20001		Copies from the Storage Facility
//
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __STRING_H
#include <string.h>
#endif

#ifndef __STRDUP_H
#define __STRDUP_H

extern char *strDuplicate(const char *orig);

#ifdef TESTING
extern void strdup_test1();
#endif

#endif
