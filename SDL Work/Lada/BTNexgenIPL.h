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

#ifndef BTNEXGENIPL_INCLUDED
#define BTNEXGENIPL_INCLUDED

#pragma once

/////////////////////////////////////////////////////////////////////////////
// The following will ensure that we are exporting C++ classes when 
// building the DLL and importing the classes when build an application 
// using this DLL.
/////////////////////////////////////////////////////////////////////////////

#ifdef _BTNEXGENIPL
	#define BTNEXGENIPL_CLASS_EXPORT	__declspec(dllexport)
#else
	#define BTNEXGENIPL_CLASS_EXPORT	__declspec(dllimport)
#endif

/////////////////////////////////////////////////////////////////////////////
// The following will ensure that when building an application (or another
// DLL) using this DLL, the appropriate .LIB file will automatically be used
// when linking.
/////////////////////////////////////////////////////////////////////////////

#ifndef _BTNEXGENIPL_NOAUTOLIB
	#define _BTNEXGENIPL_LIBPATH "BTNexgenIPL32.lib"
	#define _BTNEXGENIPL_MESSAGE "Automatically linking with " _BTNEXGENIPL_LIBPATH

	#pragma comment(lib, _BTNEXGENIPL_LIBPATH)
	#pragma message(_BTNEXGENIPL_MESSAGE)
#endif

#endif // BTNEXGENIPL_INCLUDED