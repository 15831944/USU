/*****************************************************************************
*
*   File:           Request.cpp
*   Class:          All request classes
*   Version:        1.0
*   Project:        Parcel Tracker
*   Author:         Stephen W. Clyde
*   Last Modified:  August 14, 1997
*
*   Modification History:
*   Aug 14, 1997	Initial version
*
*   Description:
*   A Request object represents a command from the client to the server
*
*****************************************************************************/

#include "stdafx.h"

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include "RequestReply.h"
#include "Request.h"
#include "Reply.h"
#include "marshall.h"

#ifdef SERVER
#include "server/server.h"
#endif

#ifdef TESTING
#include "../TestPackage/TestPackage.h"
#endif


/******************************************************************************
*
*  Method:  Response::create
*
*/
Request* Request::create(const Message& msg, const SocketAddress& addr)
{
    Request *r = NULL;

    switch (peekAtType(msg.getData()))
    {
		case UNKNOWN:
			r = NULL;
			break;
		case LOGIN:
			r = new LoginRequest(msg, addr);
			break;
		case DATA:
			break;
		case SCHEDULING:
			break;
		case QUERY:
			break;
		case TERMINATE:
			r = new TerminateRequest(msg, addr);
            break;
        default:
			r = NULL;
    }
    return r;
}

/******************************************************************************
*
*  Request::unmarshall
*
*/
BOOL Request::unmarshall(const char*& ptr, const char* end_ptr)
{
	BOOL result=FALSE;

	if (RequestReply::unmarshall(ptr, end_ptr)==TRUE)
	{
		char tmp;
		if (::unmarshall(ptr, end_ptr, tmp)==TRUE)
		{
			request_type = (REQUEST_TYPE) tmp;
			result=TRUE;
		}
	}

	return result;
}

