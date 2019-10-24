//////////////////////////////////////////////////////////////////////////
//
// File:				Configuration.h
// Version:				1.0
// Project:				ParcelTracker
// Author:				Stephen W. Clyde
// Last Modified:       March 20, 1999
// General Description:
//
// Modified History:
// March 20, 1999   Initial version
//
// Description:
// This file defines the Configuration class, which provides an
// convenient way to read .INI kinds of files.
//
// This file also contains some basic unit testing for the Configuration
// class.  To do unit testing, compile this module with the
// "TESTING_CNFGRTN" compiler variable defined.
//
//////////////////////////////////////////////////////////////////////////

#if !defined(__CONFIGURATION_H)
#define __CONFIGURATION_H

#include <iostream.h>
#include <fstream.h>
#include "cmnexcpt.h"
#include "../common/strdup.h"

const int MAX_CONFIG_LINE_LENGTH = 256;
const int MAX_CONFIG_NAME_LENGTH = 32;
const int MAX_CONFIG_VALUE_LENGTH = 256;
const int MAX_CONFIG_LONG_LENGTH = 11;
const int MAX_CONFIG_SHORT_LENGTH = 5;

class Configuration
{
private:
	char *file_name;
	ifstream *in;

public:
	// Basic constructor
	Configuration(const char *f=NULL) : file_name(strDuplicate(f)), in(NULL) {}

	// Destructor
	~Configuration();

	bool getProfileString(const char *section, const char *entry,
							char *returnBuffer, int bufferSize );
	long getProfileLong(const char *section, const char *entry, long def_value=0 );
	unsigned long getProfileULong(const char *section, const char *entry, unsigned long def_value=0 );
	short getProfileShort(const char *section, const char *entry, short def_value=0 );
	unsigned short getProfileUShort(const char *section, const char *entry, unsigned short def_value=0 );
	char getProfileChar(const char *section, const char *entry, char def_value=0 );

#ifdef TESTING
   static void test1(void);
   static void test2(void);
   static void test3(void);
   static void run_tests(void);
#endif

};

class InvalidConfigFile : public GeneralException
{
public:
  InvalidConfigFile(const char *m) :
	 GeneralException("Invalid Configuration File",m) {}
};

#endif
