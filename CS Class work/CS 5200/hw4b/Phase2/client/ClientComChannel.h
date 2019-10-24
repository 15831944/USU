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

#ifdef TESTING
	static void test1(void);
	static void test2(void);
	static void run_tests(void);
#endif
};
