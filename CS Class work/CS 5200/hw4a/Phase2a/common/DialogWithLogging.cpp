/*****************************************************************************
*
*  File:          DialogWithLogging.cpp
*  Class:         DialogWithLogging
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
#include "DialogWithLogging.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DialogWithLogging* DialogWithLogging::current_log_window;


