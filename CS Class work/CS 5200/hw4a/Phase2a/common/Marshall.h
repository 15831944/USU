/*****************************************************************************
*
*  File:          Marshall.h
*  Version:       1.0
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*     Sep 5, 2001  Initial version
*
*  Description:
*     The function definitions in this represent basic marshalling functions
*
******************************************************************************/

#ifndef  __MARSHALL_H__
#define  __MARSHALL_H__

#include "DString.h"

extern BOOL marshall(char*& ptr, const char* end_ptr, unsigned long n);
extern BOOL marshall(char*& ptr, const char* end_ptr, long n);
extern BOOL marshall(char*& ptr, const char* end_ptr, unsigned short n);
extern BOOL marshall(char*& ptr, const char* end_ptr, short n);
extern BOOL marshall(char*& ptr, const char* end_ptr, unsigned int n);
extern BOOL marshall(char*& ptr, const char* end_ptr, int n);
extern BOOL marshall(char*& ptr, const char* end_ptr, const char c);
extern BOOL marshall(char*& ptr, const char* end_ptr, const unsigned char c);
extern BOOL marshall(char*& ptr, const char* end_ptr, const char* c, int lng);
extern BOOL marshall(char*& ptr, const char* end_ptr, const DString& s);

extern BOOL unmarshall(const char*& ptr, const char* end_ptr, unsigned long &n);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, long &n);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, unsigned short &n);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, short &n);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, unsigned int &n);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, int &n);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, char& c);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, unsigned char& c);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, char* c, int lng);
extern BOOL unmarshall(const char*& ptr, const char* end_ptr, DString& s);

#endif