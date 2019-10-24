/*****************************************************************************
*
*  File:          ClientComChannel.h
*  Class:         ClientComChannel
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*     Sep. 5, 2001  Initial version
*
*  Description:
*     A ClientComChannel handles all of the communication with
*	  a server on behave of a client.
*
*/

#pragma once

#include "../common/ComChannel.h"

class ClientComChannel : public ComChannel
{
public:
	// Constructor
	ClientComChannel(UINT nSocketPort=0) :
	  ComChannel(nSocketPort) {}

	// Methods for communicating with the server
	BOOL requestEventList(CTime& start_date, CTime& end_date, const DString &server_ip, UINT server_port);
    BOOL requestNewEvent(const DString &server_ip, UINT server_port);
	BOOL receiveId(long& id, DString &server_ip, UINT &server_port, unsigned long max_time);
	BOOL receiveCount(short& count, DString &server_ip, UINT &server_port, unsigned long max_time);

#ifdef TESTING
	static void test1(void);
	static void test2(void);
	static void test3(void);
#endif
};
