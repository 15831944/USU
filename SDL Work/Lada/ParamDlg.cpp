// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog allows you to change the parameters for the document
// ParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "ParamDlg.h"
#include "LADA Control ModuleDoc.h"
#include "ControlParameters.h"

//#include "ChooseTime.h"
#include "WetupSettingsDlg.h"
#include "Ladastrings.h"
#include "lstring.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK); // Message Box
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);		// Message Box
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);				// Message Box
#undef MessageBox
#define MessageBox MyMessageBox

#include "inputlocations.h"

extern CString IntToString(int number);
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);			// Returns value with dPlaces numbers as a CString 
extern LString Strings;													// Contains the text Strings in both languages
extern CFont RussianArial;											// The font used
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);	// Sets text to a font
extern void SetItemFont(UINT controlID, CWnd *window);					// Sets an Item to a font

/////////////////////////////////////////////////////////////////////////////
// CParamDlg dialog

// Constructor
// doc is the current document
// Sets inital values to 0 and m_wChamber to -1
CParamDlg::CParamDlg(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CParamDlg::IDD, pParent)
{
	m_ShowWetup = TRUE;//ShowWetup;
	//IsInitialization = Initialization;
	pDoc=doc;
	//{{AFX_DATA_INIT(CParamDlg)
	m_wChamber = -1;
	m_CR10Moisture = 0.0;
	m_Moisture = 0.0;
	m_CR10LightOff = 0;
	m_CR10LightOn = 0;
	m_LightOff = 0;
	m_LightOn = 0;
	m_wSMPFreq = -1;
	m_CR10MaxDosage = 0;
	m_MaxDosage = 0;
	m_MoistureReading = _T("");
	//}}AFX_DATA_INIT

}

// Data Exchange
void CParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamDlg)
	DDX_Control(pDX, IDC_SMP_FREQ, m_cSMPFreq);
	DDX_Control(pDX, IDC_SELECT_CHAMBER, m_cwChamber);
	DDX_CBIndex(pDX, IDC_SELECT_CHAMBER, m_wChamber);
	DDX_Text(pDX, IDC_CR10_M_LEVEL, m_CR10Moisture);
	DDX_Text(pDX, IDC_NEW_M_LEVEL, m_Moisture);
	DDX_Text(pDX, IDC_CR10_LIGHT_TIME_OFF, m_CR10LightOff);
	DDX_Text(pDX, IDC_CR10_LIGHT_TIME_ON, m_CR10LightOn);
	DDX_Text(pDX, IDC_NEW_LIGHT_TIME_OFF, m_LightOff);
	DDX_Text(pDX, IDC_NEW_LIGHT_TIME_ON, m_LightOn);
	DDX_CBIndex(pDX, IDC_SMP_FREQ, m_wSMPFreq);
	DDX_Text(pDX, IDC_CR10_MAX_DOSAGE, m_CR10MaxDosage);
	DDX_Text(pDX, IDC_NEW_MAX_DOSAGE, m_MaxDosage);
	DDX_Text(pDX, IDC_MOISTURE_READING, m_MoistureReading);
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(CParamDlg, CDialog)
	//{{AFX_MSG_MAP(CParamDlg)
	ON_CBN_SELCHANGE(IDC_SELECT_CHAMBER, OnSelchangeSelectChamber)
	ON_BN_CLICKED(ID_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_LIGHTS1, OnLights1)
	ON_BN_CLICKED(IDC_LIGHTS2, OnLights2)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamDlg message handlers

