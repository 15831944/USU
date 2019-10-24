// Assignment 1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Assignment 1.h"
#include "Assignment 1Dlg.h"
#include <Mmsystem.h>

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
// CAssignment1Dlg dialog

CAssignment1Dlg::CAssignment1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAssignment1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAssignment1Dlg)
	m_SolutionNumber = 0;
	m_RecursiveCalls = 0;
	m_QueensRemoved = 0;
	m_Solutions = 0;
	m_TimeRequired = 0;
	m_IsSafeCalls = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	DWORD startTime = timeGetTime();
	Solve8Queens();
	m_TimeRequired = timeGetTime() - startTime; 
	m_SolutionNumber = 1;
}


BOOL CAssignment1Dlg::IsSquareSafe(int Row, int Col,int QueenRow[]){
	m_IsSafeCalls++;
	for (int whichQueen = 0; whichQueen < Col; whichQueen++){
		if (QueenRow[whichQueen] == Row)
			return FALSE;
		if (Row - QueenRow[whichQueen] == Col - whichQueen ||
			QueenRow[whichQueen] - Row == Col - whichQueen )
			return FALSE;
	}
	return TRUE;
}

void CAssignment1Dlg::Solve8Queens(int QueensPos[] /*=NULL*/, int CurrColumn /*=0*/){
	
	for (int Row = 0; Row < 8; Row++){
	
		if (IsSquareSafe(Row, CurrColumn, QueensPos)){
			int QueenRow[8];
			for (int i = 0; i < CurrColumn; i++)
				QueenRow[i] = QueensPos[i];
			
			QueenRow[CurrColumn] = Row;
			if (CurrColumn == 7){
				memcpy(SolutionData[m_Solutions++],QueenRow,sizeof(QueenRow));
			}
			else
			{
				m_RecursiveCalls++;
				Solve8Queens(QueenRow, ++CurrColumn);
				m_QueensRemoved++;
				CurrColumn--;
			}
		}
	}
}

void CAssignment1Dlg::ShowSolution(){
	CPaintDC dc(GetDlgItem(IDC_CHESS_AREA));
	CRect rect;
	m_ChessArea.GetClientRect( rect );
	int SquareWidth = rect.Width()  / 8;
	int SquareHeigth = rect.Height() / 8;
	int x = 0;
	int y = 0;

	for (int row = 0; row < 8; row++){
		for (int column = 0; column < 8; column++){
			if (SolutionData[m_SolutionNumber - 1][column] == row){
				dc.BitBlt(x,y,44,37,((row + column) % 2 == 0 ? &m_memQueenBmpG : &m_memQueenBmpP),0,0,SRCCOPY); 
			}
			else{
				if ((row + column) % 2 == 0)
					dc.FillSolidRect( x, y, SquareWidth, SquareHeigth, PALETTEINDEX(12));
				else
					dc.FillSolidRect( x, y, SquareWidth, SquareHeigth, PALETTEINDEX(4));
			}
			x += SquareWidth;
		}
		y += SquareHeigth;
		x = 0;
	}
}


void CAssignment1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssignment1Dlg)
	DDX_Control(pDX, IDC_CHESS_AREA, m_ChessArea);
	DDX_Control(pDX, IDC_SPIN1, m_SpinControl);
	DDX_Text(pDX, IDC_SOLUTION_NUMBER, m_SolutionNumber);
	DDV_MinMaxInt(pDX, m_SolutionNumber, 1, 92);
	DDX_Text(pDX, IDC_RECURSIVE_CALLS, m_RecursiveCalls);
	DDX_Text(pDX, IDC_QUEENS_REMOVED, m_QueensRemoved);
	DDX_Text(pDX, IDC_SOLUTIONS, m_Solutions);
	DDX_Text(pDX, IDC_TIME_REQUIRED, m_TimeRequired);
	DDX_Text(pDX, IDC_IS_SAFE_CALLS, m_IsSafeCalls);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAssignment1Dlg, CDialog)
	//{{AFX_MSG_MAP(CAssignment1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_VIEW_SOURCE, OnViewSource)
	ON_EN_CHANGE(IDC_SOLUTION_NUMBER, OnChangeSolutionNumber)
	ON_BN_CLICKED(IDC_ABOUTBOX, OnAboutbox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssignment1Dlg message handlers

BOOL CAssignment1Dlg::OnInitDialog()
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
	CClientDC dc(GetDlgItem(IDC_CHESS_AREA));
	m_bmpQueenP.LoadBitmap(IDB_QUEEN_PURPLE);
	m_memQueenBmpP.CreateCompatibleDC( &dc );
	m_memQueenBmpP.SelectObject(&m_bmpQueenP);
	m_bmpQueenG.LoadBitmap(IDB_QUEEN_GRAY);
	m_memQueenBmpG.CreateCompatibleDC( &dc );
	m_memQueenBmpG.SelectObject(&m_bmpQueenG);
	
	m_SpinControl.SetBuddy( GetDlgItem(IDC_SOLUTION_NUMBER));
	m_SpinControl.SetRange( 1, m_Solutions );
	UpdateData(TOSCREEN);
	UpdateWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAssignment1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAssignment1Dlg::OnPaint() 
{
	CDialog::OnPaint();
	ShowSolution();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAssignment1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAssignment1Dlg::OnViewSource() 
{
	// TODO: Add your control notification handler code here
	MessageBox("This feature is not yet implemented","View source code",MB_ICONINFORMATION);	
}

void CAssignment1Dlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CAssignment1Dlg::OnChangeSolutionNumber() 
{
	UpdateData(FROMSCREEN);
	RedrawWindow(NULL, NULL);
}

void CAssignment1Dlg::OnAboutbox() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
