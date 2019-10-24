// This is Version 1.0 PLEASE DOCUMENT CHANGES
// LadaTest.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "Lada Control ModuleDoc.h"
#include "LadaTest.h"
#include "CommOperations.h"
#include "ManualSample.h"
#include "SystemDiagDlg.h"
#include "LString.h"
#include "LadaStrings.h"
#include "inputlocations.h"
#include "LadaTest2.h"
#include "measurewater.h"
//#include "pumpcheck1.h"
//#include "pumpcheck2.h"
#include "ladaSetupDlg.h"
// Times
#define ONE_SECOND				1000
#define TWENTY_SECONDS			20000
#define THIRTY_SECONDS			30000
#define ONE_MINUTE				60000
#define TEN_MINUTES				180000

// Timers
#define EVERY_SECOND					99
#define LIGHTS_ON_ONE_MINUTE			0
#define FANS_ON_ONE_MINUTE				1
#define LIGHTS_AND_FANS_ON_ONE_MINUTE	2
#define LIGHTS_ON_10_MINUTES			3
#define PUMP1_ON1						4
#define PUMP1_OFF1						5
#define PUMP1_ON2						6
#define PUMP2_ON1						7
#define PUMP2_OFF1						8
#define PUMP2_ON2						9

// Steps
#define LIGHTS_ONE_MINUTE			0
#define FANS_ONE_MINUTE				1
#define LIGHTS_AND_FANS_ONE_MINUTE	2
#define MANUAL_SAMPLE				3
#define LIGHTS_TEN_MINUTES			4
#define DISPLAY_VALUES				5
#define PUMP1_TEST					6
#define PUMP2_TEST          		7
#define FINISHED					8

// Doing
#define LIGHTS_ON				0
#define LIGHTS_FANS_ON			0
#define FANS_ON					1
#define PUMP1_ON				2
#define PUMP1_OFF				3
#define PUMP2_ON				4
#define PUMP2_OFF				5
#define ALL_OFF					6

// Other
#define DOING_BASE				IDS_R33

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CString ValueToString(double value, int dPlaces=2, BOOL applyLanguage = FALSE);	// Changes a value to a String with dPlaces numbers after the decimal
extern LString Strings;										// Strings holds all the information for the strings of both languages
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK); // Message Boxes
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);		// Message Boxes
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);				// Message Boxes
#undef MessageBox
#define MessageBox MyMessageBox

extern CFont RussianArial;								// The font used
extern void SetItemFont(UINT controlID, CWnd *window);		// Sets an item to a font

/////////////////////////////////////////////////////////////////////////////
// LadaTest dialog

// Constructor
// Sets initial Data to 0
// doc is the current document
// prin is the data for checkout
LadaTest::LadaTest(CLADAControlModuleDoc* doc,CCheckout* prin,BOOL isauto,CWnd* pParent /*=NULL*/)
	: CDialog(LadaTest::IDD, pParent)
{
	step=LIGHTS_ONE_MINUTE;
	Doing=LIGHTS_ON;
	IsAutomatic=isauto;
	print=prin;
	pDoc=doc;
	//{{AFX_DATA_INIT(LadaTest)
	m_cv1 = _T("");
	m_cv14 = _T("");
	m_cv2 = _T("");
	m_uv1 = _T("");
	m_uv2 = _T("");
	m_uv14 = 0.0;
	m_cv13 = _T("");
	m_uv13 = 0.0;
	//}}AFX_DATA_INIT
}

// Data Exchange
void LadaTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LadaTest)
	DDX_Control(pDX, IDC_COMMENTS, m_ccomments);
	DDX_Text(pDX, IDC_CV14, m_cv14);
	DDX_Text(pDX, IDC_CV2, m_cv2);
	DDX_Text(pDX, IDC_UV2, m_uv2);
	DDX_Text(pDX, IDC_UV14, m_uv14);
	DDX_Text(pDX, IDC_CV13, m_cv13);
	DDX_Text(pDX, IDC_UV13, m_uv13);
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(LadaTest, CDialog)
	//{{AFX_MSG_MAP(LadaTest)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LadaTest message handlers

