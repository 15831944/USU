/*****************************************************************************
*
*	File:          Event.cpp
*	Class:         Event
*	Version:       1.0
*	Project:       Distributed Calendar System
*	Author:        Stephen W. Clyde
*	Last Modified: September 5, 2001
*
*	Modification History:
*
*  	Sep. 5, 2001	Initial version
*
*	Description:
*
*	This file contains the implementation and test cases for Building.
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <fstream.h>
#include "Event.h"
#include "Marshall.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/******************************************************************************
*
*  Method:  Event::load
*
*  This function loads a Event object from string data.
*
*  After you load a Event object, the validity of the object can be checked
*  with the isValid() method.
*/
BOOL Event::load(const char* buffer, unsigned short& buffer_lng)
{
	BOOL result = FALSE;
	valid=FALSE;
	unsigned short lng;
	char  tmp;

	const char* ptr = buffer;
    const char* end_ptr = ptr + buffer_lng;
    if (unmarshall(ptr, end_ptr, id)==TRUE)
	  if (unmarshall(ptr, end_ptr, tmp)==TRUE)
	  {
		event_type = (EVENT_TYPE) tmp;
		if (unmarshall(ptr, end_ptr, name)==TRUE)
          if (unmarshall(ptr, end_ptr, description)==TRUE)
            if (unmarshall(ptr, end_ptr, note)==TRUE)
			{
			  lng = end_ptr - ptr;
			  if (event_date.load(ptr, lng)==TRUE)
			  {
			    ptr += lng;
				lng = end_ptr - ptr;
				if (event_time.load(ptr, lng)==TRUE)
				{
				  ptr += lng;
				  if (unmarshall(ptr, end_ptr, location_id)==TRUE)
				    if (unmarshall(ptr, end_ptr, tmp)==TRUE)
					{
					  status = (STATUS) tmp;
					  result=validate();
					}
				}
			  }
			}
	  }
	buffer_lng = ptr - buffer;

	return result;
}

/******************************************************************************
*
*  Method:  Event::save
*
*  This function save a Event object into a string.
*
*/
BOOL Event::save(char* buffer, unsigned short& buffer_lng) const
{
    BOOL result = FALSE;
	unsigned short lng;
	char tmp;

    char* ptr = buffer;
    const char* end_ptr = buffer + buffer_lng;

	if (marshall(ptr, end_ptr, id)==TRUE)
	{
	  tmp = (char) event_type;
	  if (marshall(ptr, end_ptr, tmp)==TRUE)
	  {
		if (marshall(ptr, end_ptr, name)==TRUE)
		  if (marshall(ptr, end_ptr, description)==TRUE)
		    if (marshall(ptr, end_ptr, note)==TRUE)
			{
			  lng = end_ptr - ptr;
			  if (event_date.save(ptr, lng)==TRUE)
			  {
				ptr += lng;
				lng = end_ptr - ptr;
				if (event_time.save(ptr, lng)==TRUE)
				{
				  ptr += lng;
                  if (marshall(ptr, end_ptr, location_id)==TRUE)
				  {
				    tmp = (char) status;
                    result = marshall(ptr, end_ptr, tmp);
				  }
				}
			  }
			}
	  }
	}

	buffer_lng = ptr - buffer;
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
	assert(e1.id==-1);
	assert(e1.event_type==FACE2FACE);
	assert(e1.name=="");
	assert(e1.description=="");
	assert(e1.note=="");
	assert(e1.event_date<=CalendarDate());
	assert(e1.event_time==TimeBlock());
	assert(e1.location_id==0);
	assert(e1.status==UNKNOWN);

	char *tmp = "\0\0\0\3"
				"V"
				"\0\22Doctor Appointment"
				"\0\13Eye examine"
				"\0\12Be earlier"
				"\7\321\0\1\0\2"
				"\0\12\0\36\0\36"
				"\0\0\0\1"
				"U";

	unsigned short lng = 67;
    Event e2(tmp, lng);
	assert(lng==67);

	assert(e2.id==3);
	assert(e2.event_type==VIDEO_CALL);
	assert(e2.name=="Doctor Appointment");
	assert(e2.description=="Eye examine");
	assert(e2.note=="Be earlier");
	assert(e2.event_date==CalendarDate(2001,1,2));
	assert(e2.event_time==TimeBlock(10,30,30));
	assert(e2.location_id==1);
	assert(e2.status==UNSCHEDULED);

	Event e3(e2);
	assert(e3.id==3);
	assert(e3.event_type==VIDEO_CALL);
	assert(e3.name=="Doctor Appointment");
	assert(e3.description=="Eye examine");
	assert(e3.note=="Be earlier");
	assert(e3.event_date==CalendarDate(2001,1,2));
	assert(e3.event_time==TimeBlock(10,30,30));
	assert(e3.location_id==1);
	assert(e3.status==UNSCHEDULED);

	app->DisplayMessage("Event Test 1 complete\r\n");
}

