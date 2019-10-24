/*****************************************************************************
*
*  File:          ComChannel.cpp
*  Class:         ComChannel
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*
*/

#include "stdafx.h"
#include <stdlib.h>
#include <iostream.h>
#include <assert.h>
#include "ComChannel.h"
#include "Event.h"

const char* ACK="ACK";
const char* NAK="NAK";

/*****************************************************************************
*
*  ComChannel Constructor
*
*  This builds and setups up a communication channel for requesting and sending
*  calendering requests and events
*
*  Parameters:
*     nSocketPort    The socket port number
*/
ComChannel::ComChannel(UINT nSocketPort)
{
	status = Create(nSocketPort,SOCK_DGRAM);
	if (status==FALSE)
	{
		last_error = GetLastError();
		if (last_error == 10048) // means socket is already in use...
		{
			CString m;
			m.Format("Socket cannot be created with socket port = %i.  It appears this socket is already in use.",nSocketPort);
			MessageBox(NULL,m,"Error",MB_ICONSTOP);
		}
		else
		{
			CString m;
			m.Format("Socket cannot be created with socket port = %i.  Error # %i.",nSocketPort,last_error);
			MessageBox(NULL,m,"Error",MB_ICONSTOP);
		}
	}
	else
		last_error = 0;
}

/*****************************************************************************
*
*  ComChannel::SendEvent(Event& event, DString &remote_ip, UINT remote_port);
*
*  This method send an event to a remote process.
*
*  Parameters:
*     event        a reference to an event object.  The contents of the event
*                  object are replaced the data received on the datagram.
*     remote_ip    a reference to a string containing the ip address of the remote process
*     remote_port  a reference to an integer containing the ip port of the remote process
*
*  Output:
*     TRUE		   Event was sent
*     FALSE		   Communication or data failure.  Call GetLastError() to get an error
*				   code in the case of a communication failure.
*/
BOOL ComChannel::SendEvent(Event &event, DString& server_ip, UINT server_port)
{
	DString tmp;

	event.save(tmp);
	char* buffer=tmp.GetBuffer(Event::LNG+1);
	int count = SendTo(buffer, Event::LNG, server_port, server_ip);
	status = ((count==Event::LNG) ? TRUE : FALSE);
	return status;
}

/*****************************************************************************
*
*  ComChannel::ReceiveEvent(Event& event, DString &remote_ip, UINT& remote_port, unsigned long max_time);
*
*  This method receives a parcel and loads the data into the into the parameter
*  parcel object.
*
*  Parameters:
*     event        a reference to an event object.  The contents of the event
*                  object are replaced the data received on the datagram.
*     server_ip    a reference to a string into which ip of the server that
*                  sent the parcel will be written.
*     server_port  a reference to an integer into which port of the server that
*                  sent the parcel will be written.
*     max_time	   Max time to wait, in milliseconds
*
*  Output:
*     TRUE		   A good parcel was received
*     FALSE		   Communication or data failure.  Call GetLastError() to get an error
*				   code in the case of a communication failure.
*/
BOOL ComChannel::ReceiveEvent(Event &event, DString& server_ip, UINT& server_port, unsigned long max_time)
{
	status = FALSE;
	DString data;
	char	*buffer = new char[Event::LNG+1];

	DWORD last_err;
    int count = 0;
	int total_count = 0;
	unsigned long wait_time = 0;
	do
	{
		 count = ReceiveFrom(buffer+total_count, Event::LNG-total_count, server_ip, server_port);
		 if (count>0)
		 {
		    total_count += count;
			last_err=0;
		 }
		 else
		 {
	        last_err = GetLastError();
			Sleep(25);
			wait_time += 25;
		 }
	}
	while (total_count<Event::LNG && wait_time<max_time && (last_err==WSAEWOULDBLOCK || last_err==0));

	if (total_count == Event::LNG)
	{
		buffer[total_count]=0;
	    data = buffer;
	    status = event.load(data);
	}

	delete buffer;

	return status;
}

/*****************************************************************************
*
*  ComChannel::SendAck(DString &remote_ip, UINT& remote_port)
*
*  This method sends an acknowledgement to a remote process
*
*  Parameters:
*    remote_id    An string contains the ip of the target process
*    remote_port  An unsigned integer contains the port number of the target process
*
*  Output:
*    TRUE         Success
*    FALSE        Communication failure
*/
BOOL ComChannel::SendAck(DString &remote_ip, UINT& remote_port)
{
	int count = SendTo(ACK, strlen(ACK), remote_port, remote_ip);
	status = ((count==strlen(ACK)) ? TRUE : FALSE);
	return status;
}

/*****************************************************************************
*
*  ComChannel::SendNak(DString &remote_ip, UINT& remote_port)
*
*  This method sends a negative acknowledgement to a remote process
*
*  Parameters:
*    remote_id    An string contains the ip of the target process
*    remote_port  An unsigned integer contains the port number of the target process
*
*  Output:
*    TRUE         Success
*    FALSE        Communication failure
*/
BOOL ComChannel::SendNak(DString &remote_ip, UINT& remote_port)
{
	int count = SendTo(NAK, strlen(NAK), remote_port, remote_ip);
	status = ((count==strlen(NAK)) ? TRUE : FALSE);
	return status;
}

