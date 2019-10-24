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

ComChannel* ComChannel::default_com_channel = NULL;

/*****************************************************************************
*
*  ComChannel Constructor
*
*  This builds and setups up a communication channel for both clients and
*  servers.  If default_com_channel is NULL, then this newly created
*  ComChannel becomes the default communication channel.
*
*  Parameters:
*     nSocketPort    The socket port number
*/
ComChannel::ComChannel(UINT nSocketPort)
{
	status = Create(nSocketPort,SOCK_DGRAM);
	if (status==FALSE)
		last_error = GetLastError();
	else
	{
		last_error = 0;
		if (!default_com_channel) default_com_channel=this;
	}
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

// Test 1 - Basic Constructors and the setting of the default communication
// channel
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

	assert(default_com_channel==&c);
	assert(getDefaultComChannel()==&c);

	ComChannel* c2 = new ComChannel();
	assert(default_com_channel==&c);
	assert(getDefaultComChannel()==&c);

	setDefaultComChannel(c2);
	assert(default_com_channel==c2);
	assert(getDefaultComChannel()==c2);

	delete c2;
	assert(default_com_channel==NULL);
	assert(getDefaultComChannel()==NULL);

    app->DisplayMessage("ComChannel Test 1 complete\r\n");
}

// Test 2 - SendTo and ReceiveFrom
void ComChannel::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	CString ip_address_1;
	UINT ip_port_1;
	CString ip_address_2;
	UINT ip_port_2;
	CString ip_address_tmp;
	UINT ip_port_tmp;
	char response[256];
	int lng;
	int result;

	ComChannel c1(12001);
	assert(c1.getStatus()==TRUE);
	c1.GetSockName(ip_address_1, ip_port_1);
	assert(ip_port_1==12001);

	ComChannel c2(12002);
	assert(c2.getStatus()==TRUE);
	c2.GetSockName(ip_address_2, ip_port_2);
	assert(ip_port_2==12002);

	result=c1.SendTo("Hello",5,12002,"127.0.0.1");
	assert(result==5);

	lng=255;
	result=c2.ReceiveFrom(response,lng,ip_address_tmp,ip_port_tmp);
	assert(result==5);
	response[5]=0;
	assert(strcmp(response,"Hello")==0);

    app->DisplayMessage("ComChannel Test 2 complete\r\n");
}

// Test case Dispatcher
void ComChannel::run_tests(void)
{
	ComChannel::test1();
	ComChannel::test2();
}

#endif