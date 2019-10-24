/*****************************************************************************
*
*  File:          ParcelAddress.cpp
*  Class:         ParcelAddress
*  Project:       Parcel Tracker
*  Author:        Stephen W. Clyde
*  Last Modified: August 14, 1997
*
*  Modification History:
*  	Aug 14, 1997	Initial version
*
*  Description:
*	A Parcel Address is a standard postal address in the US.  This version
*   has a known design weakness, namely the fields have relatively small
*   maximum lengths.  The marshalling and unmarshalling uses fixed length
*   fields in the data stream.
*
*/

// stdafx.h must be in all *.cpp files run with Visual C++, possibly with MFC.

//#ifdef _MSC_VER
#include "stdafx.h"
//#endif

#include "ParcelAddress.h"

const int ParcelAddress::NAME_LNG=30;
const int ParcelAddress::ORG_LNG=30;
const int ParcelAddress::STREET_LNG=30;
const int ParcelAddress::CITY_LNG=20;
const int ParcelAddress::STATE_LNG=2;
const int ParcelAddress::ZIP_LNG=10;
const int ParcelAddress::LNG = ParcelAddress::NAME_LNG +
                               ParcelAddress::ORG_LNG +
                               ParcelAddress::STREET_LNG +
                               ParcelAddress::CITY_LNG +
						       ParcelAddress::STATE_LNG +
						       ParcelAddress::ZIP_LNG;

/******************************************************************************
*
*  Method:  ParcelAddress::load
*
*  This function loads a parcel object from string data.  The format of the
*  string data is as follows:
*
*
*		field        field length in bytes     field format
*       =====        =====================     ============
*		name         ParcelAddress::NAME_LNG   char string, space filled
*		org          ParcelAddress::ORG_LNG    char string, space filled
*		street       ParcelAddress::STREET_LNG char string, space filled
*       city         ParcelAddress::CITY_LNG   char string, space filled
*       state        ParcelAddress::STATE_LNG  char string, space filled
*       zip          ParcelAddress::ZIP_LNG    char string, space filled
*
*  The output of this function represent the validity of the object.
*/

BOOL ParcelAddress::load(const DString &data)
{
    if (data.GetLength()!=LNG)
	    return FALSE;
	name = data.Left(NAME_LNG);
	name.TrimRight();
	int pos = NAME_LNG;

	org = data.Mid(pos,ORG_LNG);
	org.TrimRight();
	pos += ORG_LNG;

	street = data.Mid(pos,STREET_LNG);
	street.TrimRight();
	pos += STREET_LNG;

	city = data.Mid(pos,CITY_LNG);
	city.TrimRight();
	pos += CITY_LNG;

	state = data.Mid(pos,STATE_LNG);
	state.TrimRight();
	pos += STATE_LNG;

	zip = data.Mid(pos,ZIP_LNG);
	zip.TrimRight();

    return isValid();
}

/*
loads one ParcelAddress from stream, for now

may need to use 'in.get()' instead of 'in.read()' 
because of EOL (or else LNG+1).
*/
BOOL ParcelAddress::load(istream& in)
{
    BOOL valid = FALSE;
	DString dtemp;
	char *ctemp = new char[LNG+2];

	if (in.good() && in.peek() != EOF) {
		int next_char = in.peek();
		cout << next_char << endl;
		in.getline(ctemp,LNG+2,'\n');
		int count = in.gcount();
		dtemp=ctemp;
		valid=load(dtemp);
	}
	
	delete ctemp;
	return valid;
}

