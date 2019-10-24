/////////////////////////////////////////////////////////////////////////////
//
// NexgenIPL - Next Generation Image Processing Library
// Copyright (C) 1999-2001 Binary Technologies
// All Rights Reserved.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Binary Technologies
// http://www.binary-technologies.de
// info@binary-technologies.de
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BTIPROGRESSNOTIFICATION_INCLUDED
#define BTIPROGRESSNOTIFICATION_INCLUDED

#pragma once

// Defines an interface for progress notifications.
class BTIProgressNotification
{
public:
	virtual void OnProgress(int nPercent) = 0;
};

#endif // BTIPROGRESSNOTIFICATION_INCLUDED