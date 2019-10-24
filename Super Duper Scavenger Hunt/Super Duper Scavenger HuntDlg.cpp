// Super Duper Scavenger HuntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Super Duper Scavenger Hunt.h"
#include "Super Duper Scavenger HuntDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <fstream.h>

extern CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4);
/////////////////////////////////////////////////////////////////////////////
// CSuperDuperScavengerHuntDlg dialog

CSuperDuperScavengerHuntDlg::CSuperDuperScavengerHuntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperDuperScavengerHuntDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuperDuperScavengerHuntDlg)
	m_Answer = _T("");
	m_RiddleText = _T("");
	m_TimeLeft = _T("");
	m_AnswerText = _T("");
	m_Location = _T("");
	m_Heading = _T("");
	m_Distance = _T("");
	m_Caption = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	totalSteps = 9;
	nStepsTimeOut = 0;
	nStepsWrong = 0;
	curStep = 0;
	
	Steps[0].IsRiddle = TRUE;
	Steps[0].RiddleText = "Where is a kiss more than just a kiss...  Here it is a _________.";
	Steps[0].Answer = "rite of passage";
	Steps[0].SecondsToNextStep = 300;
	Steps[0].CompletionInfo = "Good job.  Be sure to look for a sweet treat under the 'A'.";
	Steps[0].RiddleHint = "midnight... fullmoon... school spirit... ";
	Steps[0].Location = "Wherever we drop you off...";

	Steps[1].IsRiddle = FALSE;
	Steps[1].Answer = "SAGEBRUSH";
	Steps[1].Distance = "2 1/4 inches";
	Steps[1].Heading = "200";
	Steps[1].Location = "On the 'A' by Old Main.";
	Steps[1].SecondsToNextStep = 180;
	Steps[1].RiddleHint = "look for a yellow ribbon ";


	Steps[2].IsRiddle = FALSE;
	Steps[2].Answer = "256";
	Steps[2].Distance = "2 9/16 inches";
	Steps[2].Heading = "330";
	Steps[2].Location = "In the ampitheater.";
	Steps[2].SecondsToNextStep = 180;
	Steps[2].CompletionInfo = "Good job.  Look on a door to find the next secret code.  There will be no yellow ribbon.";
	Steps[2].RiddleHint = "look for a yellow ribbon ";


	Steps[3].IsRiddle = FALSE;
	Steps[3].Answer = "Editorial Services";
	Steps[3].Distance = "1 3/16 inches";
	Steps[3].Heading = "90";
	Steps[3].Location = "At a tree near the bottom of Old Main hill.";
	Steps[3].SecondsToNextStep = 180;
	Steps[3].CompletionInfo = "Clue for your next point - dihydrogen oxide falling over rocks...";
	Steps[3].RiddleHint = "a name printed on a door";

	Steps[4].IsRiddle = FALSE;
	Steps[4].Answer = "Yo Banana Boy!";
	Steps[4].Distance = "2 1/8 inches";
	Steps[4].Heading = "333";
	Steps[4].Location = "At the building being renovated next to Old Main.";
	Steps[4].SecondsToNextStep = 300;
	Steps[4].CompletionInfo = "You're coming along well.  Before you leave make sure you find the hidden treasure.";
	Steps[4].RiddleHint = "look for a yellow ribbon ";

	Steps[5].IsRiddle = TRUE;
	Steps[5].RiddleText = "Whose magic pipe soothes the _________.";
	Steps[5].RiddleHint = "gift from Thailand... near the quad... is he smoking a pipe or playing a flute? ... There is no yellow ribbon.";
	Steps[5].Answer = "Listeners";
	Steps[5].Location = "At the waterfall across from the heating plant.";
	Steps[5].SecondsToNextStep = 420;
	Steps[5].CompletionInfo = "You can find the next answer by going to the closest thing to McDonalds on campus.  There is no yellow ribbon.";
	

	Steps[6].IsRiddle = TRUE;
	Steps[6].RiddleText = "Betwixt the french fries is a ____.";
	Steps[6].RiddleHint = "look at a sculpture on campus.";
	Steps[6].Answer = "rock";
	Steps[6].Location = "At the buddha statue next to the quad between the animal scienc and geology building.";
	Steps[6].SecondsToNextStep = 180;
	Steps[6].RiddleHint = "it's an object found all over";
	Steps[6].CompletionInfo = "The answer to your next point is a riddle.  There is no yellow ribbon.  Here is a clue - Who makes bathrooms for dogs?";

	Steps[7].IsRiddle = FALSE;
	Steps[7].Answer = "MUELLER";
	Steps[7].Distance = "2 1/8 inches";
	Steps[7].Heading = "90";
	Steps[7].Location = "In between the natural resources and biology building at a sculpture resembling french fries.";
	Steps[7].SecondsToNextStep = 180;
	Steps[7].RiddleHint = "hmm... it's red.  who made it?";
	Steps[7].CompletionInfo = "Wow.. you've made it far.  You must be close to finishing!  The next secret code is by a yellow ribbon.";

	Steps[8].IsRiddle = FALSE;
	Steps[8].Answer = "twisty slide";
	Steps[8].Distance = "3 inches";
	Steps[8].Heading = "345";
	Steps[8].Location = "At the red fire hydrant next to the SER and Engineering buildings.";
	Steps[8].SecondsToNextStep = 420;
	Steps[8].RiddleHint = "one of my favorite places as a kid... still is.  Warning: repeated use of this device may make one naseaus...";
	Steps[8].CompletionInfo = "Look for buried treasure under the ribbon!";

	ifstream fin("C:\\hunt.dat");
	fin >> curStep;
	fin >> nStepsTimeOut;
	fin >> nStepsWrong;
	time_t ftime = 0;
	fin >> ftime;
	fin.close();
	if (ftime && curStep < totalSteps)
	{
		CTime FinishTime(ftime);
		if (CTime::GetCurrentTime() > FinishTime)
			Steps[curStep].SecondsToNextStep =  0;
		else
			Steps[curStep].SecondsToNextStep = (FinishTime - CTime::GetCurrentTime()).GetTotalSeconds();

	}

}