/******************************************************************************
*
*  Method:  ParcelAddress::save
*
*  This function save a parcel object into a string.  The format of the
*  string data is as follows:
*
*
*		field        field length in bytes     field format
*       =====        =====================     ============
*		name         ParcelAddress::NAME_LNG   char string, space filled
*		org          ParcelAddress::ORG_LNG    char string, space filled
*		street       ParcelAddress::STREET_LNG char string, space filled
*       city         ParcelAddress::CITY_LNG   char string, space filled
*       state        ParcelAddress::STATE_LNG  char string, space filled
*       zip          ParcelAddress::ZIP_LNG    char string, space filled
*/
BOOL ParcelAddress::save(DString &data) const
{
   BOOL result=isValid();
   if (result==TRUE)
   {
	   data =  DString(name,NAME_LNG,' ');
	   data += DString(org,ORG_LNG,' ');
	   data += DString(street,STREET_LNG,' ');
	   data += DString(city,CITY_LNG,' ');
	   data += DString(state,STATE_LNG,' ');
   	   data += DString(zip,ZIP_LNG,' ');
   }
   else
	   data = "";
   return result;
}

BOOL ParcelAddress::save(ostream& out) const
{
	BOOL result = FALSE;
	DString dtemp;

    if (out.good()) {
       result = save(dtemp);
	   out << dtemp.GetBuffer(ParcelAddress::LNG) << endl;
    }

    return result;
}

/******************************************************************************
*
*  Method:  ParcelAddress::compare
*
*  This function compare this ParcelAddress with some other address a.
*
*  Output:
*      -1   - this is ordered before a
*       0   - this and a have equivalent values
*       1   - this is ordered after a
*/
int ParcelAddress::compare(const ParcelAddress& a) const
{

	int result=0;
	if (name<a.name)
		result = -1;
	else if (name>a.name)
		result = 1;
	else if (org<a.org)
		result = -1;
	else if (org>a.org)
		result = 1;
	else if (street<a.street)
		result = -1;
	else if (street>a.street)
		result = 1;
	else if (city<a.city)
		result = -1;
	else if (city>a.city)
		result = 1;
	else if (state<a.state)
		result = -1;
	else if (state>a.state)
		result = 1;
	else if (zip<a.zip)
		result = -1;
	else if (zip>a.zip)
		result = 1;
	return result;
}


#ifdef TESTING_PARCEL_ADDRESS
/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <assert.h>

// Test 1 - Default constructor
void ParcelAddress::test1(void)
{
	ParcelAddress	a1;

	assert(a1.name.IsEmpty()==TRUE);
	assert(a1.org.IsEmpty()==TRUE);
	assert(a1.street.IsEmpty()==TRUE);
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);

	cout << "Test 1 complete" << endl;
}

