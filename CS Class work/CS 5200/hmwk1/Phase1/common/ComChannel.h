/*****************************************************************************
*
*  File:          ComChannel.h
*  Class:         ComChannel
*  Project:       Distributed Calendering System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*     Sep 5, 2001  Initial version
*
*  Description:
*     A ComChannel object manages a communication channel
*
*/

#pragma once

#include <afxsock.h>
#include "Event.h"

class ComChannel : public CAsyncSocket
{
protected:
	BOOL status;
	int last_error;

public:
	// Constructor
	ComChannel(UINT nSocketPort = 0);

	// Status
	BOOL getStatus(void) { return status; }
	int getLastError(void) { return last_error; }

	// Communication methods common to clients and servers
    BOOL SendEvent(Event& event, DString &remote_ip, UINT remote_port);
    BOOL ReceiveEvent(Event& event, DString &remote_ip, UINT& remote_port, unsigned long max_time);
	BOOL SendAck(DString &remote_ip, UINT& remote_port);
	BOOL SendNak(DString &remote_ip, UINT& remote_port);
    short ReceiveAckOrNak(DString &remote_ip, UINT& remote_port, unsigned long max_time);

#ifdef TESTING
	static void test1(void);
	static void test2(void);
	static void test3(void);
#endif

};
