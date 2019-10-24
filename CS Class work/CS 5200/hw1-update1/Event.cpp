/*****************************************************************************
*
*  File:          Event.cpp
*  Class:         Event
*  Version:       1.0
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*	A Event object represents something on someone's calendar.
*
*   This version of the Event object contains some known inefficiencies
*	in the way it marshalling its data in the save function.  It uses
*   fix length fields and saves all numeric data as strings.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "Event.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

const int Event::ID_LNG=10;
const int Event::EVENT_TYPE_LNG=1;
const int Event::NAME_LNG=64;
const int Event::DESCRIPTION_LNG=256;
const int Event::NOTE_LNG=1024;
const int Event::DATE_TIME_LNG=14;		// YYYYMMDD HH:MM (%Y%m%d %H:%M)
const int Event::DURATION_LNG=6;
const int Event::LOCATION_ID_LNG=10;
const int Event::STATUS_LNG=12;
const int Event::LNG =  Event::ID_LNG +
                        Event::EVENT_TYPE_LNG +
						Event::NAME_LNG +
						Event::DESCRIPTION_LNG +
						Event::NOTE_LNG +
						Event::DATE_TIME_LNG +
						Event::DURATION_LNG +
						Event::LOCATION_ID_LNG +
						Event::STATUS_LNG;

int Event::max_day[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/******************************************************************************
*
*  Method:  Event::load
*
*  This function loads a Event object from string data.
*
*  After you load a Event object, the validity of the object can be checked
*  with the isValid() method.
*/
BOOL Event::load(const DString &data)
{
    if (data.GetLength()!=LNG)
	    return FALSE;

	DString tmp = data.Left(ID_LNG);
	id = (long) tmp;
	int pos = ID_LNG;

	setEventType(data.Mid(pos,EVENT_TYPE_LNG));
	pos += EVENT_TYPE_LNG;

	setName(data.Mid(pos,NAME_LNG));
	pos += NAME_LNG;

	setDescription(data.Mid(pos,DESCRIPTION_LNG));
	pos += DESCRIPTION_LNG;

	setNote(data.Mid(pos,NOTE_LNG));
	pos += NOTE_LNG;

	setDateTime(data.Mid(pos,DATE_TIME_LNG));
	pos += DATE_TIME_LNG;

	setDuration(data.Mid(pos,DURATION_LNG));
	pos += DURATION_LNG;

	setLocationId(data.Mid(pos,LOCATION_ID_LNG));
	pos += LOCATION_ID_LNG;

	setStatus(data.Mid(pos,STATUS_LNG));
	pos += STATUS_LNG;

	return TRUE;
}

