/*****************************************************************************
*
*	File:          Reply.cpp
*	Class:         Reply classes of all kinds
*	Version:       1.0
*	Project:       Parcel Tracker
*	Author:        Stephen W. Clyde
*	Last Modified: August 14, 1997
*
*	Modification History:
*
*  	Aug 14, 1997	Initial version
*
*	Description:
*
*	A Reply object represents a response to a request
*/

#include "stdafx.h"

#include <iostream.h>
#include <stdlib.h>
#include "Reply.h"
#include "marshall.h"
#include "Building.h"
#include "Calendar.h"
#include "Event.h"
#include "Location.h"
#include "ReservedTime.h"
#include "MeetingPreference.h"

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif

/******************************************************************************
*
*  Method:  Reply::create
*
*/
Reply* Reply::create(const Message &msg)
{
    Reply *r = NULL;

    switch (peekAtType(msg.getData()))
    {
	    case UNKNOWN:
			break;
		case OBJ:							// Object response
			r = new ObjectReply(msg);
			break;
		case COUNT:							// Count response
			r = new CountReply(msg);
			break;
		case ACK:                           // Ack response
			r = new AckReply(msg);
			break;
		case ERR_RESP:                      // Error response
			r = new ErrorReply(msg);
			break;
		case NEW_ID:                        // New-id response
			r = new NewIdReply(msg);
			break;
    }
    return r;
}

/******************************************************************************
*
*  Reply::unmarshall
*
*/
BOOL Reply::unmarshall(const char*& ptr, const char* end_ptr)
{
	BOOL result=FALSE;

	if (RequestReply::unmarshall(ptr, end_ptr)==TRUE)
	{
		char tmp;
		if (::unmarshall(ptr, end_ptr, tmp)==TRUE)
		{
			reply_type = (REPLY_TYPE) tmp;
			if (::unmarshall(ptr, end_ptr, request_msg_id)==TRUE)
				result=TRUE;
		}
	}

	return result;
}

/******************************************************************************
*
*  Reply::marshall
*
*/
BOOL Reply::marshall(char*& ptr, const char* end_ptr)
{
    BOOL result=FALSE;

	if (RequestReply::marshall(ptr, end_ptr))
	{	
		char tmp = (char) reply_type;
		if (::marshall(ptr, end_ptr, tmp)==TRUE)
			result = ::marshall(ptr, end_ptr, request_msg_id);
	}

    return result;
}

/******************************************************************************
*
*	Request::peekAtType
*
*	This method check the type of packaged RequestReply.  It dependent on the
*	implementation of the save methods.
*
*/
Reply::REPLY_TYPE Reply::peekAtType(const char* data)
{
	REPLY_TYPE result = UNKNOWN;

	if (data)
	{
	  char tmp = data[1];
	  if (tmp=='O' || tmp=='C' || tmp=='A' || tmp=='E' || tmp=='N')
		result = (REPLY_TYPE) tmp;
	}

	return result;
}

/******************************************************************************
*
*  Method:  ObjectReply::load
*
*/
BOOL ObjectReply::load(const Message &msg)
{
    BOOL result=FALSE;
	clear();

    const char* ptr = msg.getData();
    const char* end_ptr = ptr + msg.getLength();
	if (Reply::unmarshall(ptr, end_ptr))
	{
		if (getReplyType()==Reply::OBJ)
		{
			char tmp;
			if (::unmarshall(ptr, end_ptr, tmp)==TRUE)
			{
				obj_type = (OBJ_TYPE) tmp;
				unsigned short lng = end_ptr - ptr;
				switch (obj_type)
				{
					case BUILDING:
						obj = new Building(ptr, lng);
						break;
					case CALENDAR:
						obj = new Calendar(ptr, lng);
						break;
					case EVENT:
						obj = new Event(ptr, lng);
						break;
					case LOCATION:
						obj = new Location(ptr, lng);
						break;
					case RESERVED_TIME:
						obj = new ReservedTime(ptr, lng);
						break;
					case MEETING_PREFERENCE:
						obj = new MeetingPreference(ptr, lng);
						break;
				}
				ptr += lng;
				if (obj)
				{
					result=TRUE;
					obj_cleanup_required=TRUE;
				}
			}
		}
    }

    return result;
}


/******************************************************************************
*
*  Method:  ObjectReply::save
*
*/
BOOL ObjectReply::save(Message& msg)
{
	unsigned short lng = getPackLng();
    char* tmp = new char[lng];
    char* ptr = tmp;
    char* end_ptr = ptr + lng;
	BOOL result;

	if (Reply::marshall(ptr, end_ptr)==TRUE)
	{
		char tmp_type = (char) obj_type;
		if (::marshall(ptr, end_ptr, tmp_type)==TRUE)
		{
			unsigned short lng = end_ptr - ptr;
			if (obj->save(ptr, lng)==TRUE)
			{
				ptr += lng;
				msg.setData(tmp, ptr-tmp);
				result = TRUE;
			}
		}
	}

	delete tmp;

    return result;
}

