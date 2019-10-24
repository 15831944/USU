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

#ifndef BTCIOSTREAM_INCLUDED
#define BTCIOSTREAM_INCLUDED

#pragma once

class BTCIOStream
{
public:
	enum Position	{	Begin    = 1,
						Current  = 2,
						End      = 3 };

	/////////////////////////////////////////////////////////////////////////////
	// Seek returns the offset, in bytes, of the new position from the
	// beginning of the stream.
	// A return value of -1 indicates an error.
	/////////////////////////////////////////////////////////////////////////////

	virtual long Seek(long lOffset, unsigned int nOrigin) = 0;

	/////////////////////////////////////////////////////////////////////////////
	// Check the stream if it is open.
	/////////////////////////////////////////////////////////////////////////////

	virtual bool IsOpen() = 0;

	/////////////////////////////////////////////////////////////////////////////
	// Close the stream.
	/////////////////////////////////////////////////////////////////////////////

	virtual void Close() = 0;
};

class BTCOStream : public BTCIOStream
{
public:

	/////////////////////////////////////////////////////////////////////////////
	// If successful, Write returns the number of bytes actually written.
	// A return value of -1 indicates an error. Also a return value less than
	// count indicates an error.
	/////////////////////////////////////////////////////////////////////////////

	virtual long Write(const void* pData, long lCount) = 0;
};

class BTCIStream : public BTCIOStream
{
public:

	/////////////////////////////////////////////////////////////////////////////
	// Read returns the number of bytes read, which may be less than count if
	// there are fewer than count bytes left in the stream.
	// A return value of -1 indicates an error.
	/////////////////////////////////////////////////////////////////////////////

	virtual long Read(void* pData, long lCount) = 0;

	/////////////////////////////////////////////////////////////////////////////
	// Retrieves the current stream pointer.
	/////////////////////////////////////////////////////////////////////////////

	virtual long GetPosition() = 0;

	/////////////////////////////////////////////////////////////////////////////
	// Retrieves the current size of the stream.
	/////////////////////////////////////////////////////////////////////////////

	virtual long GetSize() = 0;
};

#endif // BTCIOSTREAM_INCLUDED