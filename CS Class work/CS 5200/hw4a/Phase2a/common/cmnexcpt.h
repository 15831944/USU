/*****************************************************************************
*
*  File:          cmnexcpt.h
*  Classes:       GeneralException, FileException,
*                 MemoryException, IllegalCompare
*  Project:       Distributed Calendaring System
*  Programmer:    Stephen Clyde
*  Last Modified: Sep. 12, 2001
*
*  Modification History:
*  Sep. 12, 2001   Initial version
*
*  Description:
*  This file includes all general exception class definition.
*
*****************************************************************************/

#pragma once 

#include <string.h>
#include <iostream.h>
#include <strstrea.h>
#include <errno.h>

const int EXCEPTION_NAME_LNG=16;
const int EXCEPTION_MSG_LNG=64;

class GeneralException
{
private:
   char name[EXCEPTION_NAME_LNG+1];
   char msg[EXCEPTION_MSG_LNG+1];

public:
   GeneralException(const char *n, const char *m)
      {  memset(name,0,EXCEPTION_NAME_LNG+1);
         memset(msg,0,EXCEPTION_NAME_LNG+1);
         if (n)
            strncpy(name,n,EXCEPTION_NAME_LNG);
         if (m)
            strncpy(msg,m,EXCEPTION_MSG_LNG);
      }
   GeneralException(const char *n, long m)
      {  memset(name,0,EXCEPTION_NAME_LNG+1);
         memset(msg,0,EXCEPTION_NAME_LNG+1);
         if (n)
            strncpy(name,n,EXCEPTION_NAME_LNG);
         ostrstream tmp(msg,EXCEPTION_MSG_LNG);
         tmp << m;
      }
   const char* getMsg(void) const { return msg; }
   void print(ostream &out) const
      {  out << name;
         if (strlen(msg)>0) out << ": " << msg;
         out << endl;
      }

};

inline ostream& operator << (ostream &out, GeneralException &p)
{
  p.print(out);
  return out;
}

class MemoryException : public GeneralException {
public:
  MemoryException(const char *data) :
	 GeneralException("Memory Exception", data) {}
};

class FileException : public GeneralException {
public:
  FileException(const char *data) :
	 GeneralException("File Exception", data) {}
};

class IllegalCompare : public GeneralException {
public:
  IllegalCompare(const char *data) :
	 GeneralException("Illegal Compare", data) {}
};
