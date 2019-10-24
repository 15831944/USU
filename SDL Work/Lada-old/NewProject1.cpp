// This is Version 1.0 PLEASE DOCUMENT CHANGES
// NewProject1.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "NewProject1.h"

#include "LADA Control ModuleDoc.h"
#include "Ladastrings.h"
#include "LString.h"
#include "WetupSettingsDlg.h"
#include "ChooseLocationsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

extern int  AssociateFile(char (*InputLocNameList)[2][30], int maxNum, CString filename = "", int wType = 0, int ArrayID = 0);
extern CFont RussianArial;
extern LString Strings;
extern int curLanguage;
extern CTimeSpan DataPlotFreqTable[7];
extern int BackPointsTable[4];

int GetRussianEnding(int t)
{
	// 0 = nominative case
	// 1 = genitive singular
	// 2 = genitive plural

	if ((t % 10) == 1 && t != 11) // dyen
		return 0;
	else if ((t%100) >= 11 && (t%100) <= 14) // dnyei
		return 2;
	else if ((t%10) >= 2 && (t%10) <= 4) // dnya
		return 1;
	else // dnyei
		return 2;
}

CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4)
{
	CString Time;
	int t;
	int fields = 0;

	if (curLanguage == ENGLISH)
	{
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
	}
	else if (curLanguage == RUSSIAN)
	{
		if (t = C.GetDays()){
			Time = C.Format(CString("%D ") + Strings.get(IDS_RUSSIAN_DAY + GetRussianEnding(t)));	
			fields++;
		}
		if ((t = C.GetHours()) && fields < DisplayFields){
			Time += C.Format(CString("%H ") + Strings.get(IDS_RUSSIAN_HOUR + GetRussianEnding(t)));
			fields++;
		}
		if ((t = C.GetMinutes()) && fields < DisplayFields){
			Time += C.Format(CString("%M ") + Strings.get(IDS_RUSSIAN_MINUTE + GetRussianEnding(t)));
			fields++;
		}
		if ((t = C.GetSeconds()) && fields < DisplayFields){
			Time += C.Format(CString("%S ") + Strings.get(IDS_RUSSIAN_SECOND + GetRussianEnding(t)));
			fields++;
		}
	}
	return Time;

}

/////////////////////////////////////////////////////////////////////////////
// CNewProject1 dialog


CNewProject1::CNewProject1(CLADAControlModuleDoc *d, CWnd* pParent /*=NULL*/)
	: CDialog(CNewProject1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProject1)
	m_DoWetup = FALSE;
	m_curPlotFreqSel = -1;
	m_curBackPointsSel = -1;
	m_nGraphsSel = -1;
	m_ProjectName = _T("");
	m_VisibleSpan = _T("");
	m_nWetupLocations = 0;
	m_nCameras = 0;
	m_CameraFreq = 1.0;
	m_wCamera = 0;
	//}}AFX_DATA_INIT

	m_DlgInitialized = FALSE;

	doc = d;
	
	//InputListType InputLocationNameList[MAX_INPUT_LOCATIONS];
	
	for (int i = 0; i < MAX_INPUT_LOCATIONS; i++){
		wsprintf(InputLocationNameList[i][ENGLISH], "%3i:[no name]", i+1);
		wsprintf(InputLocationNameList[i][RUSSIAN], "%3i:[屠锹劳冗 团襗", i+1);
		wsprintf(WInputLocationNameList[i][ENGLISH], "%3i:[no name]", i+1);
		wsprintf(WInputLocationNameList[i][RUSSIAN], "%3i:[屠锹劳冗 团襗", i+1);
	}//YFPDFYBZ YTN
	doc->nInputLocations = 0;
	doc->m_WetupInfo.nInputLocations = 0;
	

	if (MessageBox(IDS_M_EXISTS_CS_FILE, NO_TITLE, MB_YESNO|MB_ICONQUESTION ) == IDYES)
	{
		//SetStrings();
		AssociateFile(InputLocationNameList, MAX_INPUT_LOCATIONS);
	}
	

	CChooseLocationsDlg getNamesDlg(InputLocationNameList, InputLocationList, &doc->nInputLocations);
	getNamesDlg.DoModal();

}

