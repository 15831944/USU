/******************************************************************************
*
*
*	File:       Message.cpp
*	Class:	   Message
*	Project:	   Distributed Calendar System
*	Author:	   Stephen W. Clyde
*	Last Motified:  
*
*	Modification History:
*
*	Aug 24, 1997   Initial Version
*
*	Description:
*
*    This file contains method implementations for the Message class.
*    It also contains class's test logic.
*
******************************************************************************/

#include "stdafx.h"

#include <assert.h>
#include <iostream.h>
#include <stdlib.h>

#include "Message.h"
#include "LogicalClock.h"
#include "marshall.h"
#include "ComChannel.h"
#include <mmsystem.h>

#if defined(TESTING)
	#include "../TestPackage/TestPackage.h"
	extern CTestPackageApp theApp;
#else
	#ifdef SERVER
		#include "server\server.h"
	#else
		#include "client\client.h"
	#endif
#endif

unsigned long Message::next_msg_id = 1;
unsigned short Message::max_size=1024;

CString GetErrorMessage(UINT nErrorCode)
{
	CString message;
	switch (nErrorCode)
	{
	case 0:
		message = CString("no error occured");
		break;
	case WSANOTINITIALISED:
		message = CString("WSANOTINITIALISED: A successful AfxSocketInit must occur before using this API.");
		break;
	case WSAEINPROGRESS:
		message = CString("WSAEINPROGRESS: A blocking Windows Sockets call is in progress.");
		break;
	case WSAEAFNOSUPPORT:
		message = CString("WSAEAFNOSUPPORT: Addresses in the specified family cannot be used with this socket.");
		break;
	case WSAEWOULDBLOCK:
		message = CString("WSAEWOULDBLOCK: The socket is marked as nonblocking and the connection cannot be completed immediately.");
		break;
	case WSAENETDOWN:
		message = CString("WSAENETDOWN: Network subsystem failed");
		break;
	case WSAECONNRESET:
		message = CString("WSAECONNRESET: Connection reset by remote side");
		break;
	case WSAECONNABORTED:
		message = CString("WSAECONNABORTED: Connection aborted");
		break;
	case WSAEADDRINUSE:
		message = CString("WSAEADDRINUSE: The specified address is already in use");
		break;
	case WSAEADDRNOTAVAIL:
		message = CString("WSAEADDRNOTAVAIL: The specified address is not available from the local machine");
		break;
	case WSAECONNREFUSED:
		message = CString("WSAECONNREFUSED: The attempt to connect was forcefully rejected");
		break;
	case WSAEDESTADDRREQ:
		message = CString("WSAEDESTADDRREQ: A destination address is required");
		break;
	case WSAEFAULT:
		message = CString("WSAEFAULT: The lpSockAddrLen argument is incorrect");
		break;
	case WSAEINVAL:
		message = CString("WSAEINVAL: The socket is already bound to an address");
		break;
	case WSAEISCONN:
		message = CString("WSAEISCONN: The socket is already connected");
		break;
	case WSAEMFILE:
		message = CString("WSAEMFILE: No more file descriptors are available");
		break;
	case WSAENETUNREACH:
		message = CString("WSAENETUNREACH: The network cannot be reached from this host at this time");
		break;
	case WSAENOBUFS:
		message = CString("WSAENOBUFS: No buffer space is available. The socket cannot be connected");
		break;
	case WSAENOTCONN:
		message = CString("WSAENOTCONN: The socket is not connected");
		break;
	case WSAENOTSOCK:
		message = CString("WSAENOTSOCK: The descriptor is a file, not a socket");
		break;
	case WSAETIMEDOUT:
		message = CString("WSAETIMEDOUT: The attempt to connect timed out without establishing a connection");
		break;
	default:
		message.Format("Unknown error has occured.  Code = %i",nErrorCode);
	}
	return message;
}

