// CalibrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CalibrationDlg.h"
#include <fstream.h>
#include "LADA Control ModuleDoc.h"
#include <iostream.h>
#include "LString.h"
#include "LadaStrings.h"
#include "CalibrationDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int curLanguage;
extern LString Strings;
extern CFont RussianArial;											// The font used
extern void SetItemFont(UINT controlID, CWnd *window);					// Sets and item to a font
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern CString IntToString(int number);
extern int StringToInt(const char * String, int Length = 0);
extern CString workingDirectory;
/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg dialog
#define SENSOR_NAME		0
#define OFFSET_IL		1
#define DATA_IL			2
#define CURRENT_READING	3

CCalibrationDlg::CCalibrationDlg(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CCalibrationDlg::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CCalibrationDlg)
	m_wGroup = -1;
	//}}AFX_DATA_INIT
	groupNames = NULL;
	probeNames = NULL;
	probesPerGroup = NULL;
	offset_location = NULL;
	sensor_location = NULL;
	curProbeNumber = -1;
}

CCalibrationDlg::~CCalibrationDlg()
{
	delete [] groupNames;
	delete [] probeNames;
	delete [] probesPerGroup;
	delete [] offset_location;
	delete [] sensor_location;
}

void CCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalibrationDlg)
	DDX_Control(pDX, IDC_W_GROUP, m_cwGroup);
	DDX_Control(pDX, IDC_SENSORS, m_Sensors);
	DDX_CBIndex(pDX, IDC_W_GROUP, m_wGroup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalibrationDlg, CDialog)
	//{{AFX_MSG_MAP(CCalibrationDlg)
	ON_BN_CLICKED(IDC_LOAD_FILE, OnLoadFile)
	ON_BN_CLICKED(IDC_CALIBRATE, OnCalibrate)
	ON_CBN_SELCHANGE(IDC_W_GROUP, OnSelchangeWGroup)
	ON_NOTIFY(NM_DBLCLK, IDC_SENSORS, OnDblclkSensors)
	ON_NOTIFY(NM_CLICK, IDC_SENSORS, OnClickSensors)
	ON_NOTIFY(NM_KILLFOCUS, IDC_SENSORS, OnKillfocusSensors)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg message handlers

void CCalibrationDlg::OnLoadFile() 
{
	// TODO: Add your control notification handler code here
	
}

void CCalibrationDlg::OnCalibrate() 
{
	// TODO: Add your control notification handler code here
	if (curProbeNumber != -1 && pDoc->commObject)
	{
		CCalibrationDlg2 cDlg2(pDoc, groupNames[m_wGroup][curLanguage], probeNames[curProbeNumber][m_wGroup][curLanguage], sensor_location[curProbeNumber][m_wGroup], offset_location[curProbeNumber][m_wGroup]);
		cDlg2.DoModal();
	}
}

