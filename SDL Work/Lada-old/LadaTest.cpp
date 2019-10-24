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
// Times
#define ONE_SECOND				1000
#define TWENTY_SECONDS			20000
#define ONE_MINUTE				60000
#define TEN_MINUTES				600000

// Timers
#define EVERY_SECOND					10
#define LIGHTS_ON_ONE_MINUTE			0
#define FANS_ON_ONE_MINUTE				1
#define LIGHTS_AND_FANS_ON_ONE_MINUTE	2
#define LIGHTS_ON_10_MINUTES			3
#define PUMP1_FIRST_TEST				4
//#define PUMP1_DELAY						5
#define PUMP1_SECOND_TEST				5
#define PUMP2_FIRST_TEST				6
//#define PUMP2_DELAY						
#define PUMP2_SECOND_TEST				7

// Steps
#define LIGHTS_ONE_MINUTE			0
#define FANS_ONE_MINUTE				1
#define LIGHTS_AND_FANS_ONE_MINUTE	2
#define MANUAL_SAMPLE				3
#define LIGHTS_TEN_MINUTES			4
#define DISPLAY_VALUES				5
#define PUMP1_ONE_MINUTE			6
#define PUMP1_THREE_MINUTES			7
#define PUMP2_ONE_MINUTE			8
#define PUMP3_THREE_MINUTES			9
#define FINISHED					10

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
	m_cv10 = _T("");
	m_cv11 = _T("");
	m_cv12 = _T("");
	m_cv13 = _T("");
	m_cv14 = _T("");
	m_cv2 = _T("");
	m_cv3 = _T("");
	m_cv4 = _T("");
	m_cv5 = _T("");
	m_cv6 = _T("");
	m_cv7 = _T("");
	m_cv8 = _T("");
	m_cv9 = _T("");
	m_uv1 = _T("");
	m_uv10 = _T("");
	m_uv11 = _T("");
	m_uv12 = _T("");
	m_uv13 = _T("");
	m_uv14 = _T("");
	m_uv2 = _T("");
	m_uv3 = _T("");
	m_uv4 = _T("");
	m_uv5 = _T("");
	m_uv6 = _T("");
	m_uv7 = _T("");
	m_uv8 = _T("");
	m_uv9 = _T("");
	//}}AFX_DATA_INIT
}

// Data Exchange
void LadaTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LadaTest)
	DDX_Control(pDX, IDC_COMMENTS, m_ccomments);
	DDX_Text(pDX, IDC_CV1, m_cv1);
	DDX_Text(pDX, IDC_CV10, m_cv10);
	DDX_Text(pDX, IDC_CV11, m_cv11);
	DDX_Text(pDX, IDC_CV12, m_cv12);
	DDX_Text(pDX, IDC_CV13, m_cv13);
	DDX_Text(pDX, IDC_CV14, m_cv14);
	DDX_Text(pDX, IDC_CV2, m_cv2);
	DDX_Text(pDX, IDC_CV3, m_cv3);
	DDX_Text(pDX, IDC_CV4, m_cv4);
	DDX_Text(pDX, IDC_CV5, m_cv5);
	DDX_Text(pDX, IDC_CV6, m_cv6);
	DDX_Text(pDX, IDC_CV7, m_cv7);
	DDX_Text(pDX, IDC_CV8, m_cv8);
	DDX_Text(pDX, IDC_CV9, m_cv9);
	DDX_Text(pDX, IDC_UV1, m_uv1);
	DDX_Text(pDX, IDC_UV10, m_uv10);
	DDX_Text(pDX, IDC_UV11, m_uv11);
	DDX_Text(pDX, IDC_UV12, m_uv12);
	DDX_Text(pDX, IDC_UV13, m_uv13);
	DDX_Text(pDX, IDC_UV14, m_uv14);
	DDX_Text(pDX, IDC_UV2, m_uv2);
	DDX_Text(pDX, IDC_UV3, m_uv3);
	DDX_Text(pDX, IDC_UV4, m_uv4);
	DDX_Text(pDX, IDC_UV5, m_uv5);
	DDX_Text(pDX, IDC_UV6, m_uv6);
	DDX_Text(pDX, IDC_UV7, m_uv7);
	DDX_Text(pDX, IDC_UV8, m_uv8);
	DDX_Text(pDX, IDC_UV9, m_uv9);
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
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDC_TEXT4,this);
	SetItemFont(IDC_TEXT5,this);
	SetItemFont(IDC_TEXT6,this);
	SetItemFont(IDC_TEXT7,this);
	SetItemFont(IDC_TEXT8,this);
	SetItemFont(IDC_TEXT9,this);
	SetItemFont(IDC_TEXT10,this);
	SetItemFont(IDC_TEXT11,this);
	SetItemFont(IDC_TEXT12,this);
	SetItemFont(IDC_TEXT13,this);
	SetItemFont(IDC_TEXT14,this);
	SetItemFont(IDC_TEXT15,this);
	SetItemFont(IDC_TEXT16,this);
	SetItemFont(IDC_TEXT17,this);