// Does initial setup
// Sets Fonts and Text, starts test (two timers)
BOOL LadaTest::OnInitDialog() 
{
	Doing=LIGHTS_ON;
	step=LIGHTS_ONE_MINUTE;
	CDialog::OnInitDialog();
	SetFont(&RussianArial);

	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDC_TEXT14,this);
	SetItemFont(IDC_TEXT15,this);
	SetItemFont(IDC_TEXT16,this);
	SetItemFont(IDC_TEXT17,this);
	SetItemFont(IDC_TEXT19,this);
	SetItemFont(IDOK,this);
	SetItemFont(IDC_STEPPROP,this);
	SetItemFont(IDC_TIME_REMAINING,this);
	SetItemFont(IDC_TIME_ELAPSED,this);
	SetItemFont(IDC_DOING,this);
	Start=CTime::GetCurrentTime();

	if (pDoc->commObject == NULL)
	{
		MessageBox("LADA Test Failed - No communication with CR10X available");
		EndDialog(IDABORT);
	}
	else
	{
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(On,On);	//Switch on Lamp and Fan
		int z=SetTimer(LIGHTS_ON_ONE_MINUTE,ONE_MINUTE,NULL);
		int y=SetTimer(EVERY_SECOND,ONE_SECOND,NULL);
		//int z = SetTimer(LIGHTS_ON_10_MINUTES,ONE_SECOND,NULL);
/*	STARTS THE FIRST STEP*/
		WillEnd=CTime::GetCurrentTime()+60;
		SetStrings();
		GetDlgItem(IDOK)->EnableWindow(false);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

// Called when a timer goes off
void LadaTest::OnTimer(UINT nIDEvent) 
{
	// This is called every second and updates the time elapsed
	if (nIDEvent==EVERY_SECOND)
	{
		CTime now;
		now=CTime::GetCurrentTime();
		CTimeSpan span;
		span=now-Start;
		CString time=span.Format("%M:%S");
		Left=WillEnd-now;
		if (Left < 0)
			Left=0;
		GetDlgItem(IDC_TIME)->SetWindowText(time);
		time=Left.Format("%M:%S");
		GetDlgItem(IDC_TIME2)->SetWindowText(time);
	}

/* THIS IS THE SECOND STEP */
	// the nIDEvent is set to the step that has just completed
	else if (nIDEvent==LIGHTS_ON_ONE_MINUTE)
	{
		KillTimer(LIGHTS_ON_ONE_MINUTE);
		GetDlgItem(IDC_CV1)->SetWindowText("60");
		GetDlgItem(IDC_UV1)->SetWindowText("60");		
		GetDlgItem(IDC_UV1)->SetFocus();
		step=FANS_ONE_MINUTE;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
		Doing=FANS_ON;		
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(Off);//,On);	// Switches off the lamp
		
		WillEnd=CTime::GetCurrentTime()+60;
		SetTimer(FANS_ON_ONE_MINUTE,ONE_MINUTE,NULL);
		
	}

/* THIS IS THE THIRD STEP*/
	else if (nIDEvent==FANS_ON_ONE_MINUTE)
	{
		KillTimer(FANS_ON_ONE_MINUTE);
		LadaTest2 tDlg(pDoc,print,IsAutomatic);
		tDlg.DoModal();

		GetDlgItem(IDC_CV2)->SetWindowText("60");
		GetDlgItem(IDC_UV2)->SetWindowText("60");
		GetDlgItem(IDC_UV2)->SetFocus();
		step=LIGHTS_AND_FANS_ONE_MINUTE;
		//pDoc->commObject->ControlCR10(On);//,On);	// Switches on the lamp				
		Doing=ALL_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		step=MANUAL_SAMPLE;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));		
		pDoc->commObject->ControlCR10(NoChange,Off);	// Switches the lamp and fans off
		// Retrieves values from the CR10 and displays them		
		CManualSample dlg(pDoc,IsAutomatic,print);
		dlg.DoModal();									// Do Manual Sample			
		SetStrings();
		step=LIGHTS_TEN_MINUTES;		
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));	
		Doing=LIGHTS_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
			pDoc->commObject->ControlCR10(On,On);	// Turns on the light and fans for 10 minutes
		WillEnd=CTime::GetCurrentTime()+180;
		SetTimer(LIGHTS_ON_10_MINUTES,TEN_MINUTES,NULL);
	}

