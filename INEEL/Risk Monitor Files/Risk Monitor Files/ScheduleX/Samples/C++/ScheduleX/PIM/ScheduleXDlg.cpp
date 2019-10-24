// ScheduleXDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScheduleX.h"
#include "ScheduleXDlg.h"
#include "pvdayview.h"
#include "pvalarm.h"
#include "pvappointment.h"
#include "pvappointmentset.h"
#include "pvtaskpad.h"
#include "pvtaskitem.h"
#include "pvcalendar.h"
#include "font.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleXDlg dialog

CScheduleXDlg::CScheduleXDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScheduleXDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScheduleXDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScheduleXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScheduleXDlg)
	DDX_Control(pDX, IDC_PVCALENDAR1, m_calendar);
	DDX_Control(pDX, IDC_PVTASKPAD1, m_taskpad);
	DDX_Control(pDX, IDC_PVDAYVIEW1, m_dayview);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScheduleXDlg, CDialog)
	//{{AFX_MSG_MAP(CScheduleXDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScheduleXDlg message handlers

BOOL CScheduleXDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	IUnknown *punk;
	LPDISPATCH lpDisp;

	// Get the IUnknown
	punk = m_dayview.GetControlUnknown();
	// Ask for the IDispatch
	punk->QueryInterface(IID_IDispatch, (void**)&lpDisp);
	// Attach
	m_calendar.AttachDayView(lpDisp);
	// Release
	lpDisp->Release();

	// Attach the other way
	punk = m_calendar.GetControlUnknown();
	punk->QueryInterface(IID_IDispatch, (void**)&lpDisp);
	m_dayview.AttachCalendar(lpDisp);
	lpDisp->Release();

	// Add the holidays
	AddHolidays();


	// Add some appointments
	CPVAppointment app;
	COleDateTime StartDate, EndDate, CurrentDate, appStart, appEnd;
	COleDateTimeSpan span;

	// This is the first Friday in 1999
	StartDate.SetDateTime(1999, 1, 1, 0, 0, 0);

	// This is the last Friday in 1999
	EndDate.SetDateTime(1999, 12, 31, 0, 0, 0);

	//Iterate through the year 1999 and add an appointment to every other Friday 
	span.SetDateTimeSpan(14, 0, 0, 0);
	CurrentDate = StartDate;

	while (CurrentDate <= EndDate) 
	{
		appStart.SetDateTime(CurrentDate.GetYear(), CurrentDate.GetMonth(), CurrentDate.GetDay(), 8, 30, 0);
		appEnd.SetDateTime(CurrentDate.GetYear(), CurrentDate.GetMonth(), CurrentDate.GetDay(), 9, 0, 0);
		app = m_dayview.GetAppointmentSet().Add("Bi-Weekly Meeting", appStart, appEnd);

		CurrentDate += span;
	}

	StartDate = COleDateTime::GetCurrentTime();
	CPVAlarm alarm;

	appStart.SetDateTime(StartDate.GetYear(), StartDate.GetMonth(), StartDate.GetDay(), 15, 0, 0);
	appEnd.SetDateTime(StartDate.GetYear(), StartDate.GetMonth(), StartDate.GetDay(), 16, 0, 0);
	app = m_dayview.GetAppointmentSet().Add("Another appointment", appStart, appEnd);
	alarm = app.GetAlarm();
	alarm.SetDescription("Meeting at 3pm");
	alarm.SetDisplay("Reminder");
	span.SetDateTimeSpan(0, 0, 5, 0);
	StartDate += span;
	alarm.SetStartDateTime(StartDate);
	alarm.SetOn(TRUE);

	CPVTaskItem task;
	VARIANT var;
	CString str = "Low";

	VariantInit(&var);
	task = m_taskpad.AddItem(FALSE, "Finish taxes", StartDate);
	var.vt = VT_BSTR;
	var.bstrVal = str.AllocSysString();
	task.SetFieldValue("Priority", var);
	VariantClear(&var);

	span.SetDateTimeSpan(1, 0, 0, 0);
	StartDate -= span;
	m_taskpad.AddItem(FALSE, "Give dog HeartGuard medication", StartDate);

	COleFont font;
	font = m_calendar.GetDATEFont(StartDate);
	if (font == NULL)
	{
		LPDISPATCH pDisp = NULL;
		FONTDESC fontDesc = {sizeof(FONTDESC), OLESTR("MS Sans Serif"), 
		FONTSIZE(8), FW_BOLD, DEFAULT_CHARSET, FALSE,
		FALSE, FALSE };

		OleCreateFontIndirect(&fontDesc, IID_IFont, (void**)&pDisp);

		m_calendar.SetDATEFont(StartDate, pDisp);
	}

	m_calendar.GetDATEFont(StartDate).SetBold(TRUE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScheduleXDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScheduleXDlg::OnPaint() 
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
HCURSOR CScheduleXDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScheduleXDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_calendar.AttachDayView(NULL);
	m_dayview.AttachCalendar(NULL);
	
	CDialog::OnOK();
}

void CScheduleXDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_calendar.AttachDayView(NULL);
	m_dayview.AttachCalendar(NULL);
	
	CDialog::OnCancel();
}

void CScheduleXDlg::OnClose() 
{
	m_calendar.AttachDayView(NULL);
	m_dayview.AttachCalendar(NULL);
	
	CDialog::OnClose();
}

void CScheduleXDlg::AddHolidays()
{
	int i;
	COleDateTime start, end;
	CPVAppointmentSet apptset;
	CPVAppointment appt;

	GetHolidays();

	apptset = m_dayview.GetAppointmentSet();
	start.SetTime(0, 0, 0);
	end.SetTime(23, 59, 0);

	for (i = 0; i < 23; i++)
	{
		m_calendar.SetDATEText(m_Holidays[i].Date, m_Holidays[i].Holiday);
		appt = apptset.Add(m_Holidays[i].Holiday, m_Holidays[i].Date + start, m_Holidays[i].Date + end);
	}
}

void CScheduleXDlg::GetHolidays()
{
	// Christmas Day, 2000/12/25
	m_Holidays[0].Holiday = "Christmas Day"; 
	m_Holidays[0].Date.SetDate(2000, 12, 25);
	
	// Christmas Eve, 2000/12/24
	m_Holidays[1].Holiday = "Christmas Eve";
	m_Holidays[1].Date.SetDate(2000, 12, 24);
	
	// Columbus Day, 2000/10/09
	m_Holidays[2].Holiday = "Columbus Day";
	m_Holidays[2].Date.SetDate(2000, 10, 9);

	// Easter, 2000/04/23
	m_Holidays[3].Holiday = "Easter"; 
	m_Holidays[3].Date.SetDate(2000, 4, 23);
	
	// Election Day, 2000/11/07
	m_Holidays[4].Holiday = "Election Day";
	m_Holidays[4].Date.SetDate(2000, 11, 7);

	// Father's Day, 2000/06/18
	m_Holidays[5].Holiday = "Father's Day";
	m_Holidays[5].Date.SetDate(2000, 6, 18);

	// Flag Day, 2000/06/14
	m_Holidays[6].Holiday = "Flag Day";
	m_Holidays[6].Date.SetDate(2000, 6, 14);

	// Groundhog Day, 2000/02/02
	m_Holidays[7].Holiday = "Groundhog Day";
	m_Holidays[7].Date.SetDate(2000, 2, 2);

	// Halloween, 2000/10/31
	m_Holidays[8].Holiday = "Halloween";
	m_Holidays[8].Date.SetDate(2000, 10, 31);

	// Independence Day, 2000/07/04
	m_Holidays[9].Holiday = "Independence Day";
	m_Holidays[9].Date.SetDate(2000, 7, 4);

	// Labor Day, 2000/09/04
	m_Holidays[10].Holiday = "Labor Day";
	m_Holidays[10].Date.SetDate(2000, 9, 4);

	// Lincoln's Birthday, 2000/02/12
	m_Holidays[11].Holiday = "Lincoln's Birthday";
	m_Holidays[11].Date.SetDate(2000, 2, 12);

	// Martin Luther King Day, 2000/01/17
	m_Holidays[12].Holiday = "Martin Luther King Day";
	m_Holidays[12].Date.SetDate(2000, 1, 17);

	// Memorial Day, 2000/05/29
	m_Holidays[13].Holiday = "Memorial Day";
	m_Holidays[13].Date.SetDate(2000, 5, 29);

	// Mother's Day, 2000/05/14
	m_Holidays[14].Holiday = "Mother's Day";
	m_Holidays[14].Date.SetDate(2000, 5, 14);

	// New Year's Day, 2000/01/01
	m_Holidays[15].Holiday = "New Year's Day";
	m_Holidays[15].Date.SetDate(2000, 1, 1);

	// New Year's Eve, 2000/12/31
	m_Holidays[16].Holiday = "New Year's Eve";
	m_Holidays[16].Date.SetDate(2000, 12, 31);

	// President's Day, 2000/02/21
	m_Holidays[17].Holiday = "President't Day";
	m_Holidays[17].Date.SetDate(2000, 2, 21);

	// Saint Patrick's Day, 2000/03/17
	m_Holidays[18].Holiday = "Saint Patrick's Day";
	m_Holidays[18].Date.SetDate(2000, 3, 17);

	// Tax Day, 2000/04/17
	m_Holidays[19].Holiday = "Tax Day";
	m_Holidays[19].Date.SetDate(2000, 4, 17);

	// Thanksgiving Day, 2000/11/23
	m_Holidays[20].Holiday = "Thanksgiving Day";
	m_Holidays[20].Date.SetDate(2000, 11, 23);

	// Valentine's Day, 2000/02/14
	m_Holidays[21].Holiday = "Valentine's Day";
	m_Holidays[21].Date.SetDate(2000, 2, 14);

	// Veteran's Day, 2000/11/11
	m_Holidays[22].Holiday = "Veteran's Day";
	m_Holidays[22].Date.SetDate(2000, 11, 11);
}