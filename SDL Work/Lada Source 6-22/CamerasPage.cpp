// CamerasPage.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CamerasPage.h"
#include "Lada Control ModuleDoc.h"
#include "LString.h"
#include "LadaStrings.h"
#include "CameraData.h"
#include "SetFrequencyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

extern double StringToValue(const char * ptrString);
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern CFont RussianArial;
extern LString Strings;
extern CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4);
extern int curLanguage;
extern CString IntToString(int number);

/////////////////////////////////////////////////////////////////////////////
// CCamerasPage property page

IMPLEMENT_DYNCREATE(CCamerasPage, CPropertyPage)

CCamerasPage::CCamerasPage() : CPropertyPage(CCamerasPage::IDD)
{
	//{{AFX_DATA_INIT(CCamerasPage)
	m_cFreq = _T("");
	m_IsCameraEnabled = FALSE;//pDoc->m_CamerasEnabled;
	m_wChamber = -1;
	m_nCameras = 0;
	m_cameraFrequency = _T("");
	//}}AFX_DATA_INIT
	IsModified = FALSE;
}

CCamerasPage::~CCamerasPage()
{
}

void CCamerasPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamerasPage)
	DDX_Control(pDX, IDC_W_CHAMBER, m_cChamber);
	DDX_Check(pDX, IDC_ENABLE_CAMERA, m_IsCameraEnabled);
	DDX_CBIndex(pDX, IDC_W_CHAMBER, m_wChamber);
	DDX_Text(pDX, IDC_N_CAMERAS, m_nCameras);
	DDX_Text(pDX, IDC_C_FREQUENCY, m_cameraFrequency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamerasPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCamerasPage)
	ON_CBN_SELCHANGE(IDC_W_CHAMBER, OnSelchangeWChamber)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ENABLE_CAMERA, OnEnableCamera)
	ON_EN_CHANGE(IDC_N_CAMERAS, OnChangeNCameras)
	ON_BN_CLICKED(IDC_CHANGE_FREQ, OnChangeFreq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamerasPage message handlers



void CCamerasPage::SetStrings(BOOL updateData)
{
	//if (updateData)
	//	UpdateData(TRUE);

	SetWindowText(Strings.get(IDS_AA26));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_AA28));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_C16));
	GetDlgItem(IDC_TEXT9)->SetWindowText(Strings.get(IDS_AA9));
	GetDlgItem(IDC_TEXT11)->SetWindowText(Strings.get(IDS_AA11));
	GetDlgItem(IDC_ENABLE_CAMERA)->SetWindowText(Strings.get(IDS_AA25) + IntToString(m_wChamber + 1));
		
	UpdateData(FALSE);

	//SetLocationsData();

}



void CCamerasPage::OnSelchangeWChamber() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	
	// show information about cameras...
	
	EnableCameras(m_wChamber < pDoc->nCameras);
	if (m_wChamber < pDoc->nCameras)
	{
		SetCameraData(FALSE);  // FALSE since data is updated a few lines previous
		SetTimeSensitiveCameraData();
	}
	UpdateData(FALSE);
}

void CCamerasPage::EnableCameras(BOOL enable)
{
	// THIS IS ALSO CALLED EVERY TIME THE CURRENT CHAMBER IS CHANGED
	if (enable)
	{
		m_IsCameraEnabled = pDoc->m_CameraData[m_wChamber].m_Do;
		GetDlgItem(IDC_ENABLE_CAMERA)->SetWindowText(Strings.get(IDS_AA25) + IntToString(m_wChamber + 1));
	}
	GetDlgItem(IDC_ENABLE_CAMERA)->EnableWindow(enable);
	
	GetDlgItem(IDC_TEXT9)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT10)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT11)->EnableWindow(enable);
	GetDlgItem(IDC_C_LAST)->EnableWindow(enable);
	GetDlgItem(IDC_C_NEXT)->EnableWindow(enable);
	GetDlgItem(IDC_C_FREQUENCY)->EnableWindow(enable);
}

void CCamerasPage::OnTimer(UINT nIDEvent) 
{
	SetTimeSensitiveCameraData();
}