/******************************************************************************
*
*	Message::send
*
*	This method sends the current Message to the specified
*	address and returns immediately
*
*/
unsigned long Message::send(const SocketAddress& addr, ComChannel * ptrCommChannel) // = NULL
{
	unsigned long result = 0;

	// Get a message id for this message,
	// If it doesn't already have one
	if (id == 0)
		id = getNextMsgId();
	result = id;

	// Increment the process's clock for
	// this send event.
	LogicalClock * ptrClock = (LogicalClock *)(&theApp.my_clock);

	if (ptrCommChannel == NULL)
		ptrCommChannel = (ComChannel *)(&theApp.m_commChannel);

	// Copy the process's clock into the
	// message, as the Message's timestamp
	timestamp = *ptrClock;

	// Set up a char buffer into which the
	// Message will be marshalled
	
	// include the the id, the timestamp, the data length, the data, the address? - no probably not the address
	unsigned short messageLength = getPackLng();
	char * messageBuff = new char[messageLength];
	
	// Marshall the Message into the
	// character buffer
	if (!save(messageBuff,messageLength))
	{
		MessageBox(NULL,"Failed to marshall message.  Message will not be sent.",NULL,MB_ICONWARNING);
		return 0;
	}

	// Send out the marshalled data using
	// the socket's send operation (See
	// MFC documentation
	if (ptrCommChannel->SendTo(messageBuff,messageLength,addr.getPort(),addr.getHost()) == SOCKET_ERROR )
	{
		DWORD errCode = GetLastError();
		CString message;
		message.Format("An error occured on a message send operation.  Error: %s ", GetErrorMessage(errCode));
		MessageBox(NULL,message,"Error",MB_ICONWARNING);
		return 0;
	}

	// Clean up any temporary buffer that might have
	// created to hold the marshalled data
	delete [] messageBuff;

	// If all the characters got sent out
    // then return this message's id as an
	// indication of success; otherwise,
	// return 0.

	return result;
}

/******************************************************************************
*
*	Message::receive
*
*	This method tries to receive a messsage within a specific amount of time.
*
*	Parameters:
*		max_time		Time limit
*		addr			Input/ouput parameter.  If a non-empty address is
*						specified on input, the only messages from that
*						source will be accepted.  When a message is accepted
*						is parameter will hold the source address.
*
*/
Message* Message::receive(unsigned long max_time, SocketAddress &from_addr, ComChannel * ptrCommChannel) // = NULL
{
	Message* result = NULL;

	// Try to get a datagram from the communication channel
	// within the specified time limit.  If an address is
	// given, use it as a filter so only datagrams from that
	// address will be accepted.
	BOOL msgReceived = FALSE;
	
	char * messageBuff = new char[max_size];

	// ptrCommChannel should be NULL in all cases except testing cases
	if (ptrCommChannel == NULL)
		ptrCommChannel = (ComChannel *)(&theApp.m_commChannel);
	
	DWORD endTime = timeGetTime() + max_time;
	CString Address = from_addr.getHost();
	unsigned int Port = from_addr.getPort();

	int rValue = ptrCommChannel->ReceiveFrom(messageBuff,max_size,Address,Port);
	
	while (true)
	{
		if (rValue == SOCKET_ERROR)
		{ 
			DWORD lastError = GetLastError();
			if (lastError == WSAEWOULDBLOCK)
			{
				// we are still waiting for data
			}
			else 
			{
				// let's see what this error is...
				CString message;
				message.Format("ReceiveFrom returned SOCKET_ERROR, Error: %s",GetErrorMessage(lastError));
				MessageBox(NULL,message,"Error",MB_ICONWARNING);
				delete [] messageBuff;
				return 0;
			}
		}
		else if (rValue > 0)
		{
			msgReceived = TRUE;
			break;
		}
		else
		{
			CString message;
			message.Format("rValue != SOCKET_ERROR and rValue = %i",rValue);
			MessageBox(NULL,message,NULL,MB_ICONWARNING);
		}

		if (timeGetTime() >= endTime)
			break;
		else
			Sleep(25);
		rValue = ptrCommChannel->ReceiveFrom(messageBuff,max_size,Address,Port);
	}
	

	 
	// If we got something
	if (msgReceived)
	{
		// Create a new Message using that datagram
		result = new Message;
		unsigned short length = rValue;
		result->load(messageBuff,length);
		// Get the timestamp from the incoming message
		// and compare/merge with this process's clock
		theApp.my_clock.Merge(result->getTimestamp());
		// Increment the clock
		theApp.my_clock++;
		// set from_addr to return the address of the sender
		result->setAddress(SocketAddress(Address,Port));
	}
	
	delete [] messageBuff;
	return result;
}

/******************************************************************************
*
*  Message::load
*
*  This method unmarshalls a Message
*
*/
BOOL Message::load(const char *buffer, unsigned short& lng)
{
	BOOL result = FALSE;
	unsigned short tmp_lng;

	clear();							// Clear out the message in preparation of
										// loading new data

	const char *ptr = buffer;
	const char *end_ptr = ptr + lng;
	if (unmarshall(ptr, end_ptr, id)==TRUE)
	{
		tmp_lng = end_ptr - ptr;
		if (timestamp.load(ptr, tmp_lng)==TRUE)
		{
			ptr += tmp_lng;
		    if (unmarshall(ptr, end_ptr, data_lng)==TRUE)
				if (data_lng>0)
				{
					data = new char[data_lng];
					result = unmarshall(ptr, end_ptr, data, data_lng);
				}
				else
					result = TRUE;
		}
	}

	lng = ptr - buffer;					// Return the number of bytes consumed from the
										// buffer

	return result;
}