/******************************************************************************
*
*  Request::marshall
*
*/
BOOL Request::marshall(char*& ptr, const char* end_ptr)
{
    BOOL result=FALSE;

	if (RequestReply::marshall(ptr, end_ptr))
	{	
		char tmp = (char) request_type;
		result=::marshall(ptr, end_ptr, tmp);
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
Request::REQUEST_TYPE Request::peekAtType(const char* data)
{
	REQUEST_TYPE result = UNKNOWN;

	if (data)
	{
	  char tmp = data[1];
	  if (tmp=='U' || tmp=='L' || tmp=='D' || tmp=='S' || tmp=='Q' || tmp=='T')
		result = (REQUEST_TYPE) tmp;
	}

	return result;
}

/******************************************************************************
*
*  Method:  LoginRequest::process
*
*/
BOOL LoginRequest::process(unsigned long request_id)
{
    BOOL result=FALSE;
    DString msg;

#ifdef SERVER
    CServerApp* app = (CServerApp *) AfxGetApp();

	if (getStatus()!=BAD)
	{
		// TO BE DONE LATER
	}
	else
	{
		msg.Format("Attempted to process a bad login request - processing aborted\r\n");
		setStatus(Request::FAILURE);
		app->DisplayMessage(msg);
	}
#endif

    return result;
}


/******************************************************************************
*
*	Method:  LoginRequest::load
*
*/
BOOL LoginRequest::load(const Message& msg)
{
    BOOL result=FALSE;
	setStatus(BAD);

    const char* ptr = msg.getData();
    const char* end_ptr = ptr + msg.getLength();
	if (Request::unmarshall(ptr, end_ptr))
	{
		if (getRequestType()==Request::LOGIN)
			if (::unmarshall(ptr, end_ptr, sub_type)==TRUE)
				if (::unmarshall(ptr, end_ptr, username)==TRUE)
					if (::unmarshall(ptr, end_ptr, password)==TRUE)
					{
						result=TRUE;
						setStatus(NOT_DONE);
					}
    }

    return result;
}

/******************************************************************************
*
*  Method:  LoginRequest::save
*
*/
BOOL LoginRequest::save(Message& msg)
{
	unsigned short lng = getPackLng();
    char* tmp = new char[lng];
    char* ptr = tmp;
    char* end_ptr = ptr + lng;
	BOOL result;

	if (Request::marshall(ptr, end_ptr)==TRUE)
		if (::marshall(ptr, end_ptr, sub_type)==TRUE)
			if (::marshall(ptr, end_ptr, username)==TRUE)
				if (::marshall(ptr, end_ptr, password)==TRUE)
				{
				    msg.setData(tmp, ptr-tmp);
					result = TRUE;
				}

	delete tmp;

    return result;
}

/******************************************************************************
*
*  Method:  TerminateRequest::process
*
*/
BOOL TerminateRequest::process(unsigned long)
{
	BOOL result = FALSE;

#ifdef SERVER
    CServerApp* app = (CServerApp *) AfxGetApp();

	if (getStatus()==Request::NOT_DONE)
	{

		// TO BE FINISHED LATER

		msg.Format("Shutting down\r\n");
		app->DisplayMessage(msg);
		setStatus(Request::SUCCESS);
		result = TRUE;
	}
#endif

    return result;
}

/******************************************************************************
*
*  Method:  TerminateRequest::load
*
*/
BOOL TerminateRequest::load(const Message& msg)
{
    BOOL result=FALSE;
	setStatus(BAD);

    const char* ptr = msg.getData();
    const char* end_ptr = ptr + msg.getLength();
	if (Request::unmarshall(ptr, end_ptr))
	{
		if (getRequestType()==Request::TERMINATE)
		{
			if (::unmarshall(ptr, end_ptr, sub_type)==TRUE)
			{
				result=TRUE;
				setStatus(NOT_DONE);
			}
		}
    }

    return result;
}

/******************************************************************************
*
*  Method:  TerminateRequest::save
*
*/
BOOL TerminateRequest::save(Message& msg)
{
	unsigned short lng = getPackLng();
    char* tmp = new char[lng];
    char* ptr = tmp;
    char* end_ptr = ptr + lng;
	BOOL result;

	if (Request::marshall(ptr, end_ptr)==TRUE)
	{
		if (::marshall(ptr, end_ptr, sub_type)==TRUE)
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

// Test 1 - Constructors and create method
//
void LoginRequest::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	LoginRequest r1;
	assert(r1.getType()==RequestReply::REQUEST);
	assert(r1.getRequestType()==Request::LOGIN);
	assert(r1.getReplyTo()==SocketAddress());
	assert(r1.getStatus()==Request::NOT_DONE);
	assert(r1.sub_type==' ');
	assert(r1.username=="");
	assert(r1.password=="");

	LoginRequest r2(SocketAddress("206.81.134.101",3000));
	assert(r2.getType()==RequestReply::REQUEST);
	assert(r2.getRequestType()==Request::LOGIN);
	assert(r2.getReplyTo()==SocketAddress("206.81.134.101",3000));
	assert(r2.getStatus()==Request::NOT_DONE);
	assert(r2.sub_type==' ');
	assert(r2.username=="");
	assert(r2.password=="");

	Message msg(1000, "RL \0\6stevec\0\7testing", 20);
	LoginRequest r3(msg, SocketAddress("206.81.134.101",3000));
	assert(r3.getType()==RequestReply::REQUEST);
	assert(r3.getRequestType()==Request::LOGIN);
	assert(r3.getReplyTo()==SocketAddress("206.81.134.101",3000));
	assert(r3.getStatus()==Request::NOT_DONE);
	assert(r3.sub_type==' ');
	assert(r3.username=="stevec");
	assert(r3.password=="testing");

	Request* r4 = Request::create(msg, SocketAddress("129.123.7.17",3001));
	assert(r4!=NULL);
	assert(r4->getRequestType()==Request::LOGIN);
	LoginRequest* r5 = (LoginRequest*) r4;

	assert(r5->getType()==RequestReply::REQUEST);
	assert(r5->getReplyTo()==SocketAddress("129.123.7.17",3001));
	assert(r5->getStatus()==Request::NOT_DONE);
	assert(r5->sub_type==' ');
	assert(r5->username=="stevec");
	assert(r5->password=="testing");

	delete r4;

	app->DisplayMessage("LoginRequest Test 1 complete\r\n");
}

// Test 2 - set and get methods
//
void LoginRequest::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	LoginRequest r1("joe","testing");
	assert(r1.getType()==RequestReply::REQUEST);
	assert(r1.getRequestType()==Request::LOGIN);
	r1.setReplyTo(SocketAddress("129.123.1.7",3002));
	assert(r1.getReplyTo()==SocketAddress("129.123.1.7",3002));
	r1.setStatus(SUCCESS);
	assert(r1.getStatus()==SUCCESS);
	assert(r1.getUsername()=="joe");
	assert(r1.getPassword()=="testing");

	app->DisplayMessage("LoginRequest Test 2 complete\r\n");
}

// Test 3 - save and load methods
//
void LoginRequest::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	LoginRequest r1("joe","testing");
	Message m1;
	r1.save(m1);

	LoginRequest r2(m1, SocketAddress("129.123.7.163",3003));
	assert(r2.getType()==RequestReply::REQUEST);
	assert(r2.getRequestType()==Request::LOGIN);
	assert(r2.getReplyTo()==SocketAddress("129.123.7.163",3003));
	assert(r2.getUsername()=="joe");
	assert(r2.getPassword()=="testing");

	app->DisplayMessage("LoginRequest Test 3 complete\r\n");
}

// Test 4 - process
//
void LoginRequest::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	// TO DO

	app->DisplayMessage("LoginRequest Test 3 complete\r\n");
}

