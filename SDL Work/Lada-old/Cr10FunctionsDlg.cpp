// Cr10FunctionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "Cr10FunctionsDlg.h"
#include "LADA Control ModuleDoc.h"

#include "ChangeLocationDlg.h"
#include "Ladastrings.h"
#include "lstring.h"
#include "Flag.h"
#include "InputLocations.h"
#include "ProgressDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int	LastDSP;
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK); // Message Box
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);		// Message Box
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);				// Message Box
#undef MessageBox
#define MessageBox MyMessageBox

extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);			// Returns value with dPlaces numbers as a CString 
extern LString Strings;													// Contains the text Strings in both languages
extern CFont RussianArial;											// The font used
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);	// Sets text to a font
extern void SetItemFont(UINT controlID, CWnd *window);

/////////////////////////////////////////////////////////////////////////////
// CCr10FunctionsDlg dialog


CCr10FunctionsDlg::CCr10FunctionsDlg(CLADAControlModuleDoc *doc, CWnd* pParent /*=NULL*/)
	: CDialog(CCr10FunctionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCr10FunctionsDlg)
	m_CR10Time = _T("");
	m_FIVATime = _T("");
	//}}AFX_DATA_INIT
	pDoc = doc;
}


void CCr10FunctionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCr10FunctionsDlg)
	DDX_Text(pDX, IDC_CR10_TIME, m_CR10Time);
	DDX_Text(pDX, IDC_COMPUTER_TIME, m_FIVATime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCr10FunctionsDlg, CDialog)
	//{{AFX_MSG_MAP(CCr10FunctionsDlg)
	ON_BN_CLICKED(IDC_GET_FINAL_STORAGE, OnGetFinalStorage)
	ON_BN_CLICKED(IDC_SET_FLAGS, OnSetFlags)
	ON_BN_CLICKED(IDC_SETLOCATION, OnSetlocation)
	ON_BN_CLICKED(IDC_UPDATE_TIME, OnUpdateTime)
	ON_BN_CLICKED(IDC_UPLOADPROGRAM, OnUploadprogram)
	ON_BN_CLICKED(IDC_UNLOCK_PASSWORD, OnUnlockPassword)
	ON_BN_CLICKED(IDC_CALIBRATION, OnCalibration)
	ON_BN_CLICKED(IDC_RESET_FINAL_STORAGE, OnResetFinalStorage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCr10FunctionsDlg message handlers

BOOL CCr10FunctionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT4,this);
	SetItemFont(IDC_TEXT7,this);
	SetItemFont(IDC_UPDATE_TIME,this);
	SetItemFont(IDC_UPLOADPROGRAM,this);
	SetItemFont(IDC_SETLOCATION,this);
	SetItemFont(IDC_SET_FLAGS,this);
	SetItemFont(IDC_CR10_TIME,this);
	SetItemFont(IDC_COMPUTER_TIME,this);
	SetItemFont(IDC_GET_FINAL_STORAGE,this);
	SetItemFont(IDC_CALIBRATION,this);
	SetItemFont(IDC_UNLOCK_PASSWORD,this);
	SetItemFont(IDC_RESET_FINAL_STORAGE,this);

	if (pDoc->commObject)
	{
		CTime cTime;
		pDoc->commObject->GetCR10Time(&cTime);
		m_CR10Time = cTime.Format("%H:%M:%S, %B %d, %Y");
		m_FIVATime = CTime::GetCurrentTime().Format("%H:%M:%S, %B %d, %Y");
		GetDlgItem(IDC_UNLOCK_PASSWORD)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_TEXT4)->EnableWindow(FALSE);
		GetDlgItem(IDC_TEXT7)->EnableWindow(FALSE);
		GetDlgItem(IDC_UPDATE_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_UPLOADPROGRAM)->EnableWindow(FALSE);
		GetDlgItem(IDC_SET_FLAGS)->EnableWindow(FALSE);
		GetDlgItem(IDC_SETLOCATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_GET_FINAL_STORAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CALIBRATION)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_RESET_FINAL_STORAGE)->EnableWindow(pDoc->nFSFiles>0);
	SetStrings();
	UpdateData(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCr10FunctionsDlg::SetStrings()
{

	SetWindowText(Strings.get(IDS_BB0));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_BB1));
	GetDlgItem(IDC_TEXT7)->SetWindowText(Strings.get(IDS_BB2));
	GetDlgItem(IDC_UPDATE_TIME)->SetWindowText(Strings.get(IDS_BB3));
	GetDlgItem(IDC_UPLOADPROGRAM)->SetWindowText(Strings.get(IDS_BB4));
	GetDlgItem(IDC_SETLOCATION)->SetWindowText(Strings.get(IDS_BB5));
	GetDlgItem(IDC_GET_FINAL_STORAGE)->SetWindowText(Strings.get(IDS_BB6));
	GetDlgItem(IDC_SET_FLAGS)->SetWindowText(Strings.get(IDS_BB7));
	GetDlgItem(IDC_CALIBRATION)->SetWindowText(Strings.get(IDS_BB8));
	GetDlgItem(IDC_UNLOCK_PASSWORD)->SetWindowText(Strings.get(IDS_BB9));
	GetDlgItem(IDC_RESET_FINAL_STORAGE)->SetWindowText(Strings.get(IDS_BB10));
}

void CCr10FunctionsDlg::OnGetFinalStorage() 
{
	// TODO: Add your control notification handler code here
	pDoc->m_pMainView->GetFinalStorage();	
}

void CCr10FunctionsDlg::OnSetFlags() 
{
	// TODO: Add your control notification handler code here
	CFlag fDialog(pDoc);
	fDialog.DoModal();
}