// Test 2 - Get and set methods and isValid method
void Event::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Event e1;

	BOOL result;

	result=e1.setId(2532);
	assert(e1.getId()==2532);
	result=e1.setId(0);
	assert(e1.getId()==0);
	result=e1.setId(6436);
	assert(e1.getId()==6436);
	result=e1.setId(-1);
	assert(e1.getId()==-1);
	result=e1.setId(-2364);
	assert(e1.getId()==-2364);

	result=e1.setEventType(VOICE_CALL);
	assert(e1.getEventType()==VOICE_CALL);

	result=e1.setEventType('F');
	assert(e1.getEventType()==FACE2FACE);

	result=e1.setName(DString("Group Meeting"));
	assert(e1.getName()=="Group Meeting");
	result=e1.setName(DString(""));
	assert(e1.getName()=="");
	result=e1.setName(DString("Big Group Meeting"));
	assert(e1.getName()=="Big Group Meeting");

	result=e1.setDescription(DString("This will be an important group meeting"));
	assert(e1.getDescription()=="This will be an important group meeting");
	result=e1.setDescription(DString(""));
	assert(e1.getDescription()=="");
	result=e1.setDescription(DString("This will be a really really really important group meeting"));
	assert(e1.getDescription()=="This will be a really really really important group meeting");

	result=e1.setNote(DString("This meeting will probably be boring"));
	assert(e1.getNote()=="This meeting will probably be boring");
	result=e1.setNote(DString(""));
	assert(e1.getNote()=="");
	result=e1.setNote(DString("This will be a really really really really really realy exciting"));
	assert(e1.getNote()=="This will be a really really really really really realy exciting");

	result=e1.setDate(CalendarDate(2001,5,30));
	assert(e1.getDate()==CalendarDate(2001,5,30));

	result=e1.setTime(TimeBlock(10,30,45));
	assert(e1.getTime()==TimeBlock(10,30,45));

	result=e1.setLocationId(2532);
	assert(e1.getLocationId()==2532);
	result=e1.setLocationId(0);
	assert(e1.getLocationId()==0);
	result=e1.setLocationId(6436);
	assert(e1.getLocationId()==6436);
	result=e1.setLocationId(-1);
	assert(e1.getLocationId()==-1);
	result=e1.setLocationId(-2364);
	assert(e1.getLocationId()==-2364);

	result=e1.setStatus("Scheduled");
	assert(e1.getStatus()==SCHEDULED);
	result=e1.setStatus("Unscheduled");
	assert(e1.getStatus()==UNSCHEDULED);
	result=e1.setStatus("aaaa");
	assert(e1.getStatus()==UNSCHEDULED);

	app->DisplayMessage("Event Test 2 complete\r\n");
}

// Test 3 - Load and save methods and string-based constructor
void Event::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	BOOL result;

	Event e0;
	unsigned tmp_lng = e0.getPackLng();
	assert(tmp_lng==28);

	Event e1;
	result=e1.setId(2532);
	result=e1.setEventType(VOICE_CALL);
	result=e1.setName(CString("Group Meeting"));
	result=e1.setDescription(DString("This will be an important group meeting"));
	result=e1.setNote(DString("This meeting will probably be boring"));
	result=e1.setDate(CalendarDate(2001,5,30));
	result=e1.setTime(TimeBlock(10,0,60));
	result=e1.setLocationId(2532);
	result=e1.setStatus("Scheduled");
	assert(e1.getStatus()==SCHEDULED);

	unsigned short lng = e1.getPackLng();
	char *tmp = new char[lng];
	e1.save(tmp, lng);
	assert(lng==e1.getPackLng());

	Event e2(tmp, lng);
	assert(lng==e1.getPackLng());

	assert(e2.getId()==2532);
	assert(e2.getEventType()==VOICE_CALL);
	assert(e2.getName()=="Group Meeting");
	assert(e2.getDescription()=="This will be an important group meeting");
	assert(e2.getNote()=="This meeting will probably be boring");
	assert(e2.getDate()==CalendarDate(2001,5,30));
	assert(e2.getTime()==TimeBlock(10,0,60));
	assert(e2.getLocationId()==2532);
	assert(e2.getStatus()==SCHEDULED);

	delete tmp;

	app->DisplayMessage("Event Test 3 complete\r\n");
}

// Test 4 - Comparison function and operators
void Event::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Event e1;
	e1.setId(0);
	Event e2;
	e2.setId(3);
	Event e3;
	e3.setId(10);
	Event e4;
	e4.setId(10);

	assert(e1<e2);
	assert(e2>e1);
	assert(e1<=e2);
	assert(e2>=e1);
	assert(e1!=e2);
	assert(e2<e3);
	assert(e3>e2);
	assert(e2<=e3);
	assert(e3>=e2);
	assert(e3!=e2);
	assert(e3==e4);
	assert(e3<=e4);
	assert(e4>=e4);

	app->DisplayMessage("Event Test 4 complete\r\n");
}

// Test 5 - Validation functions
void Event::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	BOOL result;

	Event e1;
	result=e1.setId(2532);
	result=e1.setEventType(VOICE_CALL);
	result=e1.setName(CString("Group Meeting"));
	result=e1.setDescription(CString("This will be an important group meeting"));
	result=e1.setNote(CString("This meeting will probably be boring"));
	result=e1.setDate(CalendarDate(2001,5,30));
	result=e1.setTime(TimeBlock(10,0,60));
	result=e1.setLocationId(2532);
	result=e1.setStatus("Scheduled");

	assert(e1.getValid()==TRUE);
	result=e1.setDate(CalendarDate(2001,14,30));
	assert(result==FALSE);
	assert(e1.getValid()==FALSE);
	result=e1.setTime(TimeBlock(24,0,0));
	assert(result==FALSE);
	assert(e1.getValid()==FALSE);

	app->DisplayMessage("Event Test 5 complete\r\n");
}

// Test case Dispatcher
void Event::run_tests(void)
{
	Event::test1();
	Event::test2();
	Event::test3();
	Event::test4();
	Event::test5();
}


#endif