//	SetItemFont(IDC_TEXT18,this);
	SetItemFont(IDC_TEXT19,this);
	SetItemFont(IDOK,this);
	SetItemFont(IDC_STEP,this);
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
		pDoc->commObject->ControlCR10(On,On,Off,Off);	//Switch on Lamp and Fan
		int z=SetTimer(LIGHTS_ON_ONE_MINUTE,ONE_MINUTE,NULL);
		int y=SetTimer(EVERY_SECOND,ONE_SECOND,NULL);

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
		pDoc->commObject->ControlCR10(Off,On,Off,Off);	// Switches off the lamp		
		WillEnd=CTime::GetCurrentTime()+60;
		SetTimer(FANS_ON_ONE_MINUTE,ONE_MINUTE,NULL);
		
	}

/* THIS IS THE THIRD STEP*/
	else if (nIDEvent==FANS_ON_ONE_MINUTE)
	{
		KillTimer(FANS_ON_ONE_MINUTE);
		GetDlgItem(IDC_CV2)->SetWindowText("60");
		GetDlgItem(IDC_UV2)->SetWindowText("60");
		GetDlgItem(IDC_UV2)->SetFocus();
		step=LIGHTS_AND_FANS_ONE_MINUTE;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
		Doing=LIGHTS_FANS_ON;				
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(On,On,Off,Off);	// Switches on the lamp				
		WillEnd=CTime::GetCurrentTime()+60;
		SetTimer(LIGHTS_AND_FANS_ON_ONE_MINUTE,ONE_MINUTE,NULL);
	}

