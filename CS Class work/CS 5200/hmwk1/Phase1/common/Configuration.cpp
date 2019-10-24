//////////////////////////////////////////////////////////////////////////
//
//	File:               Configuration.cpp
//	Version:			1.0
//	Project:			ParcelTracker
//	Author:				Stephen W. Clyde
//	Last Modified:		March 20, 1999
//	General Description:
//
//	This file implements the Configuration class, which provides an convenient
//	way to read INI files.
//
//	This file also contains some basic unit testing for the Configuration
//	class.  To do unit testing, compile this module with the
//	"TESTING_CONFIGURATION" compiler variable defined.
//
//	Modified History:
//	March 20, 1999   Initial version
//
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Configuration.h"
#include "strdup.h"
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////
//
// Configuration destructor
//
Configuration::~Configuration()
{
	if (file_name)
		delete file_name;
	if (in)
		delete in;
}

////////////////////////////////////////////////////////////////////////////
//
// Configuration::getProfileString
//
// This function extracts a string name in file classfr.ini.  If given section
// and entry exist, return 1 and put the result in returnBuffer.  Otherwise,
// return 0
//
bool Configuration::getProfileString( const char * section, const char * entry,
									char * returnBuffer, int bufferSize )
{
	bool result = FALSE;
	if (file_name)
	{
		if (!in)
		{
			in = new ifstream();
			in->open( file_name );
			if (in->fail())
			{
				delete in;
				in = NULL;
				throw InvalidConfigFile(file_name);
			}
		}
		char a[MAX_CONFIG_LINE_LENGTH];
		char *pt;

		in->seekg( 0 );
		do
		{
			in->getline(a, MAX_CONFIG_LINE_LENGTH);
			if (a[0] == ';')
				pt = NULL;
			else
				if (a[0] == '[')
					pt = strtok(a, "[ ]");
				else
					pt = NULL;
		} while (!in->eof() && (pt== NULL || strcmp(section, pt)!=0));

		if (!in->eof())
		{
			do
			{
				in->getline( a, MAX_CONFIG_LINE_LENGTH );
				if ( a[0] == ';' )
					pt = NULL;
				else
					pt = strtok(a, "= ");
			} while (a[0]!='[' && !in->eof() && (!pt || strcmp(entry, pt) != 0));

			if (a[0]!='[' && !in->eof())
			{
				pt = strtok(NULL, "=");
				if (pt)
				{
					// remove leading spaces
					for (;*pt==' ';pt++);
					strncpy(returnBuffer, pt, bufferSize-1);
					
					
					returnBuffer[bufferSize - 1] = 0;
					result=TRUE;
				}
			}
		}
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////
//
// Configuration::getProfileLong
//
// This function extracts a long integer value in file classfr.ini
//
long Configuration::getProfileLong(const char *section, const char *entry, long def_value)
{
	long result = def_value;
	char buffer[MAX_CONFIG_LONG_LENGTH+1];
	if (getProfileString(section, entry, buffer, MAX_CONFIG_LONG_LENGTH))
		result = strtol(buffer, NULL, 10 );
	return result;
}

////////////////////////////////////////////////////////////////////////////
//
// Configuration::getProfileLong
//
// This function extracts a long integer value in file classfr.ini
//
unsigned long Configuration::getProfileULong(const char *section, const char *entry, unsigned long def_value)
{
	unsigned long result = def_value;
	char buffer[MAX_CONFIG_LONG_LENGTH+1];
	if (getProfileString(section, entry, buffer, MAX_CONFIG_LONG_LENGTH))
		result = strtoul(buffer, NULL, 10 );
	return result;
}

////////////////////////////////////////////////////////////////////////////
//
// Configuration::getProfileShort
//
// This function extracts a short integer value in file classfr.ini
//
short Configuration::getProfileShort(const char *section, const char *entry, short def_value)
{
	short result = def_value;
	char buffer[MAX_CONFIG_SHORT_LENGTH+1];
	if (getProfileString(section, entry, buffer, MAX_CONFIG_SHORT_LENGTH))
		result = (short) strtol(buffer, NULL, 10 );
	return result;
}

////////////////////////////////////////////////////////////////////////////
//
// Configuration::getProfileShort
//
// This function extracts an unsigned short integer value in file classfr.ini
//
unsigned short Configuration::getProfileUShort(const char *section, const char *entry, unsigned short def_value)
{
	unsigned short result = def_value;
	char buffer[MAX_CONFIG_LONG_LENGTH+1];
	if (getProfileString(section, entry, buffer, MAX_CONFIG_LONG_LENGTH))
		result = (unsigned short) strtoul(buffer, NULL, 10 );
	return result;
}

////////////////////////////////////////////////////////////////////////////
//
// Configuration::getProfileChar
//
// This function extracts a character value in file classfr.ini
//
char Configuration::getProfileChar( const char * section, const char * entry, char def_value)
{
	char result = def_value;
	char buffer[MAX_CONFIG_VALUE_LENGTH];
	if (getProfileString( section, entry, buffer, MAX_CONFIG_VALUE_LENGTH ))
		result = buffer[0];
	return result;
}


#ifdef TESTING
#include <assert.h>
#include "../TestPackage/TestPackage.h"

////////////////////////////////////////////////////////////////////////////
//
// Unit Testing for the Configuration class
//

// Test 1
//		Check out the constructor and the getProfileString method
//
void Configuration::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Configuration a("../test.ini");
	assert(a.file_name!=NULL);
	assert(strcmp(a.file_name,"../test.ini")==0);
	assert(a.in==NULL);
	char buf[64];
	bool result;

	result = a.getProfileString("Section1","Par1",buf,63);
	assert(a.in!=NULL);
	assert(result==TRUE);
	assert(strcmp(buf,"ABC")==0);
	result = a.getProfileString("Section1","Par2",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"1234567890123456789012345678901234567890")==0);
	result = a.getProfileString("Section1","Par3",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"XYZ")==0);
	result = a.getProfileString("Section1","LongNameParameter",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"123456789")==0);

	result = a.getProfileString("Section3","Par3",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"XXYYZZ")==0);
	result = a.getProfileString("Section3","Par2",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"C")==0);
	result = a.getProfileString("Section3","Par1",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"A")==0);

	result = a.getProfileString("Section2","Par3",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"456")==0);
	result = a.getProfileString("Section2","Par2",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"123")==0);
	result = a.getProfileString("Section2","Par1",buf,63);
	assert(result==TRUE);
	assert(strcmp(buf,"AAABBBCCC")==0);

	result = a.getProfileString("Section4","Par3",buf,63);
	assert(result==FALSE);
	result = a.getProfileString("Section2","Par4",buf,63);
	assert(result==FALSE);

	app->DisplayMessage("Configuration: Test Case 1 Complete\r\n");
}

