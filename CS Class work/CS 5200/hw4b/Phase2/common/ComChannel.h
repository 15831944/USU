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

int const DEFAULT_TIMEOUT = 3000;
int const DEFAULT_MAX_RETRIES = 3;

class ComChannel : public CAsyncSocket
{
protected:
	BOOL				status;
	int					last_error;
	static ComChannel*	default_com_channel;

public:
	// Constructor
	ComChannel(UINT nSocketPort = 0);

	// Destructor
	~ComChannel() { if (default_com_channel==this) default_com_channel=NULL; }

	// Status
	BOOL getStatus(void) { return status; }
	int getLastError(void) { return last_error; }

	static void setDefaultComChannel(ComChannel* com) { default_com_channel=com; }
	static ComChannel* getDefaultComChannel(void) { return default_com_channel; }

#ifdef TESTING
	static void test1(void);
	static void test2(void);
	static void run_tests(void);
#endif

};
