// ParamMenu.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ParamMenu.h"
#include "LADA Control ModuleDoc.h"
#include "LadaStrings.h"
#include "LString.h"
#include "ManualControl.h"
#include "ParamDlg.h"
#include "DataCollectionSheet.h"
#include "CalibrationDlg.h"

extern LString Strings;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Cr10FunctionsDlg.h"

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK); // Message Box
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);		// Message Box
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);				// Message Box
#undef MessageBox
#define MessageBox MyMessageBox

extern CFont RussianArial;
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);	// Sets text to a font
extern void SetItemFont(UINT controlID, CWnd *window);					// Sets an Item to a font


/////////////////////////////////////////////////////////////////////////////
// CParamMenu dialog


CParamMenu::CParamMenu(CLADAControlModuleDoc *doc, CWnd* pParent /*=NULL*/)
	: CDialog(CParamMenu::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CParamMenu)
	m_DisplayManualDlg = FALSE;
	//}}AFX_DATA_INIT
}


void CParamMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamMenu)
	DDX_Control(pDX, IDC_OPMODE, m_modeWindow);
	DDX_Check(pDX, IDC_DISPLAY_WINDOW, m_DisplayManualDlg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParamMenu, CDialog)
	//{{AFX_MSG_MAP(CParamMenu)
	ON_BN_CLICKED(IDC_DISPLAY_WINDOW, OnDisplayWindow)
	ON_BN_CLICKED(IDC_CR10_FUNCTIONS, OnCr10Functions)
	ON_BN_CLICKED(IDC_DATA_COLLECTION, OnDataCollection)
	ON_BN_CLICKED(IDC_PARAMS, OnParams)
	ON_BN_CLICKED(IDC_CALIBRATION, OnCalibration)
	ON_BN_CLICKED(IDC_SWITCH_MODE, OnSwitchMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamMenu message handlers

void CParamMenu::OnSwitchMode() 
{
		// TODO: Add your control notification handler code here
	UpdateData();
	if (pDoc->commObject)
	{
		if (pDoc->m_ControlMode == ManualControlMode)
			pDoc->m_ControlMode = AutomaticControlMode;
		else
			pDoc->m_ControlMode = ManualControlMode;

		if (pDoc->m_ControlMode == AutomaticControlMode)
		{
			m_DisplayManualDlg = FALSE;
			UpdateData(FALSE);
			if ( pDoc->m_ptrManualDlg != NULL)
			{ // destory dialog
				pDoc->m_ptrManualDlg->OnClose();
			}
		}

		if (SetControlMode())
		{
			SetControlModeWindow(pDoc->m_ControlMode);
			pDoc->m_pMainView->SetControlModeWindow(pDoc->m_ControlMode);
		}
		else
		{	
			if (pDoc->m_ControlMode == ManualControlMode)
				pDoc->m_ControlMode = AutomaticControlMode;
			else
				pDoc->m_ControlMode = ManualControlMode;
			MessageBox(IDS_M_UNABLE_SWITCH_CONTROL_MODE,IDS_ERROR,MB_ICONWARNING);
		}
	}
	else
		MessageBox(IDS_M_CONNECT_BEFORE_SWITCH_MODE,IDS_ERROR,MB_ICONINFORMATION);
	GetDlgItem(IDC_DISPLAY_WINDOW)->EnableWindow(pDoc->m_ControlMode == ManualControlMode && pDoc->commObject);
}

BOOL CParamMenu::SetControlMode()
{
	CWaitCursor wCursor;
	if (pDoc->commObject)
	{
		return pDoc->commObject->SetControlMode(pDoc->m_ControlMode);
	}
	else
		MessageBox("SetControlMode() should not be called unless commObject != NULL","Error");
	return FALSE;
}

void CParamMenu::SetControlModeWindow(ControlModeType mode)
{
	switch (mode)
	{
	case ManualControlMode:
		{
			m_modeWindow.SetBitmap((HBITMAP)pDoc->ManualBMP->m_hObject);
			GetDlgItem(IDC_MODE_TEXT)->SetWindowText(Strings.get(IDS_MANUAL));
		} break;
	case AutomaticControlMode:
		{
			m_modeWindow.SetBitmap((HBITMAP)pDoc->AutomaticBMP->m_hObject);
			GetDlgItem(IDC_MODE_TEXT)->SetWindowText(Strings.get(IDS_AUTOMATIC));
		} break;
	}
}

void CParamMenu::OnDisplayWindow() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_DisplayManualDlg && pDoc->m_ptrManualDlg == NULL && pDoc->m_ControlMode != AutomaticControlMode)
	{ // display dialog
		pDoc->m_ptrManualDlg = new CManualControl(pDoc);
		pDoc->m_ptrManualDlg->Create(IDD_MANUAL_CONTROL);
	}
	else if (!m_DisplayManualDlg && pDoc->m_ptrManualDlg != NULL)
	{ // destory dialog
		pDoc->m_ptrManualDlg->OnClose();
	}
}

