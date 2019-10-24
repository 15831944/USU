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

// Test 2 - Unused
void ClientComChannel::test2(void)
{
	CTestPackageApp* app = (CTestPackageApp*) AfxGetApp();

    app->DisplayMessage("ClientComChannel Test 2 complete\r\n");
}

// Test case Dispatcher
void ClientComChannel::run_tests(void)
{
	ClientComChannel::test1();
	ClientComChannel::test2();
}

#endif