/******************************************************************************
*
*  Message::save
*
*  This method marshalls a Message
*
*/
BOOL Message::save(char *buffer, unsigned short& lng)
{
	BOOL result = FALSE;

	unsigned short tmp_lng;

	char *ptr = buffer;
	char *end_ptr = buffer + lng;

	if (buffer)
	{
		if (marshall(ptr, end_ptr, id)==TRUE)
		{
			tmp_lng = end_ptr - ptr;
			if (timestamp.save(ptr, tmp_lng)==TRUE)
			{
				ptr += tmp_lng;
				if (marshall(ptr,end_ptr,data_lng)==TRUE)
					if (marshall(ptr, end_ptr, data, data_lng)==TRUE)
						result = TRUE;
			}
		}
	}

	lng = ptr - buffer;

	return result;
}

/******************************************************************************
*
*  Message::clearData
*
*  This method clears out the data for an existing message
*
*/
void Message::clearData(void)
{ 
	if (data)							// Delete old data
		delete data;
    data=NULL;
    data_lng=0;
}

/******************************************************************************
*
*  Message::clear
*
*  This method clears out an existing message
*
*/
void Message::clear(void)
{ 

	id=0;								// Reset message id to 0
	timestamp.clear();					// Make sure the Message's timestamp is
										// cleared just in case the load fails
	clearData();						// Clear out the data
}

/******************************************************************************
*
*  Message::setData
*
*  This method fills the message with data by copying it from a buffer.
*
*/
void Message::setData(const char *buffer, int lng)
{
   clearData();
   if (buffer && lng>0)
   {
      data_lng = lng;
      data = new char[data_lng];
      memcpy(data, buffer, data_lng);
   }
}

/******************************************************************************
*
*	Message::setData
*
*	This method compares the current message with another.  The comparision
*	is based on the message id.
*
*/
int Message::compare(const Message &m) const
{
  int result = 0;
  if (id<m.id)
	 result = -1;
  else if (id>m.id)
	 result = 1;

  return result;
}

#ifdef TESTING
/*****************************************************************************
*
*   Test cases
*
*/

#include <fstream.h>
#include <strstrea.h>

// Test 1
// Check out the class constructors
//
void Message::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	// testing default constructor
	Message m1;
	assert(m1.id==0);
	assert(m1.data==NULL);
	assert(m1.data_lng==0);
	assert(m1.timestamp==LogicalClock(0));

	Message m8(14);
	assert(m8.id==14);
	assert(m8.data==NULL);
	assert(m8.data_lng==0);
	assert(m8.timestamp==LogicalClock(0));

	// testing full member constructor
	char *str = new char[10];
	strcpy(str,"testing");
	unsigned short len = strlen(str);

	Message m2(12, str, len);
	assert(m2.id==12);
	assert(memcmp(m2.data, str, len)==0);
	assert(m2.data_lng==len);
	assert(m2.timestamp==LogicalClock(0));

	// testing Message(const char *, int)
	len=12;
	Message m3("\0\0\0\1\0\0\0\5\0\0",len);
	assert(m3.id==1);
	assert(m3.data==NULL);
	assert(m3.data_lng==0);
	assert(m3.timestamp==LogicalClock(5));

	len=17;
	Message m4("\0\0\0\5\0\0\0\6\0\5Hello",len);
	assert(m4.id==5);
	assert(memcmp(m4.data,"Hello",5)==0);
	assert(m4.data_lng==5);
	assert(m4.timestamp==LogicalClock(6));

	len=3;
	Message m5("\0\0\0\6\0\0\1\3\0\5Hello",len);
	assert(m5.id==0);
	assert(m5.data==NULL);
	assert(m5.data_lng==0);
	assert(m5.timestamp==LogicalClock(0));

	// testing copy constructor
	
	Message m6(m4);
	assert(m6.id==5);
	assert(memcmp(m6.data,"Hello",5)==0);
	assert(m6.data_lng==5);
	assert(m6.timestamp==LogicalClock(6));

	Message m7(m5);
	assert(m7.id==0);
	assert(m7.data==NULL);
	assert(m7.data_lng==0);
	assert(m7.timestamp==LogicalClock(0));

	delete str;

	app->DisplayMessage("Test Case 1 - Complete\r\n");
}