void CParamMenu::OnDataCollection() 
{
	// TODO: Add your control notification handler code here
	/*
	if (pDoc->InCommMode == FALSE || pDoc->ConnectionStatus == NotConnected)
	{
		MessageBox(IDS_M_MUST_CONNECT,IDS_PROGRAM_NAME);
		return;
	}
	*/
	CDataCollectionSheet mySheet(pDoc);
	mySheet.DoModal();
	//CDataCollectionStatusDlg dDlg(pDoc);
	//dDlg.DoModal();
	SetStrings();
}

void CParamMenu::OnCr10Functions() 
{
	// TODO: Add your control notification handler code here
	CCr10FunctionsDlg cDlg(pDoc);
	cDlg.DoModal();
	SetStrings();
}

void CParamMenu::SetStrings()
{
	
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_EXIT));
	GetDlgItem(IDC_DATA_COLLECTION)->SetWindowText(Strings.get(IDS_J10));
	GetDlgItem(IDC_CR10_FUNCTIONS)->SetWindowText(Strings.get(IDS_J11));
	GetDlgItem(IDC_PARAMS)->SetWindowText(Strings.get(IDS_J17));
	GetDlgItem(IDC_CALIBRATION)->SetWindowText(Strings.get(IDS_J18));
	SetWindowText(Strings.get(IDS_J0));
	if (pDoc->m_ControlMode == AutomaticControlMode)
		GetDlgItem(IDC_MODE_TEXT)->SetWindowText(Strings.get(IDS_AUTOMATIC));
	else
		GetDlgItem(IDC_MODE_TEXT)->SetWindowText(Strings.get(IDS_MANUAL));
	GetDlgItem(IDC_CONTROL_MODE)->SetWindowText(Strings.get(IDS_D15));
	GetDlgItem(IDC_DISPLAY_WINDOW)->SetWindowText(Strings.get(IDS_J13));
	GetDlgItem(IDC_SWITCH_MODE)->SetWindowText(Strings.get(IDS_D16));


}

void CParamMenu::MakeCR10Inactive()
{
		GetDlgItem(IDC_CONTROL_MODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MODE_TEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISPLAY_WINDOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_SWITCH_MODE)->EnableWindow(FALSE);
}

BOOL CParamMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetItemFont(IDC_PARAMS, this);
	SetItemFont(IDC_CALIBRATION, this);
	SetItemFont(IDOK,this);
	SetItemFont(IDC_DATA_COLLECTION,this);
	SetItemFont(IDC_CR10_FUNCTIONS,this);
	//IDC_INITIALIZATION
	SetItemFont(IDC_CONTROL_MODE,this);
	SetItemFont(IDC_MODE_TEXT,this);
	SetItemFont(IDC_DISPLAY_WINDOW,this);
	SetItemFont(IDC_SWITCH_MODE,this);

	GetDlgItem(IDC_DISPLAY_WINDOW)->EnableWindow(pDoc->m_ControlMode == ManualControlMode && pDoc->commObject);

	if (pDoc->commObject && pDoc->m_ControlState == Regular)
	{
		
	}
	else
	{
		MakeCR10Inactive();	
	}

	GetDlgItem(IDC_DATA_COLLECTION)->EnableWindow(pDoc->m_ControlState == Regular);
	
	if (pDoc->m_ptrManualDlg)
		m_DisplayManualDlg = TRUE;
	else
		m_DisplayManualDlg = FALSE;
	
	SetControlModeWindow(pDoc->m_ControlMode);
	SetStrings();
	
	//if (IsInitialization)
	//{
	//	GetDlgItem(IDC_INITIALIZATION)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_CR10_FUNCTIONS)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_DATA_COLLECTION)->EnableWindow(FALSE);
	//}

	return TRUE;  // return TRUE  unless you set the focus to a control
}


BOOL CParamMenu::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}





void CParamMenu::OnParams() 
{
	// TODO: Add your control notification handler code here
		CParamDlg cDlg(pDoc);
		cDlg.DoModal();
}

void CParamMenu::OnCalibration() 
{
	// TODO: Add your control notification handler code here
	CCalibrationDlg cDlg(pDoc);
	cDlg.DoModal();

}