void CNewProject1::ShowVisibleSpan()
{
	UpdateData(TRUE);
	CTimeSpan visibleSpan = CTimeSpan(time_t(DataPlotFreqTable[m_curPlotFreqSel].GetTotalSeconds() * BackPointsTable[m_curBackPointsSel]));
	m_VisibleSpan = GetTimeSpan(visibleSpan, 3);
	UpdateData(FALSE);
}

void CNewProject1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProject1)
	DDX_Control(pDX, IDC_N_GRAPHS, m_nGraphs);
	DDX_Control(pDX, IDC_N_BACK_POINTS, m_CNBackPoints);
	DDX_Control(pDX, IDC_LOCATION_LIST, m_CLocationList);
	DDX_Control(pDX, IDC_GRAPH_PLOT_FREQ, m_CGraphPlotFreq);
	DDX_Check(pDX, IDC_DOWETUP, m_DoWetup);
	DDX_CBIndex(pDX, IDC_GRAPH_PLOT_FREQ, m_curPlotFreqSel);
	DDX_CBIndex(pDX, IDC_N_BACK_POINTS, m_curBackPointsSel);
	DDX_CBIndex(pDX, IDC_N_GRAPHS, m_nGraphsSel);
	DDX_Text(pDX, IDC_SAVE_PROJECT, m_ProjectName);
	DDX_Text(pDX, IDC_VISIBLE_SPAN, m_VisibleSpan);
	DDX_Text(pDX, IDC_N_WETUP, m_nWetupLocations);
	DDX_Text(pDX, IDC_N_CAMERAS, m_nCameras);
	DDX_Text(pDX, IDC_C_FREQ, m_CameraFreq);
	DDX_CBIndex(pDX, IDC_W_CAMERA, m_wCamera);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProject1, CDialog)
	//{{AFX_MSG_MAP(CNewProject1)
	ON_BN_CLICKED(IDC_DOWETUP, OnDowetup)
	ON_BN_CLICKED(IDC_EDIT_LOCATION_LIST, OnEditLocationList)
	ON_CBN_SELCHANGE(IDC_GRAPH_PLOT_FREQ, OnSelchangeGraphPlotFreq)
	ON_CBN_SELCHANGE(IDC_N_BACK_POINTS, OnSelchangeNBackPoints)
	ON_BN_CLICKED(IDC_WSETTINGS, OnWsettings)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_EDIT_WETUP_LOCATION_LIST, OnEditWetupLocationList)
	ON_CBN_SELCHANGE(IDC_W_CAMERA, OnSelchangeWCamera)
	ON_EN_CHANGE(IDC_N_CAMERAS, OnChangeNCameras)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProject1 message handlers

void CNewProject1::OnDowetup() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItem(IDC_WSETTINGS)->EnableWindow(m_DoWetup);
}

void CNewProject1::OnEditLocationList() 
{
	CChooseLocationsDlg getNamesDlg(InputLocationNameList, InputLocationList, &doc->nInputLocations);
	getNamesDlg.DoModal();
	
	m_CLocationList.ResetContent();
	
	if (doc->InputLocationList){
		delete [] doc->InputLocationList;
		doc->InputLocationList = NULL;
	}
	if (doc->InputLocationNameList)
	{
		delete [] doc->InputLocationNameList;
		doc->InputLocationNameList = NULL;
	}
	
	if (doc->nInputLocations)
	{
		doc->InputLocationList = new int[doc->nInputLocations];
		doc->InputLocationNameList = new InputListType[doc->nInputLocations];
		for (int i = 0; i < doc->nInputLocations; i++)
		{
			memcpy(doc->InputLocationNameList[i], InputLocationNameList[InputLocationList[i]],sizeof(InputListType));
		}
		memcpy(doc->InputLocationList, InputLocationList, sizeof(int) * doc->nInputLocations);
	}
	SetStrings();
	//for (int i = 0; i < doc->nInputLocations; i++)
	//{
	//	m_CLocationList.AddString(doc->InputLocationNameList[i][curLanguage]);
	//}
	
}