BOOL CCamerasPage::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{ 
		Strings.ToggleLanguage();
		SetStrings();
		return TRUE;
	}
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==13)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CCamerasPage::SetTimeSensitiveCameraData()
{
	
	if (m_wChamber < pDoc->nCameras && m_wChamber >= 0)
	{
		CTime currTime = CTime::GetCurrentTime();
		CString s;
		//if (pDoc->m_CameraData[m_wChamber].m_nSuccessful)
		//	GetDlgItem
		if ( (pDoc->m_CameraData[m_wChamber].m_LastPictureTaken != 0) && pDoc->m_CameraData[m_wChamber].m_nSuccessful)
			GetDlgItem(IDC_C_LAST)->SetWindowText(pDoc->m_CameraData[m_wChamber].m_LastPictureTaken.Format("%m/%d/%y %H:%M"));
		if ( pDoc->m_CameraData[m_wChamber].m_Do )
		{
			//s = (pDoc->m_CameraData[m_wChamber].m_LastPictureTaken + pDoc->m_CameraData[m_wChamber].m_PictureFrequency).Format("%m/%d/%y %H:%M");
			s = pDoc->m_CameraData[m_wChamber].m_NextPictureTime.Format("%m/%d/%y %H:%M");
			GetDlgItem(IDC_C_NEXT)->SetWindowText(s);
		}
		m_cFreq = ValueToString(pDoc->m_CameraData[m_wChamber].m_PictureFrequency.GetTotalMinutes() / 60.0);
	}
}

void CCamerasPage::ApplyCameraChanges(int wChamber)
{
	// reset the camera timer
	pDoc->m_pMainView->SetCameraTimer(wChamber);	
}

void CCamerasPage::OnEnableCamera() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (pDoc->m_CameraData[m_wChamber].m_Do != m_IsCameraEnabled)
	{
		pDoc->SetModifiedFlag();
		if (m_IsCameraEnabled)
		{
			if (!pDoc->m_AreCamerasLoaded) // we have just turned the first camera on
			{
				if (MessageBox(IDS_M_LOAD_CAMERA_DRIVER_NOW,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
				{
					pDoc->LoadCameras();
					if (pDoc->m_LastCameraLoadFailed)
					{
						MessageBox(IDS_M_FAILED_LOAD_CAMERA,IDS_PROGRAM_NAME,MB_ICONWARNING);
						pDoc->UnloadCameras();
						m_IsCameraEnabled = FALSE;
						UpdateData(FALSE);
						return;
					}
					else
						MessageBox(IDS_M_SUCCEEDED_LOAD_CAMERA,IDS_PROGRAM_NAME,MB_ICONINFORMATION);
				}
				else
				{
					m_IsCameraEnabled = FALSE;
					UpdateData(FALSE);
					return;
				}
			}
			pDoc->m_CamerasEnabled++;
		}
		else
		{
			if (pDoc->m_CamerasEnabled == 1 && pDoc->m_AreCamerasLoaded) // we have just turned the last camera off
			{
				if (MessageBox(IDS_M_UNLOAD_CAMERA_DRIVER_NOW,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
					pDoc->UnloadCameras();
				else
				{
					m_IsCameraEnabled = TRUE;
					UpdateData(FALSE);
					return;
				}
				
			}
			pDoc->m_CamerasEnabled--;
#ifdef _DEBUG			
			if (pDoc->m_CamerasEnabled < 0)
				MessageBox("m_CamerasEnabled should not be less than 0","Program Error");
#endif

		}
		SetModified(TRUE);
		pDoc->SetModifiedFlag(TRUE);
		pDoc->m_CameraData[m_wChamber].m_Do = m_IsCameraEnabled;
		ApplyCameraChanges(m_wChamber);
	}
}


BOOL CCamerasPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	//cameras
	GetDlgItem(IDC_TEXT1)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT2)->SetFont(&RussianArial);
	GetDlgItem(IDC_N_CAMERAS)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT9)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT11)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT10)->SetFont(&RussianArial);
	GetDlgItem(IDC_W_CHAMBER)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_LAST)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_NEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_FREQUENCY)->SetFont(&RussianArial);
	GetDlgItem(IDC_ENABLE_CAMERA)->SetFont(&RussianArial);
	// start initializing chamber stuff
	m_nCameras = pDoc->nCameras;
	for (int i = 0; i < m_nCameras; i++)
		m_cChamber.AddString(IntToString(i+1));
	m_wChamber = 0;
	m_IsCameraEnabled = pDoc->m_CamerasEnabled;
	UpdateData(FALSE);
	
	
	GetDlgItem(IDC_W_CHAMBER)->EnableWindow(m_nCameras);
	GetDlgItem(IDC_TEXT1)->EnableWindow(m_nCameras);
	GetDlgItem(IDC_CHANGE_FREQ)->EnableWindow(m_nCameras); 
	// start initializing camera info
	EnableCameras(m_wChamber < pDoc->nCameras);
	if (m_wChamber < pDoc->nCameras)
	{
		SetCameraData(FALSE);
		SetTimeSensitiveCameraData();
	}
	SetModified(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CCamerasPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(1);
	
	return CPropertyPage::OnKillActive();
}