/* THIS IS THE THIRD STEP*/
	else if (nIDEvent==LIGHTS_AND_FANS_ON_ONE_MINUTE)
	{
		KillTimer(LIGHTS_AND_FANS_ON_ONE_MINUTE);
		GetDlgItem(IDC_CV3)->SetWindowText("60");
		GetDlgItem(IDC_UV3)->SetWindowText("60");
		GetDlgItem(IDC_UV3)->SetFocus();
		Doing=ALL_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		step=MANUAL_SAMPLE;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));		
		pDoc->commObject->ControlCR10(Off,Off,Off,Off);	// Switches the lamp and fans off
		// Retrieves values from the CR10 and displays them		
		GetDlgItem(IDC_CV4)->SetWindowText(ValueToString(get(IAirTemp)));
		GetDlgItem(IDC_CV5)->SetWindowText(ValueToString(get(IBallTemp)));
		GetDlgItem(IDC_CV6)->SetWindowText(ValueToString(get(ILeaf1)));
		GetDlgItem(IDC_CV7)->SetWindowText(ValueToString(get(ILeaf2)));
		GetDlgItem(IDC_CV8)->SetWindowText(ValueToString(get(ILeaf3)));
		GetDlgItem(IDC_CV9)->SetWindowText(ValueToString(get(ILeaf4)));
		GetDlgItem(IDC_CV10)->SetWindowText(ValueToString(get(ILeaf1)));
		GetDlgItem(IDC_CV11)->SetWindowText(ValueToString(get(ILeafSurface)));
		GetDlgItem(IDC_CV12)->SetWindowText(ValueToString(get(IHumOut)));

		GetDlgItem(IDC_UV4)->SetWindowText(ValueToString(get(IAirTemp)));
		GetDlgItem(IDC_UV5)->SetWindowText(ValueToString(get(IBallTemp)));
		GetDlgItem(IDC_UV6)->SetWindowText(ValueToString(get(ILeaf1)));
		GetDlgItem(IDC_UV7)->SetWindowText(ValueToString(get(ILeaf2)));
		GetDlgItem(IDC_UV8)->SetWindowText(ValueToString(get(ILeaf3)));
		GetDlgItem(IDC_UV9)->SetWindowText(ValueToString(get(ILeaf4)));
		GetDlgItem(IDC_UV10)->SetWindowText(ValueToString(get(ILeaf1)));
		GetDlgItem(IDC_UV11)->SetWindowText(ValueToString(get(ILeafSurface)));
		GetDlgItem(IDC_UV12)->SetWindowText(ValueToString(get(IHumOut)));
		CManualSample dlg(pDoc,IsAutomatic,print);
		dlg.DoModal();									// Do Manual Sample			
		SetStrings();
		step=LIGHTS_TEN_MINUTES;		
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));	
		Doing=LIGHTS_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(On,On,Off,Off);	// Turns on the light and fans for 10 minutes
		WillEnd=CTime::GetCurrentTime()+600;
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
		int listSize = 12;
		int * InputList = new int[listSize];
		InputList[0] = CA_TOP_L;
		InputList[1] = CA_MID_L;
		InputList[2] = CA_BOT_L;
		InputList[3] = CA_O2_1;
		InputList[4] = CA_O2_2;
		InputList[5] = CA_O2_3;
		InputList[6] = CA_O2_4;
		InputList[7] = ABS_TENSIOMETER;
		InputList[8] = TENSIOMETER_1; // tensiometers
		InputList[9] = TENSIOMETER_2;
		InputList[10] = TENSIOMETER_3;
		InputList[11] = TENSIOMETER_4;
		double * returnData = new double[listSize];
		CSystemDiagDlg sdlg(pDoc, -1, FALSE, InputList, listSize, returnData,IsAutomatic,FALSE);
		sdlg.DoModal();								// Displays values from CR10 and records them
		SetStrings();
		print->data[32][1]=ValueToString(returnData[0],2);
		print->data[33][1]=ValueToString(returnData[1],2);
		print->data[34][1]=ValueToString(returnData[2],2);
		print->data[19][1]=ValueToString(returnData[3],2);
		print->data[20][1]=ValueToString(returnData[4],2);
		print->data[21][1]=ValueToString(returnData[5],2);
		print->data[22][1]=ValueToString(returnData[6],2);
		delete [] InputList;
		delete [] returnData;

/* THIS IS THE FIFTH STEP */
		/* IF THIS IS NOT IN AUTOMATIC MODE */
		if (!IsAutomatic)
			MessageBox(IDS_M_PUMP1_READY, IDS_PROGRAM_NAME, MB_OK);		
		step=PUMP1_ONE_MINUTE;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
		Doing=PUMP1_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->SetLocationAndVerify(IL_WATER_PUMPED,pump,"0"); // set water pumped to zero
		pDoc->commObject->ControlCR10(Off,Off,On,Off);					// Turn on pump 1
		WillEnd=CTime::GetCurrentTime()+60;
		SetTimer(PUMP1_FIRST_TEST,ONE_MINUTE,NULL);			

	}