BOOL CNewProject1::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	m_DlgInitialized = TRUE;
	// m_ByAverage - value set in on average
	SetFont(&RussianArial);

	for (int i = 0; i < 9; i++)
		GetDlgItem(IDC_TEXT1 + i)->SetFont(&RussianArial);

	GetDlgItem(IDC_EDIT_LOCATION_LIST)->SetFont(&RussianArial);
	GetDlgItem(IDC_DOWETUP)->SetFont(&RussianArial);
	GetDlgItem(IDC_WSETTINGS)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_EDIT_WETUP_LOCATION_LIST)->SetFont(&RussianArial);
	GetDlgItem(IDC_N_W_LOCATIONS)->SetFont(&RussianArial);
	GetDlgItem(IDC_N_WETUP)->SetFont(&RussianArial);
	
	GetDlgItem(IDC_C_OPTIONS)->SetFont(&RussianArial);
	GetDlgItem(IDC_N_CAMERAS_TEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_N_CAMERAS)->SetFont(&RussianArial);
	GetDlgItem(IDC_W_CAMERA)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_FREQ_TEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_FREQ)->SetFont(&RussianArial);
	GetDlgItem(IDC_HOURS)->SetFont(&RussianArial);

	m_CLocationList.SetFont(&RussianArial);
	m_CGraphPlotFreq.SetFont(&RussianArial);
	m_CNBackPoints.SetFont(&RussianArial);
	m_nGraphs.SetFont(&RussianArial);
	GetDlgItem(IDC_SAVE_PROJECT)->SetFont(&RussianArial);
	GetDlgItem(IDC_VISIBLE_SPAN)->SetFont(&RussianArial);
	
	if (doc->InputLocationList){
		delete [] doc->InputLocationList;
		doc->InputLocationList = NULL;
	}
	if (doc->InputLocationNameList)
	{
		delete [] doc->InputLocationNameList;
		doc->InputLocationNameList = NULL;
	}
	
	if (doc->nInputLocations)
	{
		doc->InputLocationList = new int[doc->nInputLocations];
		doc->InputLocationNameList = new InputListType[doc->nInputLocations];
		for (int i = 0; i < doc->nInputLocations; i++)
		{
			memcpy(doc->InputLocationNameList[i], InputLocationNameList[InputLocationList[i]],sizeof(InputListType));
		}
		memcpy(doc->InputLocationList, InputLocationList, sizeof(int) * doc->nInputLocations);
	}
	
	SetStrings();

	m_DoWetup = doc->m_DoWetup;
	m_curPlotFreqSel = 3;
	m_curBackPointsSel = 1;
	for ( i = 0; i < 7; i++)
	{
		if (DataPlotFreqTable[i] == doc->dataPlotFreq)
		{
			m_curPlotFreqSel = i;
			break;
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (BackPointsTable[i] == doc->nBackPoints)
		{
			m_curBackPointsSel = i;
			break;
		}
	}
	m_ProjectName = doc->projectName;
	m_nGraphsSel = 2;
	m_nWetupLocations = doc->m_WetupInfo.nInputLocations;
	
	m_nCameras = doc->nCameras;
	for (i = 0; i < m_nCameras; i++)
		m_CameraData[i].m_PictureFrequency = doc->m_CameraData[i].m_PictureFrequency;
	
	ResetCameraBox();
	m_wCamera = 0;
	EnableCameras(m_nCameras > 0);
	UpdateData(FALSE);
	ShowVisibleSpan();
	
	//Reset();
	OnDowetup();
	OnSelchangeWCamera();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewProject1::OnSelchangeGraphPlotFreq() 
{
	// TODO: Add your control notification handler code here
	ShowVisibleSpan();
}

void CNewProject1::OnSelchangeNBackPoints() 
{
	// TODO: Add your control notification handler code here
	if (m_curBackPointsSel == 4){
		// choose custom number of back points

	}
	ShowVisibleSpan();
}

void CNewProject1::OnWsettings() 
{
	// TODO: Add your control notification handler code here
	CWetupSettingsDlg wDlg(doc);
	wDlg.DoModal();
	SetStrings();
}


void CNewProject1::OnNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (doc->nInputLocations == 0){
		MessageBox(IDS_M_MUST_SELECT_ONE_LOCATION, NO_TITLE, MB_ICONINFORMATION);
		//GetDlgItem(IDC_EDIT_LOCATION_LIST)->SetFocus();
		SetStrings();
		OnEditLocationList();
		return;	
	}
	if (m_DoWetup && doc->m_WetupInfo.nInputLocations == 0)
	{
		MessageBox(IDS_M_MUST_SELECT_ONE_LOCATION, NO_TITLE, MB_ICONINFORMATION);
		SetStrings();
		OnEditWetupLocationList();
		return;
	}

	OnSelchangeWCamera();

	if (doc->m_CameraData)
		delete [] doc->m_CameraData;
	doc->m_CameraData = NULL;
	if (m_nCameras)
	{
		doc->m_CameraData = new CCameraData[m_nCameras];
		doc->nCameras = m_nCameras;
		for (int i = 0; i < m_nCameras; i++)
			doc->m_CameraData[i] = m_CameraData[i];
	}

	doc->m_DoWetup = m_DoWetup;
	
	doc->dataPlotFreq = DataPlotFreqTable[m_curPlotFreqSel];
	doc->nBackPoints = BackPointsTable[m_curBackPointsSel];
	doc->projectName = m_ProjectName;
	doc->nPanes = 3;//m_nGraphsSel + 1;

	CDialog::OnOK();
}

