/*****************************************************************************
*
*  File:          Marshall.cpp
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*     Sep 5, 2001  Initial version
*
*  Modification History:
*     Aug 14, 97  Initial version
*
*  Description:
*     The function in this file are basic marshalling functions used in requests,
*     responses, and datagrams
*
******************************************************************************/

#include "stdafx.h"
#include "marshall.h"

BOOL marshall(char*& ptr, const char* end_ptr, unsigned long n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(unsigned long))
    {
        unsigned long tmp = htonl(n);
        memcpy(ptr, &tmp, sizeof(unsigned long));
        ptr += sizeof(unsigned long);
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, long n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(long))
    {
        long tmp = htonl(n);
        memcpy(ptr, &tmp, sizeof(long));
        ptr += sizeof(long);
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, unsigned short n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(unsigned short))
    {
        unsigned short tmp = htons(n);
        memcpy(ptr, &tmp, sizeof(unsigned short));
        ptr += sizeof(unsigned short);
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, short n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(short))
    {
        short tmp = htons(n);
        memcpy(ptr, &tmp, sizeof(short));
        ptr += sizeof(short);
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, unsigned int n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(unsigned int))
    {
        unsigned int tmp = htonl(n);
        memcpy(ptr, &tmp, sizeof(unsigned int));
        ptr += sizeof(unsigned int);
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, int n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(int))
    {
        short tmp = htons(n);
        memcpy(ptr, &tmp, sizeof(int));
        ptr += sizeof(int);
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, const char c)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(char))
    {
        memcpy(ptr, &c, sizeof(char));
        ptr += sizeof(char);
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, const unsigned char c)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(unsigned char))
    {
        memcpy(ptr, &c, sizeof(unsigned char));
        ptr += sizeof(char);
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, const char* c, int lng)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=lng)
    {
        memcpy(ptr, c, lng);
        ptr += lng;
        result = TRUE;
    }
    return result;
}

BOOL marshall(char*& ptr, const char* end_ptr, const DString& s)
{
    BOOL result;
    short tmp = s.GetLength();
    result = marshall(ptr, end_ptr, tmp);
    if (result==TRUE)
    {
        const char *buffer = s.getData();
        result = marshall(ptr, end_ptr, buffer, s.GetLength());
    }
    return result;
}


BOOL unmarshall(const char*& ptr, const char* end_ptr, unsigned long &n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(unsigned long))
    {
        unsigned long tmp;
        memcpy(&tmp, ptr, sizeof(unsigned long));
        ptr += sizeof(unsigned long);
        n = ntohl(tmp);
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, long &n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(long))
    {
        long tmp;
        memcpy(&tmp, ptr, sizeof(long));
        ptr += sizeof(long);
        n = ntohl(tmp);
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, unsigned short &n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(unsigned short))
    {
        unsigned short tmp;
        memcpy(&tmp, ptr, sizeof(unsigned short));
        ptr += sizeof(unsigned short);
        n = ntohs(tmp);
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, short &n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(short))
    {
        unsigned short tmp;
        memcpy(&tmp, ptr, sizeof(short));
        ptr += sizeof(short);
        n = ntohs(tmp);
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, unsigned int &n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(unsigned int))
    {
        unsigned int tmp;
        memcpy(&tmp, ptr, sizeof(unsigned int));
        ptr += sizeof(unsigned int);
        n = ntohl(tmp); // changed this code...
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, int &n)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(int))
    {
        unsigned int tmp;
        memcpy(&tmp, ptr, sizeof(int));
        ptr += sizeof(int);
        n = ntohs(tmp);
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, char& c)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(char))
    {
        memcpy(&c, ptr, sizeof(char));
        ptr += sizeof(char);
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, unsigned char& c)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=sizeof(unsigned char))
    {
        memcpy(&c, ptr, sizeof(unsigned char));
        ptr += sizeof(char);
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, char* c, int lng)
{
    BOOL result=FALSE;
    if ((end_ptr-ptr)>=lng)
    {
        memcpy(c, ptr, lng);
        ptr += lng;
        result = TRUE;
    }
    return result;
}

BOOL unmarshall(const char*& ptr, const char* end_ptr, DString& s)
{
    short lng;
    BOOL result = unmarshall(ptr, end_ptr, lng);
    if (result == TRUE)
    {
        char* buffer = new char[lng+1];
        result = unmarshall(ptr, end_ptr, buffer, lng);
        if (result==TRUE)
        {
            buffer[lng]=0;
            s = buffer;
        }
        delete buffer;
    }
    return result;
}
