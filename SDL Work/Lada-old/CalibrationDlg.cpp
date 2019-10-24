// CalibrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CalibrationDlg.h"
#include <fstream.h>
#include "LADA Control ModuleDoc.h"
#include <iostream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int curLanguage;

extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg dialog
#define SENSOR_NAME		0
#define OFFSET_IL		1
#define DATA_IL			2
#define CURRENT_READING	3

CCalibrationDlg::CCalibrationDlg(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CCalibrationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalibrationDlg)
	m_wGroup = -1;
	//}}AFX_DATA_INIT
	groupNames = NULL;
	probeNames = NULL;
	probesPerGroup = NULL;
	offset_location = NULL;
	data_location = NULL;
}

CCalibrationDlg::~CCalibrationDlg()
{
	delete [] groupNames;
	delete [] probeNames;
	delete [] probesPerGroup;
	delete [] offset_location;
	delete [] data_location;
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
	
}

BOOL CCalibrationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Sensors.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_Sensors.InsertColumn(SENSOR_NAME," Sensor Name ");
	m_Sensors.InsertColumn(OFFSET_IL," Offset I.L. ");
	m_Sensors.InsertColumn(DATA_IL," Data I.L. ");
	m_Sensors.InsertColumn(CURRENT_READING," Current Reading ");

	ifstream fin("calibration.dat", ios::nocreate );

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
		data_location = new int[MAX_PROBES][MAX_GROUPS];
		memset(offset_location, 0, sizeof(int) * MAX_PROBES * MAX_GROUPS );
		memset(data_location, 0, sizeof(int) * MAX_PROBES * MAX_GROUPS );

		char firstChar;
		char endOfLine[11];
		char line[101];
		nGroups = 0;

		while (firstChar = fin.peek() && !fin.eof())
		{
			fin.getline(line,100);
			if (firstChar == '\\')
				continue;

			fin.getline(groupNames[nGroups][0].GetBuffer(50),50,'\"');
			fin >> probesPerGroup[nGroups];
			fin.getline(endOfLine,10);
			fin >> firstChar;
			fin.getline(groupNames[nGroups][1].GetBuffer(50),50,'\"');
			fin.getline(endOfLine,10);

			for (int i = 0; i < probesPerGroup[nGroups]; i++)
			{
				fin >> firstChar;
				fin.getline(probeNames[i][nGroups][0].GetBuffer(50),50,'\"');
				if (fin >> offset_location[i][nGroups])
					fin.getline(endOfLine,10);
				else
					fin.clear();
				fin >> firstChar;
				fin.getline(probeNames[i][nGroups][1].GetBuffer(50),50,'\"');
				fin.getline(endOfLine,10);
			}
			nGroups++;
		}

		for (int i = 0; i < nGroups; i++)
		{
			m_cwGroup.AddString(groupNames[i][curLanguage]);
		}
		m_wGroup = 0;
		UpdateData(FALSE);
		ShowGroupData();

	}


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
		m_Sensors.SetItemText(i, OFFSET_IL, ValueToString(offset_location[i][m_wGroup], 0));
		m_Sensors.SetItemText(i, DATA_IL,"");
		m_Sensors.SetItemText(i, CURRENT_READING, "");
	}

	m_Sensors.SetColumnWidth(SENSOR_NAME, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(OFFSET_IL, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(DATA_IL, LVSCW_AUTOSIZE_USEHEADER);
	m_Sensors.SetColumnWidth(CURRENT_READING, LVSCW_AUTOSIZE_USEHEADER);

}
