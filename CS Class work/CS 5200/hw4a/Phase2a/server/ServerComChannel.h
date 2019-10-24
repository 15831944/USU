/*****************************************************************************
*
*  File:          ServerComChannel.h
*  Class:         ServerComChannel
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*     Sep. 5, 2001  Initial version
*
*  Description:
*
*/

#pragma once

#include "../common/ComChannel.h"
#include "../common/event.h"

class ServerComChannel : public ComChannel
{
protected:
	BOOL request_in_progress;

public:
	// Constructor
	ServerComChannel(UINT nSocketPort=12000) :
	   ComChannel(nSocketPort), request_in_progress(FALSE) {}

	// Event handlers
	virtual void OnReceive(int nErrorCode);

	// Methods for communicating with the client
    BOOL receiveRequest(DString& cmd, DString &remote_ip, UINT& remote_port);

	// Methods for communicating with the client
	BOOL sendCount(short count, const DString &server_ip, UINT server_port);
	BOOL sendId(long id, const DString &server_ip, UINT server_port);

#ifdef TESTING
	void setInProgress(void) { request_in_progress=TRUE; }
	static void test1(void);
	static void test2(void);
	static void test3(void);
	static void run_tests(void);
#endif
};