/******************************************************************************
*
*  Method:  CountReply::load
*
*/
BOOL CountReply::load(const Message &msg)
{
    BOOL result=FALSE;

    const char* ptr = msg.getData();
    const char* end_ptr = ptr + msg.getLength();
	if (Reply::unmarshall(ptr, end_ptr))
	{
		if (getReplyType()==Reply::COUNT)
			result = ::unmarshall(ptr, end_ptr, count);
    }

    return result;
}


/******************************************************************************
*
*  Method:  CountObjectReply::save
*
*/
BOOL CountReply::save(Message& msg)
{
	unsigned short lng = getPackLng();
    char* tmp = new char[lng];
    char* ptr = tmp;
    char* end_ptr = ptr + lng;
	BOOL result;

	if (Reply::marshall(ptr, end_ptr)==TRUE)
	{
		if (::marshall(ptr, end_ptr, count)==TRUE)
		{
			msg.setData(tmp, ptr-tmp);
			result = TRUE;
		}
	}

	delete tmp;

    return result;
}


/******************************************************************************
*
*  Method:  AckReply::load
*
*/
BOOL AckReply::load(const Message &msg)
{
    BOOL result=FALSE;

    const char* ptr = msg.getData();
    const char* end_ptr = ptr + msg.getLength();
	if (Reply::unmarshall(ptr, end_ptr))
	{
		if (getReplyType()==Reply::ACK)
			result = ::unmarshall(ptr, end_ptr, value);
    }

    return result;
}


/******************************************************************************
*
*  Method:  AckReply::save
*
*/
BOOL AckReply::save(Message& msg)
{
	unsigned short lng = getPackLng();
    char* tmp = new char[lng];
    char* ptr = tmp;
    char* end_ptr = ptr + lng;
	BOOL result;

	if (Reply::marshall(ptr, end_ptr)==TRUE)
	{
		if (::marshall(ptr, end_ptr, value)==TRUE)
		{
			msg.setData(tmp, ptr-tmp);
			result = TRUE;
		}
	}

	delete tmp;

    return result;
}

/******************************************************************************
*
*  Method:  ErrorReply::load
*
*/
BOOL ErrorReply::load(const Message &msg)
{
    BOOL result=FALSE;

    const char* ptr = msg.getData();
    const char* end_ptr = ptr + msg.getLength();
	if (Reply::unmarshall(ptr, end_ptr))
	{
		if (getReplyType()==Reply::ERR_RESP)
			result = ::unmarshall(ptr, end_ptr, text);
    }

    return result;
}


/******************************************************************************
*
*  Method:  ErrorReply::save
*
*/
BOOL ErrorReply::save(Message& msg)
{
	unsigned short lng = getPackLng();
    char* tmp = new char[lng];
    char* ptr = tmp;
    char* end_ptr = ptr + lng;
	BOOL result;

	if (Reply::marshall(ptr, end_ptr)==TRUE)
	{
		if (::marshall(ptr, end_ptr, text)==TRUE)
		{
			msg.setData(tmp, ptr-tmp);
			result = TRUE;
		}
	}

	delete tmp;

    return result;
}

/******************************************************************************
*
*  Method:  NewIdReply::load
*
*/
BOOL NewIdReply::load(const Message &msg)
{
    BOOL result=FALSE;

    const char* ptr = msg.getData();
    const char* end_ptr = ptr + msg.getLength();
	if (Reply::unmarshall(ptr, end_ptr))
	{
		if (getReplyType()==Reply::NEW_ID)
			result = ::unmarshall(ptr, end_ptr, new_id);
    }

    return result;
}