BOOL CCalibrationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_LOAD_FILE,this);
	SetItemFont(IDC_CALIBRATE,this);
	m_Sensors.SetFont(&RussianArial);
	m_Sensors.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_Sensors.InsertColumn(SENSOR_NAME," Sensor Name ");
	m_Sensors.InsertColumn(OFFSET_IL," Offset I.L. ");
	m_Sensors.InsertColumn(DATA_IL," Data I.L. ");
	m_Sensors.InsertColumn(CURRENT_READING," Current Reading ");
	m_cwGroup.SetFont(&RussianArial);

	ifstream fin(workingDirectory + CString("\\calibration.dat"), ios::nocreate );

	if (!fin)
	{
		MessageBox("No calibration.dat file found.  No definitions are available for sensor groups.","Error",MB_ICONWARNING);
	}
	else
	{
		
		groupNames = new CString[MAX_GROUPS][N_LANGUAGES];
		probeNames = new CString[MAX_PROBES][MAX_GROUPS][N_LANGUAGES];
		probesPerGroup = new int[MAX_GROUPS];
		offset_location = new int[MAX_PROBES][MAX_GROUPS];
		sensor_location = new int[MAX_PROBES][MAX_GROUPS];
		memset(offset_location, 0, sizeof(int) * MAX_PROBES * MAX_GROUPS );
		memset(sensor_location, 0, sizeof(int) * MAX_PROBES * MAX_GROUPS );

		char line[101];
		nGroups = 0;
		char *tokenPtr = NULL;
		CString ErrorMessage = "";
		int lineNumber = 0;
		while (fin.getline(line,100) && !fin.eof())
		{
			if (line[0] == '\0')
				continue;

			lineNumber++;
			if (line[0] == '/')
				continue;
			
			tokenPtr = strtok(line,",");
			if (tokenPtr == NULL)
			{
				ErrorMessage = "No English group name in calibration.dat. Error found on line " + IntToString(lineNumber);
				break;
			}
			groupNames[nGroups][0] = tokenPtr;
			
			tokenPtr = strtok(NULL,",");
			if (tokenPtr == NULL)
			{
				ErrorMessage = "No Russian group name in calibration.dat. Error found on line " + IntToString(lineNumber);
				break;
			}
			groupNames[nGroups][1] = tokenPtr;

			tokenPtr = strtok(NULL,",");
			if (tokenPtr == NULL)
			{
				ErrorMessage = "No number of probes listed for group in calibration.dat. Error found on line " + IntToString(lineNumber);
				break;
			}
			probesPerGroup[nGroups] = StringToInt(tokenPtr);

			for (int i = 0; i < probesPerGroup[nGroups]; i++)
			{
				fin.getline(line,100);
				lineNumber++;
				if (line[0] == '/')
				{
					i--;
					continue;
				}
				tokenPtr = strtok(line,",");
				if (tokenPtr == NULL)
				{
					ErrorMessage = CString("No english name for sensor ") + IntToString(i+1) + CString(" in calibration.dat. Error found on line ") + IntToString(lineNumber);
					break;
				}
				probeNames[i][nGroups][0] = tokenPtr;

				tokenPtr = strtok(NULL,",");
				if (tokenPtr == NULL)
				{
					ErrorMessage = CString("No russian name for sensor ") + IntToString(i+1) + CString(" in calibration.dat. Error found on line ") + IntToString(lineNumber);
					break;
				}
				probeNames[i][nGroups][1] = tokenPtr;

				tokenPtr = strtok(NULL,",");
				if (tokenPtr == NULL)
				{
					ErrorMessage = CString("No sensor input location for sensor ") + IntToString(i+1) + CString(" in calibration.dat. Error found on line ") + IntToString(lineNumber);
					break;
				}
				sensor_location[i][nGroups] = StringToInt(tokenPtr);

				tokenPtr = strtok(NULL,",");
				if (tokenPtr == NULL)
				{
					ErrorMessage = CString("No offset input location for sensor ") + IntToString(i+1) + CString(" in calibration.dat. Error found on line ") + IntToString(lineNumber);
					break;
				}
				offset_location[i][nGroups] = StringToInt(tokenPtr);
			}
			if (ErrorMessage != "")
				break;
			nGroups++;
		}
		if (ErrorMessage != "")
		{
			MessageBox(ErrorMessage,"Error",MB_ICONWARNING);
		}
		for (int i = 0; i < nGroups; i++)
		{
			m_cwGroup.AddString(groupNames[i][curLanguage]);
		}
		m_wGroup = 0;
		UpdateData(FALSE);
		ShowGroupData();
		SetStrings();

	}

	GetDlgItem(IDC_CALIBRATE)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalibrationDlg::OnSelchangeWGroup() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	ShowGroupData();
}