// Called when the set location button is pressed
// Calls the CChangeLocation Dlg which allows you to get and set input location values
void CCr10FunctionsDlg::OnSetlocation() 
{
	// TODO: Add your control notification handler code here
	if (pDoc->commObject == NULL){
		MessageBox(IDS_M_CANT_CHANGE_LOCATION);
		SetStrings();
		return;
	}
	
	CChangeLocationDlg myDlg( pDoc );
	myDlg.DoModal();
}

// Called when the Update Time button is pressed
// Updates the time
void CCr10FunctionsDlg::OnUpdateTime() 
{
	// TODO: Add your control notification handler code here
	if (pDoc->commObject == NULL){
		MessageBox(IDS_M_CANT_UPDATE_TIME);
		SetStrings();
		return;
	}
	CWaitCursor wCursor;
	UpdateData(TRUE);
	BOOL Success;
	Success = pDoc->commObject->UpdateCR10Time();
	MessageBox((Success?IDS_M_TIME_UPDATED:IDS_M_TIME_NOT_UPDATED),IDS_PROGRAM_NAME);
}

// Called when the Upload Program button is pressed
// Uploads a program to the CR10
void CCr10FunctionsDlg::OnUploadprogram() 
{
	// TODO: Add your control notification handler code here
	if (pDoc->commObject == NULL)
	{
		MessageBox(IDS_M_CANT_UPLOAD_PROGRAM);
		SetStrings();
		return;
	}
	
	BOOL UploadSuccess;
	pDoc->PauseAutomaticCommunication();
	UploadSuccess = pDoc->commObject->UploadProgram();

	if (UploadSuccess)
	{
		//BOOL Canceled = FALSE;
		//ProgressDialog pDlg(&Canceled, "Setting Control Mode", "Initializing CR10 Parameters");	
		//pDlg.Create(PROGRESS_DIALOG);
		CString message;

		pDoc->m_IsCR10Initialized = FALSE;
		BOOL setModeSuccess = pDoc->commObject->SetControlMode( pDoc->m_ControlMode );
		pDoc->m_pMainView->SetControlModeWindow( pDoc->m_ControlMode );
		if (!setModeSuccess)
			message += Strings.get(IDS_M_UNABLE_SET_CONTROL_MODE) + "\n";
		//MessageBox(IDS_M_UNABLE_SET_CONTROL_MODE,IDS_ERROR,MB_ICONWARNING);
		else
			message += "Control Mode Set to Automatic\n";
		//MessageBox("Control Mode Set to Automatic","LADA Software System");
		
		//pDlg.SetInfo(30,"Setting Final Storage and SMP Test frequency and control time");

		
		if (pDoc->PerformInitialization(message))
		{
			message += "Final storage and SMP test frequency set\n";
			pDoc->m_IsCR10Initialized = TRUE;
		}
		else
		{
			message += "Final storage and SMP test frequency not set\n";
		}
		
		//pDlg.SetInfo(60,"Setting growth chamber moisture level and light control times");
		for (int i = 0; i < pDoc->nGrowthChambers; i++)
		{
			if (pDoc->SetControlParameters(i, pDoc->m_ControlParameters[i].m_MoistureLevel, pDoc->m_ControlParameters[i].m_24Hour, pDoc->m_ControlParameters[i].m_LightOnTime, pDoc->m_ControlParameters[i].m_LightOffTime, pDoc->m_ControlParameters[i].m_SMPFreq ))
				message += "Setting parameters for chamber 1 successful\n";
				//MessageBox("");
			else
				message += "Setting parameters for chamber 1 failed\n";
				//MessageBox("");

		}
		MessageBox(message.GetBuffer(0),"Initialization Results");
		// write to history
		//pDlg.Close();
	}

	pDoc->ResumeAutomaticCommunication();
	
}

BOOL CCr10FunctionsDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CCr10FunctionsDlg::OnUnlockPassword() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;
	if (pDoc->commObject == NULL){
				
		pDoc->commObject = new CCommOperations(pDoc, TRUE, TRUE); // ShowMessage = true and WaitExtra = true
		if (pDoc->commObject->IsConnected())
		{
			pDoc->ConnectionStatus = Connected;
			pDoc->m_pMainView->SetCommStatusWindow(pDoc->ConnectionStatus);
		
			if (pDoc->commObject->UnlockPassword())
				MessageBox("The password was cleared.");
			else
				MessageBox("Unable to unlock password.");
		}
		pDoc->StopComm();
		pDoc->m_pMainView->SetCommStatusWindow(pDoc->ConnectionStatus);
	}
	else
		MessageBox(IDS_M_MUST_NOT_CONNECT,IDS_PROGRAM_NAME);
}

void CCr10FunctionsDlg::OnCalibration() 
{
	// TODO: Add your control notification handler code here
	CString dlgString = "Calibration Files (*.txt)|*.txt|All Files (*.*)|*.*|";
	CFileDialog OpenFileDialogBox(TRUE, "txt", NULL, 
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
			dlgString,
			NULL);
		OpenFileDialogBox.m_ofn.lpstrTitle = "Select Calibration File";
	if ( OpenFileDialogBox.DoModal() == IDOK )
	{
		pDoc->commObject->LoadCalibrationFile(OpenFileDialogBox.GetPathName());
	}
}

void CCr10FunctionsDlg::OnResetFinalStorage() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox(IDS_M_SURE_RESET_FS, IDS_PROGRAM_NAME, MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		LastDSP = 1;
		pDoc->SetModifiedFlag();
	}
}