/*****************************************************************************
*
*  ComChannel::ReceiveAckOrNak(DString &remote_ip, UINT& remote_port, unsigned long max_time)
*
*  This method receives a request for a parcel.
*
*  Parameters:
*     remote_id    reference to a string into which the IP address of the sender
*                  will be written
*     remote_port  reference to an unsigned integer into which the port of sender
*                  will be written
*	  max_time	   Maximum time to wait for a Ack or Nak, specified in milliseconds
*
*	Output:
*		-1		NAK Received
*		0		Something unexcepted or nothing received
*		1		ACK Received
*/
short ComChannel::ReceiveAckOrNak(DString &remote_ip, UINT &remote_port, unsigned long max_time)
{
	BOOL    result = FALSE;
	DString data;
	UINT	max_lng = __max(strlen(ACK), strlen(NAK));
	char	*buffer = new char[max_lng+1];

	DWORD last_err;
    int count = 0;
	int total_count = 0;
	unsigned long wait_time = 0;

	do
	{
		 count = ReceiveFrom(buffer+total_count, max_lng-total_count, remote_ip, remote_port);
		 if (count>0)
		 {
		    total_count += count;
			last_err = 0;
		 }
		 else
		 {
	        last_err = GetLastError();
			Sleep(25);
			wait_time += 25;
		 }
	}
	while (total_count<max_lng && wait_time<max_time && (last_err==WSAEWOULDBLOCK || last_err==0));

	if (total_count == max_lng)
	{
		buffer[total_count]=0;
	    data = buffer;
		if (strcmp(data,ACK)==0)
			result = 1;
		else if (strcmp(data,NAK)==0)
			result = -1;
		else
			result = 0;
	}

	delete buffer;

	return result;
}

#ifdef TESTING
#include "../TestPackage/TestPackage.h"

/*****************************************************************************
*
*   Test cases
*
*/

#include <iostream.h>
#include <assert.h>

// Test 1 - Basic Constructors
void ComChannel::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	DString ip_address;
	UINT ip_port;

	ComChannel c;
	assert(c.getStatus()==TRUE);
	c.GetSockName(ip_address, ip_port);
	assert(ip_address!="");
	assert(ip_port!=0);

    app->DisplayMessage("ComChannel Test 1 complete\r\n");
}

// Test 2 - SendEvent and ReceiveEvent
void ComChannel::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	DString ip_address_1;
	UINT ip_port_1;
	DString ip_address_2;
	UINT ip_port_2;
	DString ip_address_tmp;
	UINT ip_port_tmp;
	BOOL result;

	ComChannel c1(12001);
	assert(c1.getStatus()==TRUE);
	c1.GetSockName(ip_address_1, ip_port_1);
	assert(ip_port_1==12001);

	ComChannel c2(12002);
	assert(c2.getStatus()==TRUE);
	c2.GetSockName(ip_address_2, ip_port_2);
	assert(ip_port_2==12002);

	Event e1;
	Event e2;

	e1.setId(300);
	e1.setEventType('F');
	e1.setName("Doctor Appointment");
	e1.setDescription("Eye examine with Dr. Vistason");
	e1.setNote("Bring checkbook");
	e1.setDateTime(2001,9,24,12,30,0);
	e1.setDuration(60);
	e1.setLocationId(353);
	e1.setStatus("Unscheduled");

	ip_address_1="127.0.0.1";
	ip_address_2="127.0.0.1";
	result=c1.SendEvent(e1, ip_address_2, ip_port_2);
	assert(result==TRUE);
	ip_address_tmp="";
	ip_port_tmp=0;
	result=c2.ReceiveEvent(e2, ip_address_tmp, ip_port_tmp, 3000);
	assert(result==TRUE);
	e2.setId(300);
	e2.setEventType('F');
	e2.setName("Doctor Appointment");
	e2.setDescription("Eye examine with Dr. Vistason");
	e2.setNote("Bring checkbook");
	e2.setDateTime(2001,9,24,12,30,0);
	e2.setDuration(60);
	e2.setLocationId(353);
	e2.setStatus("Unscheduled");

    app->DisplayMessage("ComChannel Test 2 complete\r\n");
}

// Test 3 - SendAck, SendNak, and ReceiveAckOrNak
void ComChannel::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	DString ip_address_1;
	UINT ip_port_1;
	DString ip_address_2;
	UINT ip_port_2;
	DString ip_address_tmp;
	UINT ip_port_tmp;

	BOOL result;
	short acknak;

	ComChannel c1(12001);
	assert(c1.getStatus()==TRUE);
	c1.GetSockName(ip_address_1, ip_port_1);
	assert(ip_port_1==12001);

	ComChannel c2(12002);
	assert(c2.getStatus()==TRUE);
	c2.GetSockName(ip_address_2, ip_port_2);
	assert(ip_port_2==12002);

	ip_address_1="127.0.0.1";
	ip_address_2="127.0.0.1";

	result=c1.SendAck(ip_address_2, ip_port_2);
	assert(result==TRUE);

	ip_address_tmp="";
	ip_port_tmp=0;
	acknak=c2.ReceiveAckOrNak(ip_address_tmp, ip_port_tmp, 3000);
	assert(acknak==1);

	result=c1.SendNak(ip_address_2, ip_port_2);
	assert(result==TRUE);

	ip_address_tmp="";
	ip_port_tmp=0;
	acknak=c2.ReceiveAckOrNak(ip_address_tmp, ip_port_tmp, 3000);
	assert(acknak==-1);

	Event e1;
	result=c1.SendEvent(e1, ip_address_2, ip_port_2);
	assert(result==TRUE);
	
	ip_address_tmp="";
	ip_port_tmp=0;
	acknak=c2.ReceiveAckOrNak(ip_address_tmp, ip_port_tmp, 3000);
	assert(acknak==0);

	app->DisplayMessage("ComChannel Test 3 complete\r\n");
}

#endif