/* THIS IS THE SIXTH STEP */
	else if (nIDEvent==PUMP1_FIRST_TEST)													// Measure the Water, and continue to pump
	{
		KillTimer(PUMP1_FIRST_TEST);
		Doing=PUMP1_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(Off,Off,Off,Off);// Turn off pump 1	
		if (!IsAutomatic)
			MessageBox(IDS_M_MEASURE_WATER, IDS_PROGRAM_NAME);
		step=PUMP1_THREE_MINUTES;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
		Doing=PUMP1_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(Off,Off,On,Off);						// Turn on pump 1
		WillEnd=CTime::GetCurrentTime()+180;
		SetTimer(PUMP1_SECOND_TEST,TWENTY_SECONDS,NULL);
	}
	else if (nIDEvent==PUMP1_SECOND_TEST)		// Checks this every 20 seconds and runs the pump for 20 seconds every minute for 3 minutes
	{
		static int x=0;
		x++;
		if ((x%3)==0)
		{
			Doing=PUMP1_ON;
			pDoc->commObject->ControlCR10(Off,Off,On,Off);					// Turn on pump 1
			GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		}
		else if(((x-1)%3)==0)
		{
			Doing=PUMP1_OFF;
			pDoc->commObject->ControlCR10(Off,Off,Off,Off);					// Turn off pump 1
			GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		}
/* THIS IS CALLED WHEN PUMP 1.2 IS FINISHED */
/* THIS IS THE SEVENTH STEP */
		if (x>=9)
		{
			x=0;
			KillTimer(PUMP1_SECOND_TEST);
			pDoc->commObject->ControlCR10(Off,Off,Off,Off);					// Turn off pump 1			
			int location = IL_WATER_PUMPED;
			pDoc->GetInputLocations(&location, 1, &pump);						// Gets the amount of water pumped by pump 1
			GetDlgItem(IDC_CV13)->SetWindowText(ValueToString(pump,2));		// Displays the amount of water pumped by pump 1
			GetDlgItem(IDC_UV13)->SetWindowText(ValueToString(pump,2));
			GetDlgItem(IDC_UV13)->SetFocus();			
			pDoc->commObject->SetLocationAndVerify(IL_WATER_PUMPED, pump, "0", 3); // Sets the water pumped to 0
			if (!IsAutomatic)
				MessageBox(IDS_M_PUMP2_READY, IDS_PROGRAM_NAME, MB_OKCANCEL);
			step=PUMP2_ONE_MINUTE;
			GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
			Doing=PUMP2_ON;
			GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
			pDoc->commObject->ControlCR10(Off,Off,Off,On);				// Turns on pump 2
			WillEnd=CTime::GetCurrentTime()+60;
			SetTimer(PUMP2_FIRST_TEST,ONE_MINUTE,NULL);				
		}
		
	}

/* THIS IS THE EIGHTH STEP */
	else if (nIDEvent==PUMP2_FIRST_TEST)
	{
		KillTimer(PUMP2_FIRST_TEST);
				pDoc->commObject->ControlCR10(Off,Off,Off,Off);			// Turn off pump 2
		Doing=PUMP2_OFF;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		if (!IsAutomatic)
			MessageBox(IDS_M_MEASURE_WATER, IDS_PROGRAM_NAME);					// Measure pump 2 water
		step=PUMP3_THREE_MINUTES;
		GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
		Doing=PUMP2_ON;
		GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		pDoc->commObject->ControlCR10(Off,Off,Off,On);			// Turn on pump 2
		WillEnd=CTime::GetCurrentTime()+180;
		SetTimer(PUMP2_SECOND_TEST,TWENTY_SECONDS,NULL);

	}
	
/* THIS IS THE NINTH STEP */	
	else if (nIDEvent==PUMP2_SECOND_TEST)
	{
		static int x=0;
		x++;
		if ((x%3)==0)
		{
			pDoc->commObject->ControlCR10(Off,Off,Off,On);					// Turn on pump 2
			Doing=PUMP2_ON;
			GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		}
		else if(((x-1)%3)==0)
		{
			pDoc->commObject->ControlCR10(Off,Off,Off,Off);					// Turn off pump 2
			Doing=PUMP2_OFF;
			GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
		}
		if (x>=9)
		{
			x=0;
			KillTimer(EVERY_SECOND);
			KillTimer(PUMP2_SECOND_TEST);
			pDoc->commObject->ControlCR10(Off,Off,Off,Off);					// Turns off pump 2
			pDoc->commObject->ExecuteICommand(IL_WATER_PUMPED, pump, NULL, 3);	// Gets the water pumped by pump 2
			GetDlgItem(IDC_CV14)->SetWindowText(ValueToString(pump,2));		// Displays the water pumped by pump 2
												// Ends Communication			
			GetDlgItem(IDOK)->EnableWindow(true);
			GetDlgItem(IDC_UV14)->SetFocus();
			step=FINISHED;
			GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
			Doing=ALL_OFF;
			GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));
			if (IsAutomatic)
				OnOK();
		}
	}

}

