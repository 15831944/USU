// CameraData.cpp: implementation of the CCameraData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "CameraData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCameraData & CCameraData::operator=(const CCameraData & right)
{
	m_nAttempted = right.m_nAttempted;
	m_nSuccessful = right.m_nSuccessful;
	m_LastPictureTaken = right.m_LastPictureTaken;
	m_PictureFrequency = right.m_PictureFrequency;
	m_Do = right.m_Do;
	return *this;
}

CCameraData::CCameraData()
{
	m_nAttempted = 0;
	m_nSuccessful = 0;
	m_LastPictureTaken = time_t(0);
	m_LastAttemptedPictureTime = time_t(0);
	m_NextPictureTime  = time_t(0);
	m_PictureFrequency = CTimeSpan(0,1,0,0);
	m_Do = FALSE;
}

CCameraData::~CCameraData()
{
	
}

void CCameraData::ReadObject(CArchive &ar)
{
	ar.Read(&m_nAttempted, sizeof(int));
	ar.Read(&m_nSuccessful, sizeof(int));
	ar.Read(&m_PictureFrequency, sizeof(CTimeSpan));
	ar.Read(&m_LastPictureTaken, sizeof(CTime));
	ar.Read(&m_LastAttemptedPictureTime, sizeof(CTime));
	ar.Read(&m_Do, sizeof(BOOL));
	
}

void CCameraData::WriteObject(CArchive &ar)
{
	ar.Write(&m_nAttempted, sizeof(int));
	ar.Write(&m_nSuccessful, sizeof(int));
	ar.Write(&m_PictureFrequency, sizeof(CTimeSpan));
	ar.Write(&m_LastPictureTaken, sizeof(CTime));
	ar.Write(&m_LastAttemptedPictureTime, sizeof(CTime));
	ar.Write(&m_Do, sizeof(BOOL));
}