//	Test 2
//		Check out getProfileLong method
//		Check out getProfileULong method
//		Check out getProfileShort method
//		Check out getProfileUShort method
//
void Configuration::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Configuration a("../test.ini");
	long result;

	result = a.getProfileLong("Section1","Par1");
	assert(result==0);
	result = a.getProfileLong("Section1","Par2");
	assert(result==1234567890L);
	result = a.getProfileLong("Section1","Par3");
	assert(result==0);
	result = a.getProfileLong("Section1","LongNameParameter");
	assert(result==123456789L);

	result = a.getProfileLong("Section2","Par3");
	assert(result==456);
	result = a.getProfileLong("Section2","Par2");
	assert(result==123);
	result = a.getProfileLong("Section2","Par1");
	assert(result==0);

	result = a.getProfileULong("Section1","Par1");
	assert(result==0);
	result = a.getProfileULong("Section1","Par2");
	assert(result==1234567890UL);
	result = a.getProfileULong("Section1","Par3");
	assert(result==0);
	result = a.getProfileULong("Section1","LongNameParameter");
	assert(result==123456789UL);

	result = a.getProfileULong("Section2","Par3");
	assert(result==456);
	result = a.getProfileULong("Section2","Par2");
	assert(result==123);
	result = a.getProfileULong("Section2","Par1");
	assert(result==0);

	result = a.getProfileShort("Section1","Par1");
	assert(result==0);
	result = a.getProfileShort("Section1","Par3");
	assert(result==0);

	result = a.getProfileShort("Section2","Par3");
	assert(result==456);
	result = a.getProfileShort("Section2","Par2");
	assert(result==123);
	result = a.getProfileShort("Section2","Par1");
	assert(result==0);

	result = a.getProfileShort("Section1","Par1");
	assert(result==0);
	result = a.getProfileShort("Section1","Par3");
	assert(result==0);

	result = a.getProfileUShort("Section2","Par3");
	assert(result==456);
	result = a.getProfileUShort("Section2","Par2");
	assert(result==123);
	result = a.getProfileUShort("Section2","Par1");
	assert(result==0);

	app->DisplayMessage("Configuration: Test Case 2 Complete\r\n");
}

//	Test 3
//		Check out getProfileChar method
void Configuration::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

    Configuration a("../test.ini");
    char result;

	result = a.getProfileChar("Section1","Par1");
	assert(result=='A');
	result = a.getProfileChar("Section1","Par2");
	assert(result=='1');
	result = a.getProfileChar("Section1","Par3");
	assert(result=='X');
	result = a.getProfileChar("Section1","LongNameParameter");
	assert(result=='1');

	result = a.getProfileChar("Section3","Par3");
	assert(result=='X');
	result = a.getProfileChar("Section3","Par2");
	assert(result=='C');
	result = a.getProfileChar("Section3","Par1");
	assert(result=='A');

	result = a.getProfileChar("Section2","Par3");
	assert(result=='4');
	result = a.getProfileChar("Section2","Par2");
	assert(result=='1');
	result = a.getProfileChar("Section2","Par1");
	assert(result=='A');

	app->DisplayMessage("Configuration: Test Case 3 Complete\r\n");
}

#endif