/******************************************************************************
*
*  Method:  NewIdReply::save
*
*/
BOOL NewIdReply::save(Message& msg)
{
	unsigned short lng = getPackLng();
    char* tmp = new char[lng];
    char* ptr = tmp;
    char* end_ptr = ptr + lng;
	BOOL result;

	if (Reply::marshall(ptr, end_ptr)==TRUE)
	{
		if (::marshall(ptr, end_ptr, new_id)==TRUE)
		{
			msg.setData(tmp, ptr-tmp);
			result = TRUE;
		}
	}

	delete tmp;

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
#include "Building.h"

// Test 1 - Constructors
//
void ObjectReply::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	ObjectReply r1;
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::OBJ);
	assert(r1.obj_type==ObjectReply::UNKNOWN);
	assert(r1.obj==NULL);
	assert(r1.obj_cleanup_required==FALSE);
	assert(r1.getObject()==NULL);
	assert(r1.getObjectType()==UNKNOWN);

	Building* b1 = new Building;
	b1->setName(DString("Old Main"));
	b1->setAddress(DString("Logan Hill"));
	b1->setCity(DString("Logan"));
	b1->setState(DString("UT"));
	b1->setZip(DString("84322-4205"));

	ObjectReply r2(BUILDING, b1, 100);
	assert(r2.getType()==RequestReply::REPLY);
	assert(r2.getReplyType()==Reply::OBJ);
	assert(r2.obj==b1);
	assert(r2.obj_cleanup_required==FALSE);
	assert(r2.getObject()==b1);
	assert(r2.getObjectType()==BUILDING);

	Message msg;
	r2.save(msg);

	delete b1;

	ObjectReply r3(msg);
	assert(r3.getReplyType()==Reply::OBJ);
	assert(r3.getObjectType()==BUILDING);
	assert(r3.getObject()!=NULL);
	assert(r3.obj_cleanup_required==TRUE);

	Building* b2 = (Building*) r3.getObject();
	assert(b2->getName()=="Old Main");
	assert(b2->getAddress()=="Logan Hill");
	assert(b2->getCity()=="Logan");
	assert(b2->getState()=="UT");
	assert(b2->getZip()=="84322-4205");

	app->DisplayMessage("ObjectReply Test 1 complete\r\n");
}

// Test 2 - save, load, clear and create methods
//
void ObjectReply::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Building* b1 = new Building;
	b1->setName("SER");
	b1->setAddress("800 N. 1000 E.");
	b1->setCity("Logan");
	b1->setState("UT");
	b1->setZip("84322-4205");

	ObjectReply r1(BUILDING, b1, 100);
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::OBJ);
	assert(r1.obj==b1);
	assert(r1.obj_cleanup_required==FALSE);
	assert(r1.getObject()==b1);
	assert(r1.getObjectType()==BUILDING);

	Message msg;
	r1.save(msg);

	delete b1;

	Reply* r2 = Reply::create(msg);
	assert(r2!=NULL);
	assert(r2->getReplyType()==Reply::OBJ);
	ObjectReply* r3 = (ObjectReply*) r2;

	assert(r3->obj_cleanup_required==TRUE);
	assert(r3->getObjectType()==BUILDING);
	assert(r3->getObject()!=NULL);

	Building* b2 = (Building*) r3->getObject();
	assert(b2->getName()=="SER");
	assert(b2->getAddress()=="800 N. 1000 E.");
	assert(b2->getCity()=="Logan");
	assert(b2->getState()=="UT");
	assert(b2->getZip()=="84322-4205");

	r3->clear();
	assert(r3->getObjectType()==UNKNOWN);
	assert(r3->getObject()==NULL);
	assert(r3->obj_cleanup_required==FALSE);

	delete r2;

	app->DisplayMessage("ObjectReply Test 2 complete\r\n");
}

// Test case Dispatcher
void ObjectReply::run_tests(void)
{
	ObjectReply::test1();
	ObjectReply::test2();
}


// Test 1 - Constructors
//
void CountReply::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	CountReply r1;
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::COUNT);
	assert(r1.count==0);
	assert(r1.getCount()==0);

	CountReply r2(5, 100);
	assert(r2.getType()==RequestReply::REPLY);
	assert(r2.getReplyType()==Reply::COUNT);
	assert(r2.count==5);
	assert(r2.getCount()==5);

	Message msg;
	r2.save(msg);

	CountReply r3(msg);
	assert(r3.getType()==RequestReply::REPLY);
	assert(r3.getReplyType()==Reply::COUNT);
	assert(r3.count==5);
	assert(r3.getCount()==5);

	app->DisplayMessage("CountReply Test 1 complete\r\n");
}

// Test 2 - save, load, set, get and create methods
//
void CountReply::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	CountReply r1(5, 100);
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::COUNT);
	assert(r1.count==5);
	assert(r1.getCount()==5);

	r1.setCount(30);
	assert(r1.getCount()==30);

	Message msg;
	r1.save(msg);

	Reply *r2 = Reply::create(msg);
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::COUNT);
	CountReply *r3 = (CountReply*) r2;
	assert(r3->getCount()==30);

	delete r2;

	app->DisplayMessage("CountReply Test 2 complete\r\n");
}

// Test case Dispatcher
void CountReply::run_tests(void)
{
	CountReply::test1();
	CountReply::test2();
}

