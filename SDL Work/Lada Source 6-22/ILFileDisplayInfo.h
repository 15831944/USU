// This is Version 1.0 PLEASE DOCUMENT CHANGES
// ILFileDisplayInfo.h: interface for the CILFileDisplayInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILFILEDISPLAYINFO_H__3FAB8562_A527_11D4_B01E_B252FB4E252A__INCLUDED_)
#define AFX_ILFILEDISPLAYINFO_H__3FAB8562_A527_11D4_B01E_B252FB4E252A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CILFileDisplayInfo  
{
public:
	int m_curILCreateFreq;
	int m_curDataSaveSel;
	int m_curDataRetrievalSel;
	CILFileDisplayInfo();
	virtual ~CILFileDisplayInfo();

};

#endif // !defined(AFX_ILFILEDISPLAYINFO_H__3FAB8562_A527_11D4_B01E_B252FB4E252A__INCLUDED_)