// Test 2 - Get and set methods and isValid method
void ParcelAddress::test2(void)
{
	ParcelAddress a1;
	assert(a1.isValid()==FALSE);

	// Test setName and getName
	a1.setName(DString("Joe Johnson"));
	assert(a1.name=="Joe Johnson");
	assert(a1.getName()=="Joe Johnson");
	assert(a1.org.IsEmpty()==TRUE);
	assert(a1.street.IsEmpty()==TRUE);
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setName(DString(""));
	assert(a1.name.IsEmpty());
	assert(a1.org.IsEmpty()==TRUE);
	assert(a1.street.IsEmpty()==TRUE);
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setName(DString("Henry Longfellow Vergalidusties Son of George the Third"));
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org.IsEmpty()==TRUE);
	assert(a1.street.IsEmpty()==TRUE);
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	// Test setOrg and getOrg
	a1.setOrg(DString("Northwest Garbage Collectors Association"));
	assert(a1.org=="Northwest Garbage Collectors A");
	assert(a1.getOrg()=="Northwest Garbage Collectors A");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.street.IsEmpty()==TRUE);
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setOrg(DString(""));
	assert(a1.org.IsEmpty());
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.street.IsEmpty()==TRUE);
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setOrg(DString("The One-two-three-four-five-six-seven-eight-nine-ten Counting Company from Saint Louis New Jersery"));
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.street.IsEmpty()==TRUE);
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);
	
	// Test setStreet and getStreet
	a1.setStreet(DString("1 Nowhere lane"));
	assert(a1.street=="1 Nowhere lane");
	assert(a1.getStreet()=="1 Nowhere lane");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setStreet(DString(""));
	assert(a1.street.IsEmpty());
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setStreet(DString("Suite 50 on ABCDEFGHIJKLMNOPQRSTUVWXYZ Street"));
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	// Test setCity and getCity
	a1.setCity(DString("Testville"));
	assert(a1.city=="Testville");
	assert(a1.getCity()=="Testville");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setCity(DString(""));
	assert(a1.city.IsEmpty()==TRUE);
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setCity(DString("Longvillllllllllllllllleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"));
	assert(a1.city=="Longvillllllllllllll");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	// Test setState and getState
	a1.setState(DString("UT"));
	assert(a1.state=="UT");
	assert(a1.getState()=="UT");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.city=="Longvillllllllllllll");
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setState(DString(""));
	assert(a1.state.IsEmpty()==TRUE);
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.city=="Longvillllllllllllll");
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	a1.setState(DString("ABC"));
	assert(a1.state=="AB");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.city=="Longvillllllllllllll");
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.isValid()==FALSE);

	// Test setZip and getZip
	a1.setZip(DString("84100"));
	assert(a1.zip=="84100");
	assert(a1.getZip()=="84100");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.city=="Longvillllllllllllll");
	assert(a1.state=="AB");
	assert(a1.isValid()==TRUE);

	a1.setZip(DString(""));
	assert(a1.zip.IsEmpty()==TRUE);
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.city=="Longvillllllllllllll");
	assert(a1.state=="AB");
	assert(a1.isValid()==FALSE);

	a1.setZip(DString("8410012345532"));
	assert(a1.zip=="8410012345");
	assert(a1.name=="Henry Longfellow Vergalidustie");
	assert(a1.org=="The One-two-three-four-five-si");
	assert(a1.street=="Suite 50 on ABCDEFGHIJKLMNOPQR");
	assert(a1.city=="Longvillllllllllllll");
	assert(a1.state=="AB");
	assert(a1.isValid()==TRUE);

	// Test isValid
	a1.setStreet("");
	assert(a1.isValid()==TRUE);
	
	a1.setOrg("");
	assert(a1.isValid()==TRUE);

	a1.setName("");
	assert(a1.isValid()==FALSE);

	a1.setName("ABC");
	assert(a1.isValid()==TRUE);

	a1.setCity("");
	assert(a1.isValid()==FALSE);

	a1.setCity("XYZ");
	assert(a1.isValid()==TRUE);

	a1.setState("");
	assert(a1.isValid()==FALSE);

	cout << "Test 2 complete" << endl;
}

// Test 3 - Copy constructor
void ParcelAddress::test3(void)
{
	ParcelAddress a1;
	a1.setName(DString("Joe Johnson"));
	a1.setOrg(DString("Garbage Collectors Association"));
	a1.setStreet(DString("1 Nowhere lane"));
	a1.setCity(DString("Testville"));
	a1.setState(DString("UT"));
	a1.setZip(DString("84100"));

	ParcelAddress a2(a1);
	assert(a2.name=="Joe Johnson");
	assert(a2.org=="Garbage Collectors Association");
	assert(a2.street=="1 Nowhere lane");
	assert(a2.city=="Testville");
	assert(a2.state=="UT");
	assert(a2.zip=="84100");
	assert(a2.isValid()==TRUE);

	cout << "Test 3 complete" << endl;
}

