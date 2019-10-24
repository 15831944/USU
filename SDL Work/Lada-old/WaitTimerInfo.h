// This is Version 1.0 PLEASE DOCUMENT CHANGES
// WaitTimerInfo.h: interface for the CWaitTimerInfo struct.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAITTIMERINFO_H__D2FCCEF3_8A4A_11D4_98E3_00A076801ACD__INCLUDED_)
#define AFX_WAITTIMERINFO_H__D2FCCEF3_8A4A_11D4_98E3_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LADA Control ModuleDoc.h"
#include "LADA Control ModuleView.h"
#include "CommOperations.h"

//class CCommOperations;
//class CLADAControlModuleDoc;
//class CLADAControlModuleView;


struct CWaitTimerInfo 
{
	CCommOperations *commObject;	
	CLADAControlModuleDoc *pDoc;
	CLADAControlModuleView *pView;
	BOOL *InCommMode;
};
#endif // !defined(AFX_WAITTIMERINFO_H__D2FCCEF3_8A4A_11D4_98E3_00A076801ACD__INCLUDED_)