BOOL Event::load(istream& in)
{
    BOOL valid = FALSE;
	DString dtemp;

	char *ctemp = new char[LNG+2];

	if (in.good() && in.peek() != EOF) {
		int next_char = in.peek();
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
*  Method:  Event::save
*
*  This function save a Event object into a string.
*
*/
BOOL Event::save(DString &data) const
{
   BOOL result=isValid();
   if (result==TRUE)
   {
	   DString tmp;

	   tmp = id;
	   tmp.fillRight(ID_LNG);
	   data =  tmp;

	   data += DString(event_type,EVENT_TYPE_LNG,' ');
	   data += DString(name,NAME_LNG,' ');
	   data += DString(description,DESCRIPTION_LNG,' ');
	   data += DString(note,NOTE_LNG,' ');

	   getDateTime(tmp);
	   data += DString(tmp,DATE_TIME_LNG,' ');

	   tmp = duration;
	   tmp.fillRight(DURATION_LNG);
	   data += tmp;

	   tmp = location_id;
	   tmp.fillRight(LOCATION_ID_LNG);
	   data += tmp;

	   getStatus(tmp);
       tmp.fillRight(STATUS_LNG);
	   data += tmp;

   }
   else
	   data = "";
   return result;
 
}

/******************************************************************************
*
*  Method:  Event::save
*
*  This function save a Event object into a string.
*
*/
BOOL Event::save(ostream& out)
{
	BOOL result=FALSE;
	if (out.good())
	{
		DString tmp;
		result=save(tmp);
		if (result)
			out << (const char *) tmp << endl;
	}

	return result;
}

/******************************************************************************
*
*  Method:  Event::setDateTime
*
*  This method sets the date and time of the event using a string in the
*  following format:
*
*		YYYYMMDD HH:MM
*/
BOOL Event::setDateTime(const CString& new_date_time)
{
	BOOL result=FALSE;

	DString tmp;
	int year, month, day, hours, minutes;

	tmp=new_date_time.Mid(0,4);
	year = (short) tmp;

	tmp=new_date_time.Mid(4,2);
	month = (short) tmp;

	tmp=new_date_time.Mid(6,2);
	day = (short) tmp;

	tmp=new_date_time.Mid(9,2);
	hours = (short) tmp;

	tmp=new_date_time.Mid(12,2);
	minutes = (short) tmp;

	result=setDateTime(year,month,day,hours,minutes);

	return result;
}


/******************************************************************************
*
*  Method:  Event::setStatus
*/
BOOL Event::setStatus(const CString &new_status)
{
	BOOL retval = TRUE;

	DString tmp(new_status);
	tmp.TrimRight();

	if (tmp=="Unknown")
		status=UNKNOWN;
	else if (tmp=="Unscheduled")
		status=UNSCHEDULED;
	else if (tmp=="Scheduled")
		status=SCHEDULED;
	else
		retval=FALSE;

	return retval;

}

/******************************************************************************
*
*  Method:  Event::getDateTime(CString& str)
*
*  This method returns the event's date and time in a YYYYMMDD HH:MM format.
*
*/
const CTime& Event::getDateTime(CString& str) const
{
	str = date_time.Format("%Y%m%d %H:%M");
	return date_time;
}

/******************************************************************************
*
*  Method:  Event::getStatus(CString& str)
*/
Event::STATUS Event::getStatus(CString& str) const
{
	switch (status)
	{
	case UNKNOWN:
	    str="Unknown";
		break;
	case UNSCHEDULED:
	    str="Unscheduled";
		break;
	case SCHEDULED:
	    str="Scheduled";
		break;
    }
	return status;
}

/******************************************************************************
*
*  Method:  Event::checkTime
*
*  This function checks to see if a time is valid
*
*/
BOOL Event::checkTime(int hours, int minutes, int seconds)
{
	BOOL result=FALSE;

	if (hours>=0 && hours<=23)
		if (minutes>=0 && minutes<59)
			if (seconds>=0 && seconds<59)
				result=TRUE;

	return result;
}

/******************************************************************************
*
*  Method:  Event::checkDate
*
*  This function checks to see if a day is valid for a given month
*
*/
BOOL Event::checkDate(int year, int month, int day)
{
	BOOL result=FALSE;

	if (isLeapYear(year)) max_day[2]=29;
	else max_day[2]=28;

	if (year>=1970 && year<=2038)
		if (month>=1 && month<=12)
			if (day>=1 && day<=max_day[month])
				result=TRUE;

	return result;
}

/******************************************************************************
*
*  Method:  Event::isLeapYear
*
*  This function checks to see if a day is valid for a given month
*
*/
BOOL Event::isLeapYear(int year)
{
	BOOL result;
	if (year%4 != 0)
		result=FALSE;
    else if (year%400 == 0)
		result=TRUE;
	else if (year%100 == 0)
		result=FALSE;
    else
		result=TRUE;

	return result;
}

/******************************************************************************
*
*  Method:  Event::compare
*
*  This function compare this Event with some other one "a".
*
*  Output:
*      -1   - this is ordered before a
*       0   - this and a have equivalent values
*       1   - this is ordered after a
*/
int Event::compare(const Event& a) const
{
	int result = 0;
	if (id < a.id)
		result = -1;
	else if (id > a.id)
	    result = 1;
	return result;
}


#ifdef TESTING
/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <fstream.h>
#include <assert.h>

// Test 1 - Constructor
void Event::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Event e1;
	assert(e1.id==0);
	assert(e1.event_type==FACE2FACE);
	assert(e1.name=="");
	assert(e1.description=="");
	assert(e1.note=="");
	assert(e1.date_time<=CTime());
	assert(e1.duration==0);
	assert(e1.location_id==0);
	assert(e1.status==UNKNOWN);

	DString tmp_id("1234");
	tmp_id.fillRight(10,' ');
	DString tmp_name("Test Event");
	tmp_name.fillRight(64,' ');
	DString tmp_desc("Test description");
	tmp_desc.fillRight(256,' ');
	DString tmp_note("Test Note");
	tmp_note.fillRight(1024,' ');
	DString tmp_datetime("20010921 10:53");
	DString tmp_location("352");
	tmp_location.fillRight(10,' ');
	DString tmp_status("Unscheduled");
	tmp_status.fillRight(12,' ');

	DString tmp;
	tmp += tmp_id;
	tmp += "F";
	tmp += tmp_name;
	tmp += tmp_desc;
	tmp += tmp_note;
	tmp += tmp_datetime;
	tmp += "60    ";
	tmp += tmp_location;
	tmp += tmp_status;

    Event e2(tmp);
	assert(e2.id==1234);
	assert(e2.event_type==FACE2FACE);
	assert(e2.name=="Test Event");
	assert(e2.description=="Test description");
	assert(e2.note=="Test Note");
	assert(e2.date_time==CTime(2001,9,21,10,53,0));
	assert(e2.duration==60);
	assert(e2.location_id==352);
	assert(e2.status==UNSCHEDULED);

	Event e3(e2);
	assert(e3.id==1234);
	assert(e3.event_type==FACE2FACE);
	assert(e3.name=="Test Event");
	assert(e3.description=="Test description");
	assert(e3.note=="Test Note");
	assert(e3.date_time==CTime(2001,9,21,10,53,0));
	assert(e3.duration==60);
	assert(e3.location_id==352);
	assert(e3.status==UNSCHEDULED);

	ofstream outstr("Event.txt");
	outstr.write(tmp,Event::LNG);
	outstr.close();

	ifstream instr("Event.txt");
	Event e4(instr);
	assert(e4.id==1234);
	assert(e4.event_type==FACE2FACE);
	assert(e4.name=="Test Event");
	assert(e4.description=="Test description");
	assert(e4.note=="Test Note");
	assert(e4.date_time==CTime(2001,9,21,10,53,0));
	assert(e4.duration==60);
	assert(e4.location_id==352);
	assert(e4.status==UNSCHEDULED);
	instr.close();

	app->DisplayMessage("Event Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void Event::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Event e1;

	BOOL result;

	result=e1.setId(2532);
	assert(result==TRUE);
	assert(e1.getId()==2532);
	result=e1.setId(0);
	assert(result==TRUE);
	assert(e1.getId()==0);
	result=e1.setId(6436);
	assert(result==TRUE);
	assert(e1.getId()==6436);
	result=e1.setId(-1);
	assert(result==FALSE);
	assert(e1.getId()==6436);
	result=e1.setId(-2364);
	assert(result==FALSE);
	assert(e1.getId()==6436);

	result=e1.setEventType(VOICE_CALL);
	assert(result==TRUE);
	assert(e1.getEventType()==VOICE_CALL);
	result=e1.setEventType('F');
	assert(result==TRUE);
	assert(e1.getEventType()==FACE2FACE);
	result=e1.setEventType(CString("O"));
	assert(result==TRUE);
	assert(e1.getEventType()==ONLINE);

	result=e1.setName(CString("Group Meeting"));
	assert(result==TRUE);
	assert(e1.getName()=="Group Meeting");
	result=e1.setName(CString(""));
	assert(result==TRUE);
	assert(e1.getName()=="");
	result=e1.setName(CString("Big Group Meeting"));
	assert(result==TRUE);
	assert(e1.getName()=="Big Group Meeting");

	result=e1.setDescription(CString("This will be an important group meeting"));
	assert(result==TRUE);
	assert(e1.getDescription()=="This will be an important group meeting");
	result=e1.setDescription(CString(""));
	assert(result==TRUE);
	assert(e1.getDescription()=="");
	result=e1.setDescription(CString("This will be a really really really important group meeting"));
	assert(result==TRUE);
	assert(e1.getDescription()=="This will be a really really really important group meeting");

	result=e1.setNote(CString("This meeting will probably be boring"));
	assert(result==TRUE);
	assert(e1.getNote()=="This meeting will probably be boring");
	result=e1.setNote(CString(""));
	assert(result==TRUE);
	assert(e1.getNote()=="");
	result=e1.setNote(CString("This will be a really really really really really realy exciting"));
	assert(result==TRUE);
	assert(e1.getNote()=="This will be a really really really really really realy exciting");

	result=e1.setDateTime(2001,5,30,14,30);
	assert(result==TRUE);
	assert(e1.getDateTime()==CTime(2001,5,30,14,30,0));
	result=e1.setDateTime(2001,5,30,14,61);
	assert(result==FALSE);
	assert(e1.getDateTime()==CTime(2001,5,30,14,30,0));
	result=e1.setDateTime(2001,5,30,61,30);
	assert(result==FALSE);
	assert(e1.getDateTime()==CTime(2001,5,30,14,30,0));
	result=e1.setDateTime(2001,5,32,14,30);
	assert(result==FALSE);
	assert(e1.getDateTime()==CTime(2001,5,30,14,30,0));
	result=e1.setDateTime(2001,13,30,14,30);
	assert(result==FALSE);
	assert(e1.getDateTime()==CTime(2001,5,30,14,30,0));
	result=e1.setDateTime(2050,5,30,14,30);
	assert(result==FALSE);
	assert(e1.getDateTime()==CTime(2001,5,30,14,30,0));
	result=e1.setDateTime(CString("20010930 16:35"));
	assert(result==TRUE);
	assert(e1.getDateTime()==CTime(2001,9,30,16,35,0));

	result=e1.setDuration(35);
	assert(result==TRUE);
	assert(e1.getDuration()==35);
	result=e1.setDuration(0);
	assert(result==TRUE);
	assert(e1.getDuration()==0);
	result=e1.setDuration(75);
	assert(result==TRUE);
	assert(e1.getDuration()==75);
	result=e1.setDuration(-1);
	assert(result==FALSE);
	assert(e1.getDuration()==75);

	result=e1.setLocationId(2532);
	assert(e1.getLocationId()==2532);
	result=e1.setLocationId(0);
	assert(e1.getLocationId()==0);
	result=e1.setLocationId(6436);
	assert(e1.getLocationId()==6436);
	result=e1.setLocationId(-1);
	assert(e1.getLocationId()==6436);
	result=e1.setLocationId(-2364);
	assert(e1.getLocationId()==6436);

	result=e1.setStatus("Scheduled");
	assert(result==TRUE);
	assert(e1.getStatus()==SCHEDULED);
	result=e1.setStatus("Unscheduled");
	assert(result==TRUE);
	assert(e1.getStatus()==UNSCHEDULED);
	result=e1.setStatus("aaaa");
	assert(result==FALSE);
	assert(e1.getStatus()==UNSCHEDULED);

	app->DisplayMessage("Event Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void Event::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Event e1;

	BOOL result;

	result=e1.setId(2532);
	result=e1.setEventType(VOICE_CALL);
	result=e1.setName(CString("Group Meeting"));
	result=e1.setDescription(CString("This will be an important group meeting"));
	result=e1.setNote(CString("This meeting will probably be boring"));
	result=e1.setDateTime(2001,5,30,14,30);
	result=e1.setDuration(35);
	result=e1.setLocationId(2532);
	result=e1.setStatus("Scheduled");

	DString tmp;
	e1.save(tmp);

	Event e2(tmp);
	assert(e2.getId()==2532);
	assert(e2.getEventType()==VOICE_CALL);
	assert(e2.getName()=="Group Meeting");
	assert(e2.getDescription()=="This will be an important group meeting");
	assert(e2.getNote()=="This meeting will probably be boring");
	assert(e2.getDateTime()==CTime(2001,5,30,14,30,0));
	assert(e2.getDuration()==35);
	assert(e2.getLocationId()==2532);
	assert(e2.getStatus()==SCHEDULED);

	app->DisplayMessage("Event Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void Event::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("Event Test 4 complete\r\n");
}

// Test 5 - Validation functions
void Event::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("Event Test 5 complete\r\n");
}

// Test 6 - 
void Event::test6(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	app->DisplayMessage("Event Test 6 complete\r\n");
}

#endif