// Test 4 - Load and save methods
void ParcelAddress::test4(void)
{
	ParcelAddress a1;
	DString d1("Joe Johnson                   Garbage Collectors Association1 Nowhere lane                Testville           UT84100     ");
	BOOL result=a1.load(d1);
	assert(result==TRUE);
	assert(a1.name=="Joe Johnson");
	assert(a1.org=="Garbage Collectors Association");
	assert(a1.street=="1 Nowhere lane");
	assert(a1.city=="Testville");
	assert(a1.state=="UT");
	assert(a1.zip=="84100");
	assert(a1.isValid()==TRUE);

	a1.setName(DString("Test Name"));
	a1.setOrg(DString("Test Org"));
	a1.setStreet(DString("Test Street"));
	a1.setCity(DString("Test City"));
	a1.setState(DString("Test State"));
	a1.setZip(DString("12345-6789"));

	DString d2;
	a1.save(d2);
	assert(d2=="Test Name                     Test Org                      Test Street                   Test City           Te12345-6789");

	DString d3;
	ParcelAddress a2;
	result = a2.load(d3);
	assert(result==FALSE);
	assert(a2.name=="");
	assert(a2.org=="");
	assert(a2.street=="");
	assert(a2.city=="");
	assert(a2.state=="");
	assert(a2.zip=="");
	assert(a2.isValid()==FALSE);

	DString d4("A String that is too longxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	ParcelAddress a3;
	result = a3.load(d4);
	assert(result==FALSE);
	assert(a3.name=="");
	assert(a3.org=="");
	assert(a3.street=="");
	assert(a3.city=="");
	assert(a3.state=="");
	assert(a3.zip=="");
	assert(a3.isValid()==FALSE);
	
	cout << "Test 4 complete" << endl;
}

// Test 5 - String-based constructor
void ParcelAddress::test5(void)
{
	DString d1("Joe Johnson                   Garbage Collectors Association1 Nowhere lane                Testville           UT84100     ");
	ParcelAddress a1(d1);
	assert(a1.name=="Joe Johnson");
	assert(a1.org=="Garbage Collectors Association");
	assert(a1.street=="1 Nowhere lane");
	assert(a1.city=="Testville");
	assert(a1.state=="UT");
	assert(a1.zip=="84100");
	assert(a1.isValid()==TRUE);

	cout << "Test 5 complete" << endl;
}

// Test 6 - Comparison functions
void ParcelAddress::test6(void)
{
	DString d1("Joe Johnson                   Garbage Collectors Association1 Nowhere lane                Testville           UT84100     ");
	DString d2("Tim Johnson                   Garbage Collectors Association1 Nowhere lane                Testville           UT84100     ");
	DString d3("Joe Johnson                   Garbage Collectors Agency     1 Nowhere lane                Testville           UT84100     ");
	DString d4("Joe Johnson                   Garbage Collectors Association2 Nowhere lane                Testville           UT84100     ");
	DString d5("Joe Johnson                   Garbage Collectors Association1 Nowhere lane                Bestville           UT84100     ");
	DString d6("Joe Johnson                   Garbage Collectors Association1 Nowhere lane                Testville           WY84100     ");
	DString d7("Joe Johnson                   Garbage Collectors Association1 Nowhere lane                Testville           UT94100     ");
	
	ParcelAddress a1(d1);
	ParcelAddress a2(d2);
	ParcelAddress a3(d3);
	ParcelAddress a4(d4);
	ParcelAddress a5(d5);
	ParcelAddress a6(d6);
	ParcelAddress a7(d7);
	ParcelAddress a8(d1);

	assert(a1==a8);
	assert(a1>=a8);
	assert(a1<=a8);
	assert(a1!=a2);
	assert(a1<a2);
	assert(a1>a3);
	assert(a2>a3);
	assert(a1<=a4);
	assert(a1>a5);
	assert(a1<a6);
	assert(a1<a7);

	cout << "Test 6 complete" << endl;
}

// Test main
void main(void)
{
	cout << "Testing ParcelAddress" << endl;
	ParcelAddress::test1();
	ParcelAddress::test2();
	ParcelAddress::test3();
	ParcelAddress::test4();
	ParcelAddress::test5();
	ParcelAddress::test6();
	cout << "Testing complete" << endl;
}

#endif



