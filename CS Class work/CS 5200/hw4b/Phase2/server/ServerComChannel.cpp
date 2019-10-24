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
#include "../common/SockAddr.h"
#include "../common/Message.h"
#include "../server/ServerComChannel.h"

#ifdef TESTING
	#include "../TestPackage/TestPackage.h"
#else
	#ifdef SERVER
		#include "../server/server.h"
	#endif
#endif

//////////////////////////////////////////////////////////////////////////////
//
//	ServerComChannel::OnReceive
//
//	This method responses to OnReceive events.  It reads the incoming datagram
//	unpackages it into a request of some kind.  It then dispatches a new thread
//	to process that request
//
void ServerComChannel::OnReceive( int nErrorCode )
{
	#ifdef TESTING
		CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();
	#else
		#ifdef SERVER
			CServerApp* app = (CServerApp*) AfxGetApp();
		#endif
	#endif

	SocketAddress sender_addr;
	Message* msg = Message::receive(1, sender_addr);

	if (msg)
	{
		app->DisplayMessage("Recieved Message");

		// Add msg to message queue
    }
}

#ifdef TESTING

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

// Test 2 - OnReceive
void ServerComChannel::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

	// TO DO

    app->DisplayMessage("ServerComChannel Test 2 complete\r\n");
}

// Test case Dispatcher
void ServerComChannel::run_tests(void)
{
	ServerComChannel::test1();
	ServerComChannel::test2();
}

#endif