/* THIS IS THE FOURTH STEP*/
	else if (nIDEvent==LIGHTS_ON_10_MINUTES)
	{
		KillTimer(LIGHTS_ON_10_MINUTES);
		step=DISPLAY_VALUES;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
		Doing=ALL_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));	
		
		pDoc->commObject->ControlCR10(Off,Off);
		Sleep(50); //for a buffer between commands
		int InputList[] = { CA_TOP_L, CA_MID_L, CA_BOT_L };

		double returnData[3];
		CSystemDiagDlg sdlg(pDoc, -1, FALSE, InputList, 3, returnData,IsAutomatic,FALSE);
		sdlg.DoModal();								// Displays values from CR10 and records them
		SetStrings();
		print->data[37][1]=ValueToString(returnData[0],2);
		print->data[38][1]=ValueToString(returnData[1],2);
		print->data[39][1]=ValueToString(returnData[2],2);
		//print->data[28][1]=ValueToString(returnData[3],2);
		//print->data[29][1]=ValueToString(returnData[4],2);
		//print->data[30][1]=ValueToString(returnData[5],2);
		//print->data[31][1]=ValueToString(returnData[6],2);
				
		/* THIS IS THE FIFTH STEP */
		/* IF THIS IS NOT IN AUTOMATIC MODE */
		if (!IsAutomatic)
		{
			int location = IL_WATER_PUMPED;
			for (int wTry = 0; wTry < 5 && !pDoc->GetInputLocations(&location, 1, &lastVolumePumped,9); wTry++);
			if (wTry == 5)
				MessageBox(IDS_M_FAILED_PUMP_READ);
			
			CLADASetupDlg dlg(Pump1,pDoc);
			dlg.DoModal();
			SetStrings();
		}
		step=PUMP1_TEST;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
		Doing=PUMP1_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
			
		pDoc->commObject->ControlCR10(NoChange,NoChange,On);					// Turn on pump 1
		WillEnd=CTime::GetCurrentTime()+30;
		SetTimer(PUMP1_ON1,THIRTY_SECONDS,NULL);		

	}