// Initialization
// Sets Fonts, and retrieves values from the document
// Displays CR10 Time and Computer Time
BOOL CParamDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_wChamber = 0;
	curControlParameters = &pDoc->m_ControlParameters[m_wChamber];

	// important values
	m_Moisture = curControlParameters->m_MoistureLevel;
	m_MaxDosage = pDoc->m_ControlParameters[0].m_MaxDosage;
	// the reason for this is that only one max dosage is used for both chambers
	//m_Fan = curControlParameters->m_FanOnTime;
	m_LightOn = curControlParameters->m_LightOnTime;
	m_LightOff = curControlParameters->m_LightOffTime;
	m_24Hour = curControlParameters->m_24Hour;
	m_wSMPFreq = curControlParameters->m_SMPFreq;
	SetLocations();

	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT6,this);
	SetItemFont(IDC_TEXT8,this);
	SetItemFont(IDC_TEXT_MOISTURE,this);
	SetItemFont(IDC_TEXT_LIGHTS_ON,this);
	SetItemFont(IDC_TEXT_LIGHTS_OFF,this);
	//SetItemFont(IDC_TEXT_FANS,this);
	SetItemFont(ID_UPDATE,this);
	SetItemFont(IDOK,this);
	//IDC_INITIALIZATION
	SetItemFont(IDC_LIGHTS1,this);
	SetItemFont(IDC_LIGHTS2,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDC_SMP_FREQ,this);
	SetItemFont(IDC_MAX_DOSAGE ,this);
	SetItemFont(IDC_CR10_MAX_DOSAGE ,this);
	SetItemFont(IDC_NEW_MAX_DOSAGE ,this);
	SetItemFont(IDC_DOSE_UNITS ,this);
	SetItemFont(IDC_CR10_M_LEVEL,this);
	SetItemFont(IDC_NEW_M_LEVEL,this);
	SetItemFont(IDC_CR10_LIGHT_TIME_ON,this);
	SetItemFont(IDC_CR10_LIGHT_TIME_OFF,this);
	SetItemFont(IDC_NEW_LIGHT_TIME_ON,this);
	SetItemFont(IDC_NEW_LIGHT_TIME_OFF,this);
	SetItemFont(IDC_MOISTURE_READING,this);
	SetItemFont(IDC_LAST_SMP_AVERAGE,this);
	m_cwChamber.SetFont(&RussianArial);

	m_CanUpdateCR10 = true;


	if (pDoc->commObject && pDoc->m_ControlState == Regular)
	{
		if (!GetCR10Parameters())
		{
			MakeCR10Inactive();
		}
		else
		{
			if ( pDoc->nGrowthChambers == 0 )
				MakeCR10ParametersInactive();
			else
				UpdateLightSettings(m_24Hour);
		}

	}
	else
	{
		MakeCR10Inactive();	
	}

	
	SetStrings(FALSE);
	
	//if (IsInitialization)
	//{
	//	GetDlgItem(IDC_INITIALIZATION)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_CR10_FUNCTIONS)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_DATA_COLLECTION)->EnableWindow(FALSE);
	//}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// Called when the OK Button is pressed
// Asks if you wish to save if there is a change and then exits
void CParamDlg::OnOK() 
{
	UpdateData(TRUE);
	SaveValues();

	if (CloseCurrentChamber())
		EndDialog(IDOK);

	//CDialog::OnOK();
}


// Called when you change which paramter you wish to view
// Allows you to select between Chamber A and Chamber b
void CParamDlg::OnSelchangeSelectChamber() 
{
	UpdateData();
	if (CloseCurrentChamber())
	{
		SetLocations();
		if (pDoc->commObject)
		{
			if (!GetCR10Parameters())
				MakeCR10Inactive();
			if ( pDoc->nGrowthChambers == 0 )
				MakeCR10ParametersInactive();
		}
		else
		{
			MakeCR10Inactive();	
		}
	}
}

// This function retrieves the parameters stored in the CR10
BOOL CParamDlg::GetCR10Parameters()
{
	int locations[5] = { m_MoistureLocation, m_LightOffLocation, m_LightOnLocation, IL_MAX_DOSAGE, IL_AVERAGE_SMP_A };
	double returnData[5];
	int loff, lon;

	pDoc->GetInputLocations(locations,5,returnData, 23);
	m_CR10Moisture = returnData[0];
	m_CR10MaxDosage = returnData[3];
	m_MoistureReading = ValueToString(returnData[4]);
	loff = (int)returnData[1];
	lon = (int)returnData[2];

	m_CR10LightOn = (int)lon;
	
	// means we are in 24 hour mode
	m_24Hour = (BOOL)((int)loff > 24);
	if ((int)loff <= 24)
	{
		m_CR10LightOff = (int)loff;
	}

	UpdateLightSettings(m_24Hour);

	return TRUE;
}