void CNewProject1::SetStrings()
{
	SetWindowText(Strings.get(IDS_C0));
	UpdateData(TRUE);
	for (int i = 0; i < 9; i++)
		GetDlgItem(IDC_TEXT1 + i)->SetWindowText(Strings.get(IDS_C1 + i));
	
	GetDlgItem(IDC_EDIT_LOCATION_LIST)->SetWindowText(Strings.get(IDS_C10));
	GetDlgItem(IDC_DOWETUP)->SetWindowText(Strings.get(IDS_C11));
	GetDlgItem(IDC_WSETTINGS)->SetWindowText(Strings.get(IDS_C12));
	GetDlgItem(IDC_NEXT)->SetWindowText(Strings.get(IDS_C13));
	GetDlgItem(IDC_EDIT_WETUP_LOCATION_LIST)->SetWindowText(Strings.get(IDS_C10));
	GetDlgItem(IDC_N_W_LOCATIONS)->SetWindowText(Strings.get(IDS_C14));

	GetDlgItem(IDC_C_OPTIONS)->SetWindowText(Strings.get(IDS_C15));
	GetDlgItem(IDC_N_CAMERAS_TEXT)->SetWindowText(Strings.get(IDS_C16));
	GetDlgItem(IDC_C_FREQ_TEXT)->SetWindowText(Strings.get(IDS_C17));
	GetDlgItem(IDC_HOURS)->SetWindowText(Strings.get(IDS_AA12));

	m_CLocationList.ResetContent();
	for ( i = 0; i < doc->nInputLocations; i++)
		m_CLocationList.AddString(doc->InputLocationNameList[i][curLanguage]);
	
	m_CGraphPlotFreq.ResetContent();
	for (i = 0; i < 7; i++)
		m_CGraphPlotFreq.AddString(Strings.get(IDS_N_DATAPLOT1 + i));
	
	m_CNBackPoints.ResetContent();
	for (i = 0; i < 3; i++)
		m_CNBackPoints.AddString(Strings.get(IDS_N_BACKPOINT1 + i));

	m_nGraphs.ResetContent();
	for (i = 0; i < 4; i++)
		m_nGraphs.AddString(CString(char(i+'1')));
	ResetCameraBox();
	UpdateData(FALSE);
	ShowVisibleSpan();
	

}