BOOL CCamerasPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetStrings(FALSE);

	if (pDoc->nFSFiles || pDoc->nILFiles || pDoc->nCameras)
		SetTimer(1,1000,NULL);
	return CPropertyPage::OnSetActive();
}

void CCamerasPage::SetDocument(CLADAControlModuleDoc * doc)
{
	pDoc = doc;
}

void CCamerasPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	//char buf[100]; wsprintf(buf,"Cameras - OnOK called.\nIsModified = %i",IsModified);
	//MessageBox(buf);
	CPropertyPage::OnOK();
	SetModified(FALSE);
}

void CCamerasPage::SetModified(BOOL Modified)
{
	IsModified = Modified;
	CPropertyPage::SetModified(Modified);
}

void CCamerasPage::SetCameraData(BOOL Update)
{
	CString s;
	if (m_wChamber < pDoc->nCameras && m_wChamber >= 0)
	{
		if (Update)
			UpdateData(TRUE);
		m_IsCameraEnabled = pDoc->m_CameraData[m_wChamber].m_Do;
		m_cameraFrequency = GetTimeSpan( pDoc->m_CameraData[m_wChamber].m_PictureFrequency );

		UpdateData(FALSE);
	}
}

void CCamerasPage::OnChangeNCameras() 
{
	if (GetDlgItem(IDC_N_CAMERAS)->GetWindowTextLength() > 0)
	{
		UpdateData();
		if (m_nCameras > 2)
		{
			MessageBox(IDS_M_CAMERAS_NOT_EXCEED_TWO,IDS_PROGRAM_NAME);
			m_nCameras = 2;
		}
		if (m_nCameras < 0)
		{
			MessageBox(IDS_M_CAMERAS_POSITIVE,IDS_PROGRAM_NAME);
			m_nCameras = 0;
		}
		if (m_wChamber >= m_nCameras)
			m_wChamber = m_nCameras - 1;
		if (m_wChamber < 0 && m_nCameras > 0)
			m_wChamber = 0;
		
		if (m_nCameras != pDoc->nCameras)
		{
			pDoc->m_CamerasEnabled = 0;
			CCameraData * ptrOldData = pDoc->m_CameraData;
			if (m_nCameras)
				pDoc->m_CameraData = new CCameraData[m_nCameras];
			for (int i = 0; i < pDoc->nCameras && i < m_nCameras; i++)
			{
				pDoc->m_CameraData[i] = ptrOldData[i];
				if (pDoc->m_CameraData[i].m_Do)
					pDoc->m_CamerasEnabled++;
			}
			delete [] ptrOldData;
			if (m_nCameras == 0)
				pDoc->m_CameraData = NULL;
			
			pDoc->nCameras = m_nCameras;
			m_cChamber.ResetContent();
			for (i = 0; i < m_nCameras; i++)
				m_cChamber.AddString(IntToString(i+1));

			// by decreasing the number of cameras to zero we should
			// unload the camera driver, if loaded
			if (pDoc->m_CamerasEnabled == 0 && pDoc->m_AreCamerasLoaded)
			{
				if (MessageBox(IDS_M_UNLOAD_CAMERA_DRIVER_NOW,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
					pDoc->UnloadCameras();
			}
			GetDlgItem(IDC_W_CHAMBER)->EnableWindow(m_nCameras);
			GetDlgItem(IDC_TEXT1)->EnableWindow(m_nCameras);
			GetDlgItem(IDC_CHANGE_FREQ)->EnableWindow(m_nCameras);
			pDoc->SetModifiedFlag();
		}
		//EnableCameras(m_wChamber > -1);
		EnableCameras(m_wChamber < pDoc->nCameras && m_wChamber >= 0);
		SetCameraData(FALSE);
		SetTimeSensitiveCameraData();

		//ResetCameraBox();
		//UpdateData(FALSE);
		//OnSelchangeWCamera();
		
	}
}

void CCamerasPage::OnChangeFreq() 
{
	// TODO: Add your control notification handler code here
	CSetFrequencyDlg sDlg(&pDoc->m_CameraData[m_wChamber].m_PictureFrequency);
	if (sDlg.DoModal()==IDOK)
	{
		pDoc->SetModifiedFlag();
		SetCameraData(TRUE);
		if (m_IsCameraEnabled)
			ApplyCameraChanges(m_wChamber);
	}
	SetStrings();
}