// This function writes the parameter values to the CR10
BOOL CParamDlg::UpdateCR10Parameters()
{
	CWaitCursor wCursor;
	if (pDoc->commObject && UpdateData(TRUE))
	{
		BOOL SetSuccess = pDoc->SetControlParameters(m_wChamber, m_Moisture, m_MaxDosage, m_24Hour, m_LightOn, m_LightOff, m_wSMPFreq );
		
		if (SetSuccess)
		{
			GetCR10Parameters();
			if (pDoc->m_ControlMode==AutomaticControlMode)
			{
				CTime cur=CTime::GetCurrentTime();
				int now=cur.GetHour();
				if (now>=m_LightOn && now < m_LightOff)
				{
					pDoc->commObject->ControlCR10(On);
				}
				else if (now<m_LightOn && now >= m_LightOff)
				{
					pDoc->commObject->ControlCR10(Off);
				}
				else if (m_LightOn<m_LightOff)
				{
					pDoc->commObject->ControlCR10(Off);
				}
				else if (m_LightOff<m_LightOn)
				{
					pDoc->commObject->ControlCR10(On);
				}
			}
		}
		else
		{
			MessageBox(IDS_CANT_SET_VALUES, IDS_WARNING, MB_ICONWARNING);
			SetStrings();
		}
		UpdateData(FALSE);
	}
	return FALSE;
}

// This function disables the dialog
void CParamDlg::MakeCR10Inactive()
{
	m_CanUpdateCR10 = false;
	MakeCR10ParametersInactive();
	//GetDlgItem(IDC_DATA_COLLECTION)->EnableWindow(FALSE);
	//GetDlgItem(IDC_INITIALIZATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEXT2)->EnableWindow(FALSE);

}

void CParamDlg::MakeCR10ParametersInactive()
{
	GetDlgItem(IDC_SELECT_CHAMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEXT_MOISTURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEXT_LIGHTS_ON)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEXT_LIGHTS_OFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_CR10_M_LEVEL)->EnableWindow(FALSE);
	//GetDlgItem(IDC_CR10_FAN_TIME_ON)->EnableWindow(FALSE);
	//GetDlgItem(IDC_CR10_FAN_TIME_OFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_CR10_LIGHT_TIME_ON)->EnableWindow(FALSE);
	GetDlgItem(IDC_CR10_LIGHT_TIME_OFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEW_M_LEVEL)->EnableWindow(FALSE);
	//GetDlgItem(IDC_NEW_FAN_TIME_ON)->EnableWindow(FALSE);
	//GetDlgItem(IDC_NEW_FAN_TIME_OFF)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEW_LIGHT_TIME_ON)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEW_LIGHT_TIME_OFF)->EnableWindow(FALSE);
	GetDlgItem(ID_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEXT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEXT8)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEXT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIGHTS1)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIGHTS2)->EnableWindow(FALSE);
	GetDlgItem(IDC_TEXT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_SMP_FREQ)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_MAX_DOSAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CR10_MAX_DOSAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEW_MAX_DOSAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOSE_UNITS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MOISTURE_READING)->EnableWindow(FALSE);
	GetDlgItem(IDC_LAST_SMP_AVERAGE)->EnableWindow(FALSE);
	

}

// This saves the values to the document
void CParamDlg::SaveValues()
{
	// this should be used to save camera interval and wetup interval...
	// it is not used to update input locations to the cr10.  
	// Update cr10 parameters function does that
	// this will be called when 'Exit' is pressed or when the growth chamber is switched.
	UpdateData();
	//pDoc->m_ControlParameters.m_CameraInterval = CTimeSpan(0,(int)m_CamInterval,0,0);
}

