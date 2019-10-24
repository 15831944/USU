// CameraData.h: interface for the CCameraData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERADATA_H__70201D34_DC80_46D7_B000_CEE7203C2743__INCLUDED_)
#define AFX_CAMERADATA_H__70201D34_DC80_46D7_B000_CEE7203C2743__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCameraData  
{
public:
	CTime m_LastAttemptedPictureTime;
	CTime m_NextPictureTime;
	CCameraData & operator=(const CCameraData & right);
	BOOL m_Do;
	void ReadObject(CArchive &ar);
	void WriteObject(CArchive &ar);
	int m_nSuccessful;
	int m_nAttempted;
	CTimeSpan m_PictureFrequency;
	CTime m_LastPictureTaken;
	CCameraData();
	virtual ~CCameraData();

};

#endif // !defined(AFX_CAMERADATA_H__70201D34_DC80_46D7_B000_CEE7203C2743__INCLUDED_)