// Test 1 - Constructors
//
void AckReply::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	AckReply r1;
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::ACK);
	assert(r1.value==0);
	assert(r1.getValue()==0);

	AckReply r2(5, 100);
	assert(r2.getType()==RequestReply::REPLY);
	assert(r2.getReplyType()==Reply::ACK);
	assert(r2.value==5);
	assert(r2.getValue()==5);

	Message msg;
	r2.save(msg);

	AckReply r3(msg);
	assert(r3.getType()==RequestReply::REPLY);
	assert(r3.getReplyType()==Reply::ACK);
	assert(r3.value==5);
	assert(r3.getValue()==5);

	app->DisplayMessage("AckReply Test 1 complete\r\n");
}

// Test 2 - save, load, set, get and create methods
//
void AckReply::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	AckReply r1(5, 100);
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::ACK);
	assert(r1.value==5);
	assert(r1.getValue()==5);

	r1.setValue(30);
	assert(r1.getValue()==30);

	Message msg;
	r1.save(msg);

	Reply *r2 = Reply::create(msg);
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::ACK);
	AckReply *r3 = (AckReply*) r2;
	assert(r3->getValue()==30);

	delete r2;

	app->DisplayMessage("AckReply Test 2 complete\r\n");
}

// Test case Dispatcher
void AckReply::run_tests(void)
{
	AckReply::test1();
	AckReply::test2();
}

// Test 1 - Constructors
//
void ErrorReply::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	ErrorReply r1;
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::ERR_RESP);
	assert(r1.text=="");
	assert(r1.getText()=="");

	ErrorReply r2(DString("Error"), 100);
	assert(r2.getType()==RequestReply::REPLY);
	assert(r2.getReplyType()==Reply::ERR_RESP);
	assert(r2.text=="Error");
	assert(r2.getText()=="Error");

	Message msg;
	r2.save(msg);

	ErrorReply r3(msg);
	assert(r3.getType()==RequestReply::REPLY);
	assert(r3.getReplyType()==Reply::ERR_RESP);
	assert(r2.text=="Error");
	assert(r2.getText()=="Error");

	app->DisplayMessage("ErrorReply Test 1 complete\r\n");
}

// Test 2 - save, load, set, get and create methods
//
void ErrorReply::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	ErrorReply r1(DString("Big Error"), 100);
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::ERR_RESP);
	assert(r1.text=="Big Error");
	assert(r1.getText()=="Big Error");

	r1.setText(DString("Small Error"));
	assert(r1.getText()=="Small Error");

	Message msg;
	r1.save(msg);

	Reply *r2 = Reply::create(msg);
	assert(r2->getType()==RequestReply::REPLY);
	assert(r2->getReplyType()==Reply::ERR_RESP);
	ErrorReply *r3 = (ErrorReply*) r2;
	assert(r3->getText()=="Small Error");

	delete r3;

	app->DisplayMessage("ErrorReply Test 2 complete\r\n");
}

// Test case Dispatcher
void ErrorReply::run_tests(void)
{
	ErrorReply::test1();
	ErrorReply::test2();
}

// Test 1 - Constructors
//
void NewIdReply::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	NewIdReply r1;
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::NEW_ID);
	assert(r1.new_id==0);
	assert(r1.getNewId()==0);

	NewIdReply r2(5, 100);
	assert(r2.getType()==RequestReply::REPLY);
	assert(r2.getReplyType()==Reply::NEW_ID);
	assert(r2.new_id==5);
	assert(r2.getNewId()==5);

	Message msg;
	r2.save(msg);

	NewIdReply r3(msg);
	assert(r3.getType()==RequestReply::REPLY);
	assert(r3.getReplyType()==Reply::NEW_ID);
	assert(r3.new_id==5);
	assert(r3.getNewId()==5);

	app->DisplayMessage("NewIdReply Test 1 complete\r\n");
}

// Test 2 - save, load, set, get and create methods
//
void NewIdReply::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	NewIdReply r1(5, 100);
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::NEW_ID);
	assert(r1.new_id==5);
	assert(r1.getNewId()==5);

	r1.setNewId(30);
	assert(r1.getNewId()==30);

	Message msg;
	r1.save(msg);

	Reply *r2 = Reply::create(msg);
	assert(r1.getType()==RequestReply::REPLY);
	assert(r1.getReplyType()==Reply::NEW_ID);
	NewIdReply *r3 = (NewIdReply*) r2;
	assert(r3->getNewId()==30);

	delete r2;

	app->DisplayMessage("NewIdReply Test 2 complete\r\n");
}

// Test case Dispatcher
void NewIdReply::run_tests(void)
{
	NewIdReply::test1();
	NewIdReply::test2();
}


#endif