CSuperDuperScavengerHuntDlg::~CSuperDuperScavengerHuntDlg()
{
	ofstream fout("C:\\hunt.dat");
	fout << curStep << endl;
	fout << nStepsTimeOut << endl;
	fout << nStepsWrong << endl;
	fout << stepFinishTime.GetTime();
	fout.close();
}

void CSuperDuperScavengerHuntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperDuperScavengerHuntDlg)
	DDX_Text(pDX, IDC_ANSWER, m_Answer);
	DDX_Text(pDX, IDC_RIDDLE_TEXT, m_RiddleText);
	DDX_Text(pDX, IDC_TIME_LEFT, m_TimeLeft);
	DDX_Text(pDX, IDC_ANSWER_TEXT, m_AnswerText);
	DDX_Text(pDX, IDC_LOCATION, m_Location);
	DDX_Text(pDX, IDC_HEADING, m_Heading);
	DDX_Text(pDX, IDC_DISTANCE, m_Distance);
	DDX_Text(pDX, IDC_DIRECTION_TEXT, m_Caption);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSuperDuperScavengerHuntDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperDuperScavengerHuntDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperDuperScavengerHuntDlg message handlers

BOOL CSuperDuperScavengerHuntDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (curStep >= totalSteps)
	{
		curStep = 0;
		nStepsTimeOut = 0;
		nStepsWrong = 0;
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	DisplayStep();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSuperDuperScavengerHuntDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSuperDuperScavengerHuntDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSuperDuperScavengerHuntDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Answer.MakeLower();
	CString temp = Steps[curStep].Answer;
	temp.MakeLower();
	
	if (temp == m_Answer)
	{
		// correct
		KillTimer(0);
		MessageBox("Answer correct!");
		AdvanceToNextStep();
	}
	else
	{
		if (TimeIsUp)
		{
			if (Steps[curStep].IsRiddle)
			{
				MessageBox(CString("The answer is: ") + Steps[curStep].Answer);
			}
			nStepsWrong++;
			// change the button text
			AdvanceToNextStep();
		}
		else
			MessageBox("Answer incorrect... try again.");
	}
}

void CSuperDuperScavengerHuntDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	//if (Steps[curStep].IsRiddle)
	//{
		if (Steps[curStep].RiddleHint == "")
		{
			MessageBox("No hint is available for this riddle.","Sorry",MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(Steps[curStep].RiddleHint,NULL,MB_ICONINFORMATION);
		}
	//}
	//else
	//	MessageBox("Program error... this button should not be visible if the current step is not a riddle.");
}

void CSuperDuperScavengerHuntDlg::DisplayStep()
{
	KillTimer(0);
	SetTimer(0,1000,NULL);
	TimeIsUp = FALSE;
	UINT RiddleControls = (Steps[curStep].IsRiddle) ? SW_SHOW : SW_HIDE;
	UINT PointControls = (Steps[curStep].IsRiddle) ? SW_HIDE : SW_SHOW;
	
	GetDlgItem(IDC_TEXT2)->ShowWindow(PointControls);
	GetDlgItem(IDC_TEXT3)->ShowWindow(PointControls);
	GetDlgItem(IDC_TEXT4)->ShowWindow(PointControls);
	GetDlgItem(IDC_TEXT5)->ShowWindow(PointControls);
	GetDlgItem(IDC_DISTANCE)->ShowWindow(PointControls);
	GetDlgItem(IDC_HEADING)->ShowWindow(PointControls);

	//GetDlgItem(IDC_BUTTON2)->ShowWindow(RiddleControls);
	GetDlgItem(IDC_RIDDLE_TEXT)->ShowWindow(RiddleControls);


	m_Answer = "";
	stepFinishTime = CTime::GetCurrentTime() + CTimeSpan(0,0,0,Steps[curStep].SecondsToNextStep);

	m_Location = Steps[curStep].Location;

	if (Steps[curStep].IsRiddle)
	{
		m_RiddleText = Steps[curStep].RiddleText;
		m_AnswerText = "The answer is";
		m_Caption = "Riddle:";
	}
	else
	{
		m_Distance = Steps[curStep].Distance;
		m_Heading = Steps[curStep].Heading;
		m_AnswerText = "The secret code is";
		m_Caption = "Directions:";
	}
	UpdateData(FALSE);
}

void CSuperDuperScavengerHuntDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (CTime::GetCurrentTime() >= stepFinishTime)
	{
		// failed to complete step on time
		KillTimer(0);
		
		UpdateData(TRUE);
		m_Answer.MakeLower();
		CString temp = Steps[curStep].Answer;
		temp.MakeLower();
	
		if (temp == m_Answer)
		{
			// correct
			MessageBox("Answer correct!");
			AdvanceToNextStep();
		}
		else
		{
			MessageBox("You failed to complete the step on time.  Better luck with the next!");
			nStepsTimeOut++;
			TimeIsUp = TRUE;
			m_TimeLeft = "Time's Up";
			UpdateData(FALSE);
		}
	}
	else
	{
		// display time remaining
		m_TimeLeft = GetTimeSpan(stepFinishTime - CTime::GetCurrentTime(), 2);
		GetDlgItem(IDC_TIME_LEFT)->SetWindowText(m_TimeLeft);

	}
	CDialog::OnTimer(nIDEvent);
}

void CSuperDuperScavengerHuntDlg::EndQuest()
{

	MessageBox("You are a genius!  Good job completing this quest.");
	MessageBox("Are you hungry by now?  Head back to Lindsey's for a treat...  See ya soon.");
	EndDialog(0);
}


void CSuperDuperScavengerHuntDlg::AdvanceToNextStep()
{
	if (Steps[curStep].CompletionInfo != "")
		MessageBox(Steps[curStep].CompletionInfo);
	curStep++;
	if (curStep == totalSteps)
	// quest complete
		EndQuest();
	else
		DisplayStep();
}