// Test case Dispatcher
void LoginRequest::run_tests(void)
{
	LoginRequest::test1();
	LoginRequest::test2();
	LoginRequest::test3();
	LoginRequest::test4();
}


// Test 1 - Constructors and create method
//
void TerminateRequest::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TerminateRequest r1;
	assert(r1.getType()==RequestReply::REQUEST);
	assert(r1.getRequestType()==Request::TERMINATE);
	assert(r1.getReplyTo()==SocketAddress());
	assert(r1.getStatus()==Request::NOT_DONE);
	assert(r1.sub_type==' ');

	TerminateRequest r2(SocketAddress("206.81.134.101",3000));
	assert(r2.getType()==RequestReply::REQUEST);
	assert(r2.getRequestType()==Request::TERMINATE);
	assert(r2.getReplyTo()==SocketAddress("206.81.134.101",3000));
	assert(r2.getStatus()==Request::NOT_DONE);
	assert(r2.sub_type==' ');

	Message msg(1000, "RT ", 3);
	TerminateRequest r3(msg, SocketAddress("206.81.134.101",3000));
	assert(r3.getType()==RequestReply::REQUEST);
	assert(r3.getRequestType()==Request::TERMINATE);
	assert(r3.getReplyTo()==SocketAddress("206.81.134.101",3000));
	assert(r3.getStatus()==Request::NOT_DONE);
	assert(r3.sub_type==' ');

	Request* r4 = Request::create(msg, SocketAddress("129.123.7.17",3001));
	assert(r4!=NULL);
	assert(r4->getRequestType()==Request::TERMINATE);
	TerminateRequest* r5 = (TerminateRequest*) r4;

	assert(r5->getType()==RequestReply::REQUEST);
	assert(r5->getReplyTo()==SocketAddress("129.123.7.17",3001));
	assert(r5->getStatus()==Request::NOT_DONE);
	assert(r5->sub_type==' ');

	delete r4;

	app->DisplayMessage("TerminateRequest Test 1 complete\r\n");
}

// Test 2 - set and get methods
//
void TerminateRequest::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TerminateRequest r1;
	assert(r1.getType()==RequestReply::REQUEST);
	assert(r1.getRequestType()==Request::TERMINATE);
	r1.setReplyTo(SocketAddress("129.123.1.7",3002));
	assert(r1.getReplyTo()==SocketAddress("129.123.1.7",3002));
	r1.setStatus(SUCCESS);
	assert(r1.getStatus()==SUCCESS);

	app->DisplayMessage("TerminateRequest Test 2 complete\r\n");
}

// Test 3 - save and load methods
//
void TerminateRequest::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	TerminateRequest r1;
	Message m1;
	r1.save(m1);

	TerminateRequest r2(m1, SocketAddress("129.123.7.163",3003));
	assert(r2.getType()==RequestReply::REQUEST);
	assert(r2.getRequestType()==Request::TERMINATE);
	assert(r2.getReplyTo()==SocketAddress("129.123.7.163",3003));

	app->DisplayMessage("TerminateRequest Test 3 complete\r\n");
}

// Test 4 - process
//
void TerminateRequest::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	// TO DO

	app->DisplayMessage("TerminateRequest Test 3 complete\r\n");
}

// Test case Dispatcher
void TerminateRequest::run_tests(void)
{
	TerminateRequest::test1();
	TerminateRequest::test2();
	TerminateRequest::test3();
	TerminateRequest::test4();
}


#endif