// Gets the requested input location and return the value
double LadaTest::get(int loc)
{
	double ret;
	pDoc->GetInputLocations(&loc,1,&ret);
	return ret;
}

// stores all information in print and exits
void LadaTest::OnOK() 
{
	UpdateData(TRUE);
	print->data[24][1]=(m_cv13+m_cv14,2);
	print->data[25][1]=(m_cv6,2);
	print->data[26][1]=(m_cv7,2);
	print->data[27][1]=(m_cv8,2);
	print->data[28][1]=(m_cv9,2);
	print->data[25][2]=(m_uv6,2);
	print->data[24][2]=(m_uv13+m_uv14,2);
	print->data[26][2]=(m_uv7,2);
	print->data[27][2]=(m_uv8,2);
	print->data[28][2]=(m_uv9,2);
	print->data[29][2]=(m_uv11,2);
	print->data[30][2]=(m_uv12,2);
	print->data[31][2]=(m_uv2,2);
	print->data[35][2]=(m_uv1,2);
	print->data[29][1]=(m_cv11,2);
	print->data[30][1]=(m_cv12,2);
	print->data[31][1]=(m_cv2,2);
	print->data[35][1]=(m_cv1,2);
	print->data[2][1]=(get(57),2);
	//print->data[41][1]=ValueToString(pDoc->m_ControlParameters.m_CameraInterval.GetTotalHours());
	print->data[23][1]=(pDoc->m_WetupInfo.m_BurstFreq);
	m_ccomments.GetWindowText(print->data[42][1]);
	pDoc->commObject->SetFlag(3,TRUE);			//Allows CR10 to return to automatic mode		
	CDialog::OnOK();
}


// Sets the text to the current language
void LadaTest::SetStrings()
{
	SetWindowText(Strings.get(IDS_R0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_R4));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_R5));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_R6));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_R7));
	GetDlgItem(IDC_TEXT5)->SetWindowText(Strings.get(IDS_R8));
	GetDlgItem(IDC_TEXT6)->SetWindowText(Strings.get(IDS_R9));
	GetDlgItem(IDC_TEXT7)->SetWindowText(Strings.get(IDS_R10));
	GetDlgItem(IDC_TEXT8)->SetWindowText(Strings.get(IDS_R11));
	GetDlgItem(IDC_TEXT9)->SetWindowText(Strings.get(IDS_R12));
	GetDlgItem(IDC_TEXT10)->SetWindowText(Strings.get(IDS_R13));
	GetDlgItem(IDC_TEXT11)->SetWindowText(Strings.get(IDS_R14));
	GetDlgItem(IDC_TEXT12)->SetWindowText(Strings.get(IDS_R15));
	GetDlgItem(IDC_TEXT13)->SetWindowText(Strings.get(IDS_R1));
	GetDlgItem(IDC_TEXT14)->SetWindowText(Strings.get(IDS_R2));
	GetDlgItem(IDC_TEXT15)->SetWindowText(Strings.get(IDS_R3));
	GetDlgItem(IDC_TEXT16)->SetWindowText(Strings.get(IDS_R16));
	GetDlgItem(IDC_TEXT17)->SetWindowText(Strings.get(IDS_R17));
	GetDlgItem(IDC_TEXT19)->SetWindowText(Strings.get(IDS_R18));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDC_STEP)->SetWindowText(Strings.get(IDS_R19));
	GetDlgItem(IDC_STEPPROP)->SetWindowText(Strings.get(IDS_R21+step));
	GetDlgItem(IDC_TIME_REMAINING)->SetWindowText(Strings.get(IDS_R20));
	GetDlgItem(IDC_TIME_ELAPSED)->SetWindowText(Strings.get(IDS_R32));
	GetDlgItem(IDC_DOING)->SetWindowText(Strings.get(DOING_BASE+Doing));

}

BOOL LadaTest::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
			Strings.ToggleLanguage();
			SetStrings();
	}
	return CDialog::PreTranslateMessage(pMsg);
}