// Sets the text to the current language
void CParamDlg::SetStrings(BOOL updateData)
{
	if (updateData)
		UpdateData(TRUE);
	m_cwChamber.ResetContent();

	for (int i = 0; i < pDoc->nGrowthChambers; i++)
		m_cwChamber.AddString(Strings.get(IDS_CHAMBER_A+i));
	m_cwChamber.EnableWindow(pDoc->nGrowthChambers > 1);

	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_J2));

	GetDlgItem(IDC_TEXT_MOISTURE)->SetWindowText(Strings.get(IDS_J4));
	//GetDlgItem(IDC_TEXT_FANS)->SetWindowText(Strings.get(IDS_J5));
	//GetDlgItem(IDC_TEXT_LIGHTS)->SetWindowText(Strings.get(IDS_J6));
	GetDlgItem(IDC_TEXT8)->SetWindowText(Strings.get(IDS_J1));

	GetDlgItem(IDC_TEXT_LIGHTS_ON)->SetWindowText(Strings.get(IDS_J5));
	GetDlgItem(IDC_TEXT_LIGHTS_OFF)->SetWindowText(Strings.get(IDS_J6));
	
	GetDlgItem(ID_UPDATE)->SetWindowText(Strings.get(IDS_J7));
	GetDlgItem(IDC_TEXT6)->SetWindowText(Strings.get(IDS_J8));
	
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_EXIT));
		//GetDlgItem(IDC_INITIALIZATION)->SetWindowText(Strings.get(IDS_J12));
	
	//GetDlgItem(IDC_SWITCH_MODE)->SetWindowText(Strings.get(IDS_D16));//Strings.get(IDS_F3));
	GetDlgItem(IDC_LIGHTS1)->SetWindowText(Strings.get(IDS_J14));
	GetDlgItem(IDC_LIGHTS2)->SetWindowText(Strings.get(IDS_J15));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_J16));
	
	GetDlgItem(IDC_MAX_DOSAGE)->SetWindowText(Strings.get(IDS_J19));
	GetDlgItem(IDC_DOSE_UNITS)->SetWindowText(Strings.get(IDS_X2));
	GetDlgItem(IDC_LAST_SMP_AVERAGE)->SetWindowText(Strings.get(IDS_J20));
	SetWindowText(Strings.get(IDS_J3));
	int preFSFreq = m_wSMPFreq;
	m_cSMPFreq.ResetContent();
	m_cSMPFreq.AddString(Strings.get(IDS_N_FSFREQ1));
	m_cSMPFreq.AddString(Strings.get(IDS_N_FSFREQ2));
	m_wSMPFreq = preFSFreq;
	UpdateData(FALSE);
}

// This is called when the Update Button is pressed
// This saves the values to the CR10 and to the document
void CParamDlg::OnUpdate() 
{
	CWaitCursor wCursor;
	UpdateCR10Parameters();	
	SaveValues();
}

BOOL CParamDlg::PreTranslateMessage(MSG* pMsg) 
{
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


void CParamDlg::SetLocations()
{
	if (m_wChamber == 0) // chamber A
	{
		m_MoistureLocation = MOISTURE_CONTROL_A;
		m_LightOnLocation = LIGHT_ON_TIME_A;
		m_LightOffLocation = LIGHT_OFF_TIME_A;
	}
	else
	{
		m_MoistureLocation = MOISTURE_CONTROL_B;
		m_LightOnLocation = LIGHT_ON_TIME_B;
		m_LightOffLocation = LIGHT_OFF_TIME_B;
	}
}


BOOL CParamDlg::CloseCurrentChamber()
{

	if (m_CanUpdateCR10 && (m_Moisture!=m_CR10Moisture||m_LightOn!=m_CR10LightOn||m_LightOff!=m_CR10LightOff)) 
	{
		int result = MessageBox(IDS_M_UPDATE_VALUES_NOW, IDS_J0, MB_YESNOCANCEL | MB_ICONQUESTION );
		if (result == IDYES)
		{
			return UpdateCR10Parameters();
		}
		else if (result == IDNO)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CParamDlg::OnLights1() 
{
	// TODO: Add your control notification handler code here
	// Turn lights on / off
	m_24Hour = FALSE;
	UpdateLightSettings(m_24Hour);
}

void CParamDlg::OnLights2() 
{
	// TODO: Add your control notification handler code here
	// Leave lights on 24 hrs
	m_24Hour = TRUE;
	UpdateLightSettings(m_24Hour);
}

void CParamDlg::UpdateLightSettings(BOOL In24HourMode)
{
	((CButton*)GetDlgItem(IDC_LIGHTS1))->SetCheck(!In24HourMode);
	((CButton*)GetDlgItem(IDC_LIGHTS2))->SetCheck(In24HourMode);

	GetDlgItem(IDC_TEXT8)->EnableWindow(!In24HourMode);	
	GetDlgItem(IDC_TEXT_LIGHTS_ON)->EnableWindow(!In24HourMode);
	GetDlgItem(IDC_TEXT_LIGHTS_OFF)->EnableWindow(!In24HourMode);
	GetDlgItem(IDC_CR10_LIGHT_TIME_ON)->EnableWindow(!In24HourMode);
	GetDlgItem(IDC_CR10_LIGHT_TIME_OFF)->EnableWindow(!In24HourMode);
	GetDlgItem(IDC_NEW_LIGHT_TIME_ON)->EnableWindow(!In24HourMode);
	GetDlgItem(IDC_NEW_LIGHT_TIME_OFF)->EnableWindow(!In24HourMode);


}
