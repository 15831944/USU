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

#ifndef BTCIMAGEOBJECT_INCLUDED
#define BTCIMAGEOBJECT_INCLUDED

#pragma once

#include "BTNexgenIPL.h"

#include "BTDefines.h"
#include "BTCImageData.h"
#include "BTCIOStream.h"
#include "BTICodec.h"
#include "BTIProgressNotification.h"

class BTNEXGENIPL_CLASS_EXPORT BTCImageObject  
{
public:
	BTCImageObject();
	virtual ~BTCImageObject();

	bool AddCodec(long lId, BTICodec* pCodec, const enum BTCodecType& CodecType);
	void RemoveCodec(long lId, const enum BTCodecType& CodecType);

	long GetFileType(BTCIStream* pIStream);
	long GetFileType(unsigned char* pData, long lSize);
	long GetFileType(UINT nResource, HANDLE hModule = NULL, LPCTSTR lpType = RT_BITMAP);
	long GetFileType(LPCTSTR lpszResource, HANDLE hModule = NULL, LPCTSTR lpType = RT_BITMAP);

	BTCImageData& GetObjectData();
	BTCImageData* GetObjectDataPtr();

	bool Attach(BTCImageData& ImageData);

	bool Load(BTCIStream* pIStream, void* pParam = NULL);
	bool Load(unsigned char* pData, long lSize, void* pParam = NULL);
	bool Load(UINT nResource, void* pParam = NULL, HANDLE hModule = NULL, LPCTSTR lpType = RT_BITMAP);
	bool Load(LPCTSTR lpszResource, void* pParam = NULL, HANDLE hModule = NULL, LPCTSTR lpType = RT_BITMAP);
	
	bool Save(BTCOStream* pOStream, long lType = BTFILETYPE_BMP, void* pParam = NULL);
	bool Save(LPCTSTR lpszFileName, long lType = BTFILETYPE_BMP, void* pParam = NULL);

	void SetProgressNotification(BTIProgressNotification* pProgressNotification);

protected:
	void*						m_pCodecMng;

	BTCImageData				m_ImageData;
	BTIProgressNotification*	m_pProgressNotification;
};

#endif // BTCIMAGEOBJECT_INCLUDED