// Test 2
// Check out load and assignment operator
//
void Message::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	BOOL result;
	Message m1;
	unsigned short lng=12;
	result = m1.load("\0\0\0\1\0\0\0\3\0\0",lng);
	assert(result==TRUE);
	assert(lng==10);
	assert(m1.id==1);
	assert(m1.data==NULL);
	assert(m1.data_lng==0);
	assert(m1.timestamp==LogicalClock(3));

	Message m2;
	lng=15;
	result = m2.load("\0\0\0\5\0\0\0\4\0\5Hello",lng);
	assert(result==TRUE);
	assert(lng==15);
	assert(m2.id==5);
	assert(memcmp(m2.data,"Hello",5)==0);
	assert(m2.data_lng==5);
	assert(m2.timestamp==LogicalClock(4));

	lng=3;
	result = m2.load("\5\0\0\0Garabage",lng);
	assert(result==FALSE);
	assert(lng==0);
	assert(m2.id==0);
	assert(m2.data==NULL);
	assert(m2.data_lng==0);
	assert(m2.timestamp==LogicalClock(0));

	
	app->DisplayMessage("Test Case 2 - Complete\r\n");
}

// Test 3
// Check out other set functions, clear and save
//
void Message::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	BOOL result;
	unsigned short lng;
	Message m1;
	m1.setId(14);
	assert(m1.id == 14);
	m1.setData("penny",5);
	assert(memcmp(m1.data,"penny",5)==0);
	assert(m1.data_lng==5);
	m1.setData("",0);
	assert(m1.data==NULL);
	assert(m1.data_lng==0);
	assert(m1.timestamp==LogicalClock(0));

	lng = 15;
	Message m4("\5\4\3\1\0\0\2\3\0\5Hello", lng);
	assert(lng==15);
	char buf[20];
	result=m4.save(buf, lng);
	assert(lng==15);
	assert(result==TRUE);
	assert(memcmp(buf,"\5\4\3\1\0\0\2\3\0\5Hello",15)==0); // 54312300

	lng=10;
	result = m1.save(buf, lng);
	assert(result==TRUE);
	assert(lng==10);
	assert(memcmp(buf,"\0\0\0\16\0\0\0\0\0\0",10)==0);

	char* tmp_buf=NULL;
	lng=20;
	result = m4.save(tmp_buf, lng);
	assert(result==FALSE);
	assert(tmp_buf==NULL);

	m4.clear();
	assert(m4.data==NULL);
	assert(m4.data_lng==0);

	app->DisplayMessage("Test Case 3 - Complete\r\n");
}


// Test 4
// Check out access functions
//
void Message::test4(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Message m1;
	char *buf=new char[20];
	int tmp;
	unsigned short lng;

	tmp = m1.getId();
	assert(tmp==m1.id);
	tmp = m1.getLength();
	assert(tmp==m1.data_lng);
	memcpy(buf,m1.getData(),m1.data_lng);
	assert(memcmp(buf,m1.data,m1.data_lng)==0);

	lng=17;
	Message m4("\0\0\0\4\0\0\0\3\0\5Hello", lng);
	tmp = m4.getId();
	assert(tmp==m4.id);
	tmp = m4.getLength();
	assert(tmp==m4.data_lng);
	memcpy(buf,m4.getData(),m4.data_lng);
	assert(memcmp(buf,m4.data,m4.data_lng)==0);
	assert(m4.getTimestamp()==LogicalClock(3));

	app->DisplayMessage("Test Case 4 - Complete\r\n");
}

//	Test 5
//	Check out send and receive methods
//
void Message::test5(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	Message m1;

	// TO DO
	CString ip_address_1;
	UINT ip_port_1;
	CString ip_address_2("127.0.0.1");
	UINT ip_port_2;
	
	ComChannel c1(0);
	assert(c1.getStatus()==TRUE);
	c1.GetSockName(ip_address_1, ip_port_1);
	ComChannel c2(0);
	assert(c2.getStatus()==TRUE);
	c2.GetSockName(ip_address_2, ip_port_2);
	
	SocketAddress a1(ip_address_1,ip_port_1);
	SocketAddress a2("127.0.0.1",ip_port_2);

	m1.data = new char[25];
	m1.data_lng = 25;
	strcpy(m1.data,"This is a test message.");

	assert(m1.send(a2,&c1));
	Message * ptrMessage = Message::receive(500,a1,&c2);
	assert(ptrMessage);
	assert(strcmp(ptrMessage->data,m1.data)==0);

	app->DisplayMessage("Test Case 5 - Complete\r\n");
}

void Message::run_tests(void)
{
	Message::test1();
	Message::test2();
	Message::test3();
	Message::test4();
	Message::test5();
}

#endif



