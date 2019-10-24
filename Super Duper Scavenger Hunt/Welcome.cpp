// Welcome.cpp : implementation file
//

#include "stdafx.h"
#include "Super Duper Scavenger Hunt.h"
#include "Welcome.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcome dialog

CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4)
{
	CString Time;
	int t;
	int fields = 0;

	if (t = C.GetDays()){
		if (t > 1)
			Time = C.Format("%D days ");
		else
			Time = "1 day ";
		fields++;
	}
	if ((t = C.GetHours()) && fields < DisplayFields){
		if (t > 1)
			Time += C.Format("%H hours ");
		else
			Time += "1 hour ";
		fields++;
	}
	if ((t = C.GetMinutes()) && fields < DisplayFields){
		if (t > 1)
			Time += C.Format("%M minutes ");
		else
			Time += "1 minute ";
		fields++;
	}
	if ((t = C.GetSeconds()) && fields < DisplayFields){
		if (t > 1)
			Time += C.Format("%S seconds");
		else
			Time += "1 second";
		fields++;
	}
	return Time;
}

CWelcome::CWelcome(CWnd* pParent /*=NULL*/)
	: CDialog(CWelcome::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWelcome)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWelcome::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcome)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcome, CDialog)
	//{{AFX_MSG_MAP(CWelcome)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcome message handlers
