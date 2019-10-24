// This is Version 1.0 PLEASE DOCUMENT CHANGES
// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ProgressDialog.h"
#include "LadaStrings.h"
#include "LString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFont RussianArial;
extern LString Strings;
/////////////////////////////////////////////////////////////////////////////
// ProgressDialog dialog


ProgressDialog::ProgressDialog(BOOL *Canceled, const char *iText, 
	const char *TitleBar, const char *CancelText, BOOL SPercent, 
	CWnd* pParent /*=NULL*/, BOOL DParent /*=TRUE*/)
	: CDialog(ProgressDialog::IDD, pParent)
{
	CancelPressed = Canceled;
	
	if (iText)
		strcpy(InitText, iText);
	else
		InitText[0] = NULL;

	if (TitleBar)
		strcpy(TitleBarText, TitleBar);
	else
		TitleBarText[0] = NULL;

	if (CancelText != NULL)
		strcpy(CancelButtonText, CancelText);
	else 
		strcpy(CancelButtonText, Strings.get(IDS_CANCEL));

	ShowPercent = SPercent;

	*CancelPressed = FALSE;
	
	if ((DisableParent = DParent) && (pParentWnd = pParent) )
		pParent->EnableWindow(FALSE);
	//{{AFX_DATA_INIT(ProgressDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL ProgressDialog::OnInitDialog()
{   
	CDialog::OnInitDialog();      // TODO: Add extra initialization here
	
	GetDlgItem(IDC_WINDOW_TEXT)->SetFont(&RussianArial);
	GetDlgItem(IDCANCEL)->SetFont(&RussianArial);
	SetFont(&RussianArial);

	SetWindowText(TitleBarText);
	SetInfo(0,InitText);

	if (CancelButtonText)
		GetDlgItem(IDCANCEL)->SetWindowText(CancelButtonText);
	
	if (!ShowPercent)
	{
		CStatic *percentWindow = (CStatic *) GetDlgItem(IDC_PERCENT);
		percentWindow->ShowWindow(SW_HIDE);
	}
	SetWindowPos(&wndTopMost, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW );

	return TRUE;   // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE}
}

void ProgressDialog::SetInfo(int percentCompletion, char *newText){
	
	CProgressCtrl *progBox = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	progBox->SetPos( percentCompletion );
	if (ShowPercent){
		CStatic *percentWindow = (CStatic *) GetDlgItem(IDC_PERCENT);
		char percentCStr[6];
		wsprintf(percentCStr,"%i%%",percentCompletion);
		percentWindow->SetWindowText(percentCStr);
	}

	if (newText){
		CStatic *nText = (CStatic *) GetDlgItem(IDC_WINDOW_TEXT);
		nText->SetWindowText(newText);
	}
}

void ProgressDialog::Close() 
{
	if (DisableParent && pParentWnd)
		pParentWnd->EnableWindow(TRUE);
	DestroyWindow();
}

void ProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProgressDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProgressDialog, CDialog)
	//{{AFX_MSG_MAP(ProgressDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgressDialog message handlers

void ProgressDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	*CancelPressed = TRUE;
	Close();
}