/* THIS IS THE SIXTH STEP */
	else if (nIDEvent == PUMP1_ON1 )
	{ // PUMP1_ON1 IS NOW OVER...
		KillTimer(PUMP1_ON1);
		// DISPLAY NEXT STEP, GET IT STARTED
		Doing=PUMP1_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(NoChange,NoChange,Off);// Turn off pump 1	
		
		if (IsAutomatic)
		{
			// this is the pump test in automatic checkout
			if (MessageBox(IDS_M_PUMP1_WORKED,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
			{
				// WRITE SOME MESSAGE?  COSMONAUT ACKNOWLEDGED THAT PUMP 1 WORKED...
			}
			SetStrings();
			step=PUMP2_TEST;
			GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
			Doing=PUMP2_ON;
			GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
			pDoc->commObject->ControlCR10(NoChange,NoChange,NoChange,On);				// Turns on pump 2
			WillEnd=CTime::GetCurrentTime()+30;
			SetTimer(PUMP2_ON1,THIRTY_SECONDS,NULL);
			return;
		}

		WillEnd=CTime::GetCurrentTime()+30;
		SetTimer(PUMP1_OFF1,THIRTY_SECONDS,NULL);
	}
	else if (nIDEvent == PUMP1_OFF1 )
	{ // PUMP1_OFF1 IS NOW OVER...
		KillTimer(PUMP1_OFF1);
		// DISPLAY NEXT STEP, GET IT STARTED
		Doing=PUMP1_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(NoChange,NoChange,On);// Turn off pump 1	
		WillEnd=CTime::GetCurrentTime()+30;
		SetTimer(PUMP1_ON2,THIRTY_SECONDS,NULL);
	}
	else if (nIDEvent == PUMP1_ON2 )
	{ // PUMP1_ON2 IS NOW OVER...
		KillTimer(PUMP1_ON2);
		// DISPLAY NEXT STEP, GET IT STARTED
		Doing=PUMP1_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(NoChange,NoChange,Off);// Turn off pump 1	
// pump 1 test is now over	
		
		// Displays the amount of water pumped by pump 1
		m_uv13 = 0;
		if (!IsAutomatic)
		{
			CMeasureWater mDlg("", &m_uv13);
			mDlg.DoModal();
			SetStrings();
			GetDlgItem(IDC_UV13)->SetWindowText(ValueToString(m_uv13,2));
		}

		int location = IL_WATER_PUMPED;
		double vPumped;
		for (int wTry = 0; wTry < 5 && !pDoc->GetInputLocations(&location, 1, &vPumped,9); wTry++);
		if (wTry == 5)
			MessageBox(IDS_M_FAILED_PUMP_READ);
		// Gets the amount of water pumped by pump 1
		m_uv13 = pump1 = vPumped-lastVolumePumped;
		GetDlgItem(IDC_CV13)->SetWindowText(ValueToString(pump1,2));
		lastVolumePumped = vPumped;

/* THIS IS THE SEVENTH STEP */
		//if (!IsAutomatic)
		//MessageBox(IDS_M_PUMP2_READY, IDS_PROGRAM_NAME, MB_OKCANCEL);
		//MessageBox("Please place the monitor pump switch to position \"Monitor Pump 2\".  Also, connect a water supply tube to \"In 2\" and a water outlet tube to \"Out 2\"");
		CLADASetupDlg dlg(Pump2,pDoc);
		dlg.DoModal();
		step=PUMP2_TEST;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
		Doing=PUMP2_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(NoChange,NoChange,NoChange,On);				// Turns on pump 2
		WillEnd=CTime::GetCurrentTime()+30;
		SetTimer(PUMP2_ON1,THIRTY_SECONDS,NULL);
	}
	else if (nIDEvent == PUMP2_ON1 )
	{ // PUMP2_ON1 IS NOW OVER...
		KillTimer(PUMP2_ON1);
		// DISPLAY NEXT STEP, GET IT STARTED
		Doing=PUMP2_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(NoChange,NoChange,NoChange,Off);// Turn off pump 1	
		
		if (IsAutomatic)
		{
			// this is the pump test in automatic checkout
			if (MessageBox(IDS_M_PUMP2_WORKED,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
			{
				// WRITE SOME MESSAGE?  COSMONAUT ACKNOWLEDGED THAT PUMP 1 WORKED...
			}
			SetStrings();
			AllStepsComplete();
			return;
		}

		WillEnd=CTime::GetCurrentTime()+30;
		SetTimer(PUMP2_OFF1,THIRTY_SECONDS,NULL);
	}
	else if (nIDEvent == PUMP2_OFF1 )
	{ // PUMP2_OFF1 IS NOW OVER...
		KillTimer(PUMP2_OFF1);
		// DISPLAY NEXT STEP, GET IT STARTED
		Doing=PUMP2_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(NoChange,NoChange,NoChange,On);// Turn off pump 1	
		WillEnd=CTime::GetCurrentTime()+30;
		SetTimer(PUMP2_ON2,THIRTY_SECONDS,NULL);
	}
	else if (nIDEvent == PUMP2_ON2 )
	{ // PUMP2_ON2 IS NOW OVER...
		KillTimer(PUMP2_ON2);
		// DISPLAY NEXT STEP, GET IT STARTED
		Doing=PUMP2_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(NoChange,NoChange,NoChange,Off);// Turn off pump 1	
// pump test 2 is now over
		m_uv14 = 0;	
		if (!IsAutomatic)
		{
			CMeasureWater mDlg("", &m_uv14);
			mDlg.DoModal();
			SetStrings();
			GetDlgItem(IDC_UV14)->SetWindowText(ValueToString(m_uv14,2));
		}
		int location = IL_WATER_PUMPED;
		double vPumped;
		for (int wTry = 0; wTry < 5 && !pDoc->GetInputLocations(&location, 1, &vPumped,9); wTry++);
		if (wTry == 5)
			MessageBox(IDS_M_FAILED_PUMP_READ);
		SetStrings();
		// Gets the amount of water pumped by pump 2
		m_uv14 = pump2 = vPumped-lastVolumePumped;
		lastVolumePumped = vPumped;

		GetDlgItem(IDC_CV14)->SetWindowText(ValueToString(pump2,2));		// Displays the amount of water pumped by pump 1
		
// THIS IS THE FINAL STEP	
		AllStepsComplete();
	}

}

// Gets the requested input location and return the value
double LadaTest::get(int loc)
{
	double ret;
	pDoc->GetInputLocations(&loc,1,&ret,11);
	return ret;
}

// stores all information in print and exits
void LadaTest::OnOK() 
{
	UpdateData(TRUE);
	
	print->data[28][1]=ValueToString(pump1);
	print->data[29][1]=ValueToString(pump2);
	print->data[28][2]=ValueToString(m_uv13);
	print->data[29][2]=ValueToString(m_uv14);
	print->data[36][2]=m_uv2;
	print->data[40][2]=m_uv1;
	print->data[36][1]=m_cv2;
	print->data[40][1]=m_cv1;
	print->data[2][1]=ValueToString(get(57),2);
	//print->data[37][1]=ValueToString(pDoc->m_ControlParameters.m_CameraInterval.GetTotalHours());
	print->data[23][1]=(pDoc->m_WetupInfo.m_BurstFreq);
	m_ccomments.GetWindowText(print->data[47][1]);
	pDoc->commObject->SetFlag(3,TRUE);			//Allows CR10 to return to automatic mode		
	CDialog::OnOK();
}


// Sets the text to the current language
void LadaTest::SetStrings()
{
	SetWindowText(Strings.get(IDS_R0));
//	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_R4));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_R5));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_R6));
	GetDlgItem(IDC_TEXT16)->SetWindowText(Strings.get(IDS_R16));
	GetDlgItem(IDC_TEXT17)->SetWindowText(Strings.get(IDS_R17));
	GetDlgItem(IDC_TEXT19)->SetWindowText(Strings.get(IDS_R18));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
	GetDlgItem(IDC_TIME_REMAINING)->SetWindowText(Strings.get(IDS_R20));
	GetDlgItem(IDC_TIME_ELAPSED)->SetWindowText(Strings.get(IDS_R32));
	GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
	GetDlgItem(IDC_TEXT14)->SetWindowText(Strings.get(IDS_R2));
	GetDlgItem(IDC_TEXT15)->SetWindowText(Strings.get(IDS_R3));

}

BOOL LadaTest::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
			Strings.ToggleLanguage();
			SetStrings();
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void LadaTest::AllStepsComplete()
{
	// Ends Communication			
	GetDlgItem(IDOK)->EnableWindow(true);
		
	step=FINISHED;
	GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
	Doing=ALL_OFF;
	GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		
	if (IsAutomatic)
		OnOK();
}