void CCalibrationDlg::ShowGroupData()
{
	m_Sensors.DeleteAllItems();

	for (int i = 0; i < probesPerGroup[m_wGroup]; i++)
	{
		m_Sensors.InsertItem(i, probeNames[i][m_wGroup][curLanguage]);
	}
	
	m_Sensors.SetColumnWidth(SENSOR_NAME, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(OFFSET_IL, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(DATA_IL, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(CURRENT_READING, LVSCW_AUTOSIZE_USEHEADER);
	
	CollectData();
}

void CCalibrationDlg::SetStrings()
{
	SetWindowText(Strings.get(IDS_CC0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_CC1));
	GetDlgItem(IDC_LOAD_FILE)->SetWindowText(Strings.get(IDS_CC2));
	GetDlgItem(IDC_CALIBRATE)->SetWindowText(Strings.get(IDS_CC3));
	LVCOLUMN* x=new LVCOLUMN;
	char* tempst=new char[20];
	for (int y=0;y<4;y++)
	{
		x->mask=LVCF_TEXT;
		x->pszText=tempst;
		x->cchTextMax=20;
		m_Sensors.GetColumn(y,x);
		CString a=Strings.get(IDS_CC4+y);
		LPTSTR temp=a.GetBuffer(0);
		x->pszText=temp;
		m_Sensors.SetColumn(y,x);
		
	}
	delete [] tempst;
	delete [] x;
	
}

BOOL CCalibrationDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		ShowGroupData();
		UpdateData(TRUE);
		m_cwGroup.ResetContent();
		for (int i = 0; i < nGroups; i++)
		{
			m_cwGroup.AddString(groupNames[i][curLanguage]);
		}
		UpdateData(FALSE);
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CCalibrationDlg::OnDblclkSensors(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_CALIBRATE)->EnableWindow(TRUE);
	POSITION pos = m_Sensors.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		curProbeNumber = m_Sensors.GetNextSelectedItem(pos);
	}
	OnCalibrate();
	*pResult = 0;
}

void CCalibrationDlg::OnClickSensors(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_CALIBRATE)->EnableWindow(TRUE);
	POSITION pos = m_Sensors.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		curProbeNumber = m_Sensors.GetNextSelectedItem(pos);
	}
	*pResult = 0;
}

void CCalibrationDlg::OnKillfocusSensors(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	const MSG * curMessage = GetCurrentMessage();
	//POINT messagePoint = curMessage->pt;
	//ScreenToClient(&messagePoint);

	//GetDlgItem(IDC_CALIBRATE)->
	//CWnd * dlg;
	
	CRect buttonRect;
	GetDlgItem(IDC_CALIBRATE)->GetWindowRect(&buttonRect);
	if (buttonRect.PtInRect( curMessage->pt ))
	{
		// they have clicked on the calibrate button
		//MessageBox("Calibrate clicked.");
		OnCalibrate();
	}
	
	curProbeNumber = -1;
	GetDlgItem(IDC_CALIBRATE)->EnableWindow(FALSE);
	*pResult = 0;
}

void CCalibrationDlg::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	CollectData();
}

void CCalibrationDlg::CollectData()
{
	CWaitCursor wCursor;
	int * wLocations = new int[probesPerGroup[m_wGroup]];
	double * returnData = new double[probesPerGroup[m_wGroup]];

	for (int i = 0; i < probesPerGroup[m_wGroup]; i++)
	{
		wLocations[i] = sensor_location[i][m_wGroup];
	}
	if (pDoc->commObject)
	{
		pDoc->GetInputLocations(wLocations, probesPerGroup[m_wGroup], returnData, 29);
	}
	for ( i = 0; i < probesPerGroup[m_wGroup]; i++)
	{
		m_Sensors.SetItemText(i, OFFSET_IL, ValueToString(offset_location[i][m_wGroup], 0));
		m_Sensors.SetItemText(i, DATA_IL, ValueToString(sensor_location[i][m_wGroup],0));
		if (pDoc->commObject)
			m_Sensors.SetItemText(i, CURRENT_READING, ValueToString(returnData[i],4));
		else
			m_Sensors.SetItemText(i, CURRENT_READING, "??");
	}

	delete [] returnData;
	delete [] wLocations;

	m_Sensors.SetColumnWidth(SENSOR_NAME, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(OFFSET_IL, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(DATA_IL, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(CURRENT_READING, LVSCW_AUTOSIZE_USEHEADER);
}
