/*****************************************************************************
*
*  File:          ServerComChannel.cpp
*  Class:         ServerComChannel
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
#include "../server/ServerComChannel.h"

#ifndef TESTING
#include "../server/server.h"
#include "../common/DialogWithLogging.h"
#endif

/*****************************************************************************
*
*  ServerComChannel::OnReceive
*
*  This method responses to OnReceive events.  For now, only the server responds
*  to receive events.
*
*  There are two versions of this functions.  The first is a version using in
*  testing.  The second is a primitive server.  Eventually, the OnReceive should
*  interact with a server object.
*
*/

void ServerComChannel::OnReceive( int nErrorCode )
{
	if (!request_in_progress)
	{
		request_in_progress=TRUE;
#ifndef TESTING
		CServerApp* app = (CServerApp*) AfxGetApp();

		DString tmp;
		long    id = 0;
		DString client_ip("");
		UINT    client_port=0;

		DString cmd;
		char request_type;

		BOOL status = receiveRequest(cmd, client_ip, client_port);
		if (status)
		{
		  request_type = cmd[0];
		  cmd=cmd.Mid(1);
		  switch (request_type)
		  {
			case 'Q':
			{
				DString tmp;
				int year, month, day, hours, minutes;
				tmp=cmd.Mid(0,4);
				year = (short) tmp;
				tmp=cmd.Mid(4,2);
				month = (short) tmp;
				tmp=cmd.Mid(6,2);
				day = (short) tmp;
				tmp=cmd.Mid(9,2);
				hours = (short) tmp;
				tmp=cmd.Mid(12,2);
				minutes = (short) tmp;
				CTime start_date(year, month, day, hours, minutes, 0);

				tmp=cmd.Mid(14,4);
				year = (short) tmp;
				tmp=cmd.Mid(18,2);
				month = (short) tmp;
				tmp=cmd.Mid(20,2);
				day = (short) tmp;
				tmp=cmd.Mid(23,2);
				hours = (short) tmp;
				tmp=cmd.Mid(26,2);
				minutes = (short) tmp;
				CTime end_date(year, month, day, hours, minutes, 0);

				tmp.Format("Look up events for \r\n",id);
				DialogWithLogging::Log(tmp);
				app->processQuery(client_ip, client_port, start_date, end_date);

				break;
			}
			case 'A':
			{
				tmp.Format("Add an event\r\n",cmd);
				DialogWithLogging::Log(tmp);
				app->processNewEvent(client_ip, client_port);
				break;
			}
			default:
			{
				tmp = "Invalid request received\r\n";
				DialogWithLogging::Log(tmp);
			}
		  }
		}
#endif
		request_in_progress=FALSE;
	}
}

/*****************************************************************************
*
*  ComChannel::receiveRequest(DString& cmd, DString &remote_ip, UINT& remote_port);
*
*  This method receives a request from the client
*
*  Parameters:
*     cmd	       a string containing the request
*     remote_ip    a reference to a string into which ip of the server that
*                  sent the parcel will be written.
*     remote_port  a reference to an integer into which port of the server that
*                  sent the parcel will be written.
*
*  Output:
*     TRUE		   A good parcel was received
*     FALSE		   Communication or data failure.  Call GetLastError() to get an error
*				   code in the case of a communication failure.
*/
BOOL ServerComChannel::receiveRequest(DString &cmd, DString& server_ip, UINT& server_port)
{
	BOOL    result = FALSE;
	DString data;
	char	*buffer = new char[MAX_CMD_LNG];

    int count = ReceiveFrom(buffer, MAX_CMD_LNG, server_ip, server_port);
	if (count>0)
	{
		buffer[count]=0;
	    data = buffer;
		cmd=data;
	    result = TRUE;
	}

	delete buffer;

	return result;
}

/*****************************************************************************
*
*  ComChannel::sendCount(short count, DString &remote_ip, UINT& remote_port);
*
*  This method sends a count to the remote process
*
*  Parameters:
*     count		   the count to send
*     remote_ip    a reference to a string into which ip of the server that
*                  sent the parcel will be written.
*     remote_port  a reference to an integer into which port of the server that
*                  sent the parcel will be written.
*
*  Output:
*     TRUE		   A good parcel was received
*     FALSE		   Communication or data failure.  Call GetLastError() to get an error
*				   code in the case of a communication failure.
*/
BOOL ServerComChannel::sendCount(short count, const DString &remote_ip, UINT remote_port)
{
	DString data;

	data=count;
	data.fillRight(COUNT_LNG,' ');

	size_t tmp= SendTo(data, strlen(data), remote_port, remote_ip);
	status = ((tmp==strlen(data)) ? TRUE : FALSE);

	return status;
}

/*****************************************************************************
*
*  ComChannel::sendId(long id, DString &remote_ip, UINT& remote_port);
*
*  This method sends an id to the remote process
*
*  Parameters:
*     id		   the id to send
*     remote_ip    a reference to a string into which ip of the server that
*                  sent the parcel will be written.
*     remote_port  a reference to an integer into which port of the server that
*                  sent the parcel will be written.
*
*  Output:
*     TRUE		   A good parcel was received
*     FALSE		   Communication or data failure.  Call GetLastError() to get an error
*				   code in the case of a communication failure.
*/
BOOL ServerComChannel::sendId(long id, const DString &remote_ip, UINT remote_port)
{
	DString data;

	data=id;
	data.fillRight(ID_LNG,' ');

	size_t count = SendTo(data, strlen(data), remote_port, remote_ip);
	status = ((count==strlen(data)) ? TRUE : FALSE);

	return status;
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
#include "../client/ClientComChannel.h"

// Test 1 - Basic Constructors
void ServerComChannel::test1(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	DString ip_address;
	UINT ip_port;

	ServerComChannel c;
	assert(c.getStatus()==TRUE);
	c.GetSockName(ip_address, ip_port);
	assert(ip_address!="");
	assert(ip_port!=0);

    app->DisplayMessage("ServerComChannel Test 1 complete\r\n");
}

// Test 2 - ReceiveRequest
void ServerComChannel::test2(void)
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

    app->DisplayMessage("ServerComChannel Test 2 complete\r\n");
}

// Test 3 - SendId, SendCount
void ServerComChannel::test3(void)
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

	app->DisplayMessage("ServerComChannel Test 3 complete\r\n");
}

// Test case Dispatcher
void ServerComChannel::run_tests(void)
{
	ServerComChannel::test1();
	ServerComChannel::test2();
	ServerComChannel::test3();
}

#endif