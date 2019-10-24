/*****************************************************************************
*
*  File:          PersisentObject.h
*  Class:         PersisentObject
*  Version:       1.0
*  Project:       Distributed Calendar System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*
*	A persistent object is one that can be saved by server in a
*	make-shift database
*/

#pragma once

#include <afx.h>
#include <iostream.h>
#include "DString.h"

class PersistentObject
{
protected:
	long	id;
	BOOL valid;

public:
	PersistentObject(long init_id = -1) : id(init_id) {}
	PersistentObject(const PersistentObject& orig) : id(orig.id) {}

	virtual ~PersistentObject() {};

	virtual BOOL load(const char* buffer, unsigned short& buffer_lng) = 0;
	virtual BOOL save(char* buffer, unsigned short&  buffer_lng) const = 0;
	virtual unsigned short getPackLng() = 0;

	long getId(void) const { return id; }
	BOOL setId(long i) { id=i; return validate(); }

	virtual BOOL validate() = 0;
	const getValid(void) const { return valid; }
};
