/*****************************************************************************
*
*  File:          ClientComChannel.cpp
*  Class:         ClientComChannel
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
#include "../common/constants.h"
#include "../client/ClientComChannel.h"

extern void DisplayErrorMessage(DWORD ErrorNum, char *AdditionalMessage = NULL);
/*****************************************************************************
*
*  ClientComChannel::RequestEventList(...)
*
*  This method requests an event list
*
*  Parameters:
*     remote_ip     a reference to a string containing the ip address of the
*					remote process
*     remote_port   a reference to an integer containing the ip port of the
*					remote process
*     start_date	beginning of the selection date range
*     end_date		ending of the selection date range
*	  
*/
BOOL ClientComChannel::requestEventList(CTime& start_date, CTime& end_date, const DString &remote_ip, UINT remote_port)
{
	DString data("Q");

	data += start_date.Format("%Y%m%d %H:%M");
	data += end_date.Format("%Y%m%d %H:%M");

	int count = SendTo(data, strlen(data), remote_port, remote_ip);
	status = ((count==strlen(data)) ? TRUE : FALSE);

	return status;
}

/*****************************************************************************
*
*  ClientComChannel::requestNewEvent(...)
*
*  This method requests a new event
*
*  Parameters:
*     remote_ip     a reference to a string containing the ip address of the
*					remote process
*     remote_port   a reference to an integer containing the ip port of the
*					remote process
*	  
*/
BOOL ClientComChannel::requestNewEvent(const DString &remote_ip, UINT remote_port)
{
	DString data("A");

	int count = SendTo(data, strlen(data), remote_port, remote_ip);
	status = ((count==strlen(data)) ? TRUE : FALSE);
	if (!status)
	{
		DisplayErrorMessage(GetLastError(),"\nrequestNewEvent failed");
	}
	return status;
}

/*****************************************************************************
*
*  ClientComChannelReceiveId(...)
*
*  This method received an Id
*
*  Parameters:
*     remote_ip     a reference to a string containing the ip address of the
*					remote process
*     remote_port   a reference to an integer containing the ip port of the
*					remote process
*	  id			a reference to a long into which the id will be
*					written
*	  max_time		time out in milliseconds
*	  
*/
BOOL ClientComChannel::receiveId(long& id, DString &remote_ip, UINT &remote_port, unsigned long max_time)
{
	BOOL    result = FALSE;
	char	buffer[ID_LNG+1];
	DString	tmp;

	DWORD last_err;
    int count = 0;
	size_t total_count = 0;
	unsigned long wait_time = 0;

	do
	{
		 count = ReceiveFrom(buffer+total_count, ID_LNG-total_count, remote_ip, remote_port);
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
	while (total_count<ID_LNG && wait_time<max_time && (last_err==WSAEWOULDBLOCK || last_err==0));

	if (total_count == ID_LNG)
	{
		buffer[total_count]=0;
	    tmp = buffer;
		id = (long) tmp;
		result = TRUE;
	}

	return result;
}

/*****************************************************************************
*
*  ClientComChannelReceiveCount(...)
*
*  This method received an Id
*
*  Parameters:
*     remote_ip     a reference to a string containing the ip address of the
*					remote process
*     remote_port   a reference to an integer containing the ip port of the
*					remote process
*	  id			a reference to a long into which the count will be
*					written
*	  max_time		time out in milliseconds
*	  
*/
BOOL ClientComChannel::receiveCount(short& count, DString &remote_ip, UINT &remote_port, unsigned long max_time)
{
	BOOL    result = 0;
	char	buffer[COUNT_LNG+1];
	DString	tmp;

	DWORD last_err;
    int tmp_count = 0;
	int total_count = 0;
	unsigned long wait_time = 0;

	do
	{
		 tmp_count = ReceiveFrom(buffer+total_count, COUNT_LNG-total_count, remote_ip, remote_port);
		 if (tmp_count>0)
		 {
		    total_count += tmp_count;
			last_err = 0;
		 }
		 else
		 {
	        last_err = GetLastError();
			Sleep(25);
			wait_time += 25;
		 }
	}
	while (total_count<COUNT_LNG && wait_time<max_time && (last_err==WSAEWOULDBLOCK || last_err==0));

	if (total_count == COUNT_LNG)
	{
		buffer[total_count]=0;
	    tmp = buffer;
		count = (short) tmp;
		result = TRUE;
	}

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
#include "../server/ServerComChannel.h"

// Test 1 - Basic Constructors
void ClientComChannel::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	DString ip_address;
	UINT ip_port;

	ClientComChannel c;
	assert(c.getStatus()==TRUE);
	c.GetSockName(ip_address, ip_port);
	assert(ip_address!="");
	assert(ip_port!=0);

    app->DisplayMessage("ClientComChannel Test 1 complete\r\n");
}

// Test 2 - RequestEventList, RequestNewEvent
void ClientComChannel::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	DString ip_address_1("127.0.0.1");
	UINT ip_port_1=12001;
	DString ip_address_2("127.0.0.1");
	UINT ip_port_2=12002;
	DString ip_address_tmp;
	UINT ip_port_tmp;
	BOOL result;
	DString cmd;

	ClientComChannel c1(ip_port_1);
	assert(c1.getStatus()==TRUE);

	ServerComChannel c2(ip_port_2);
	assert(c2.getStatus()==TRUE);

	result=c1.requestNewEvent(ip_address_2, ip_port_2);
	assert(result==TRUE);
	ip_address_tmp="";
	ip_port_tmp=0;
	result=c2.receiveRequest(cmd, ip_address_tmp, ip_port_tmp);
	assert(result==TRUE);
	assert(cmd=="A");

	CTime s(2001,3,1,10,30,0);
	CTime e(2001,4,12,12,0,0);
	result=c1.requestEventList(s, e, ip_address_2, ip_port_2);
	assert(result==TRUE);
	ip_address_tmp="";
	ip_port_tmp=0;
	result=c2.receiveRequest(cmd, ip_address_tmp, ip_port_tmp);
	assert(result==TRUE);
	assert(cmd=="Q20010301 10:3020010412 12:00");

    app->DisplayMessage("ClientComChannel Test 2 complete\r\n");
}

// Test 3 - receiveId, ReceiveCount
void ClientComChannel::test3(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	DString ip_address_1("127.0.0.1");
	UINT ip_port_1=12001;
	DString ip_address_2("127.0.0.1");
	UINT ip_port_2=12002;
	DString ip_address_tmp;
	UINT ip_port_tmp;
	BOOL result;
	DString cmd;
	long id;
	short count;

	ServerComChannel c1(ip_port_1);
	assert(c1.getStatus()==TRUE);

	ClientComChannel c2(ip_port_2);
	assert(c2.getStatus()==TRUE);

	result=c1.sendId(100,ip_address_2, ip_port_2);
	assert(result==TRUE);
	ip_address_tmp="";
	ip_port_tmp=0;
	result=c2.receiveId(id, ip_address_tmp, ip_port_tmp,3000);
	assert(result==TRUE);
	assert(id=100);

	result=c1.sendCount(40,ip_address_2, ip_port_2);
	assert(result==TRUE);
	ip_address_tmp="";
	ip_port_tmp=0;
	result=c2.receiveCount(count, ip_address_tmp, ip_port_tmp,3000);
	assert(result==TRUE);
	assert(count=100);

	app->DisplayMessage("ClientComChannel Test 3 complete\r\n");
}

#endif