BOOL CNewProject1::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		curLanguage = !curLanguage;
		SetStrings();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}



void CNewProject1::OnEditWetupLocationList() 
{
	// TODO: Add your control notification handler code here
	CChooseLocationsDlg getNamesDlg(WInputLocationNameList, WInputLocationList, &doc->m_WetupInfo.nInputLocations);
	getNamesDlg.DoModal();
	
	if (doc->m_WetupInfo.InputLocationList){
		delete [] doc->m_WetupInfo.InputLocationList;
		doc->m_WetupInfo.InputLocationList = NULL;
	}
	if (doc->m_WetupInfo.InputLocationNameList)
	{
		delete [] doc->m_WetupInfo.InputLocationNameList;
		doc->m_WetupInfo.InputLocationNameList = NULL;
	}
	
	if (doc->m_WetupInfo.nInputLocations)
	{
		doc->m_WetupInfo.InputLocationList = new int[doc->m_WetupInfo.nInputLocations];
		doc->m_WetupInfo.InputLocationNameList = new InputListType[doc->m_WetupInfo.nInputLocations];
		for (int i = 0; i < doc->m_WetupInfo.nInputLocations; i++)
		{
			memcpy(doc->m_WetupInfo.InputLocationNameList[i], WInputLocationNameList[WInputLocationList[i]],sizeof(InputListType));
		}
		memcpy(doc->m_WetupInfo.InputLocationList, WInputLocationList, sizeof(int) * doc->m_WetupInfo.nInputLocations);
	}
	UpdateData(TRUE);
	m_nWetupLocations =doc->m_WetupInfo.nInputLocations;
	UpdateData(FALSE);
	SetStrings();
	
}

void CNewProject1::OnSelchangeWCamera() 
{
	// TODO: Add your control notification handler code here
	int prevSel = m_wCamera;
	UpdateData();

	if (m_CameraFreq < 0.0)
	{
		MessageBox(IDS_M_CAMERA_FREQ_EXCEED_ZERO,IDS_PROGRAM_NAME);
		m_CameraFreq = 0.0;
	}

	if (prevSel >= 0)
		m_CameraData[prevSel].m_PictureFrequency = CTimeSpan(0,int(m_CameraFreq),int((double(m_CameraFreq)-double(int(m_CameraFreq))) * 60.0), 0);

	if (m_wCamera >= 0 && prevSel != m_wCamera)
		m_CameraFreq = m_CameraData[m_wCamera].m_PictureFrequency.GetTotalMinutes() / 60.0;

	UpdateData(FALSE);
}

void CNewProject1::OnChangeNCameras() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
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
		if (m_wCamera >= m_nCameras)
			m_wCamera = m_nCameras - 1;
		if (m_wCamera < 0 && m_nCameras > 0)
			m_wCamera = 0;
		EnableCameras(m_wCamera > -1);
		ResetCameraBox();
		UpdateData(FALSE);
		OnSelchangeWCamera();
		
	}
}

void CNewProject1::EnableCameras(BOOL enable)
{
	GetDlgItem(IDC_W_CAMERA)->EnableWindow(enable);
	GetDlgItem(IDC_C_FREQ_TEXT)->EnableWindow(enable);
	GetDlgItem(IDC_C_FREQ)->EnableWindow(enable);
	GetDlgItem(IDC_HOURS)->EnableWindow(enable);
}

void CNewProject1::ResetCameraBox()
{
	((CComboBox *)GetDlgItem(IDC_W_CAMERA))->ResetContent();
	for (int i = 0; i < m_nCameras; i++)
		((CComboBox *)GetDlgItem(IDC_W_CAMERA))->AddString(Strings.get(IDS_F3+i));
}
