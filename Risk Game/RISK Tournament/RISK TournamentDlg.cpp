// RISK TournamentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RISK Tournament.h"
#include "RISK TournamentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char workingDirectory[255];

/////////////////////////////////////////////////////////////////////////////
// CRISKTournamentDlg dialog

CRISKTournamentDlg::CRISKTournamentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRISKTournamentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRISKTournamentDlg)
	m_nPlayers = 0;
	m_nGames = 0;
	m_nRepetitions = 1;
	m_PPG = 2;
	m_CurrentGame = _T("");
	m_GamesPlayed = _T("");
	m_TimeRemaining = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_IsRunning = FALSE;
}

BOOL CRISKTournamentDlg::IsDLLPathInUse(CString fileName)
{
	for (int i = 0; i < m_nPlayers; i++)
	{
		if (fileName == m_DllList.GetItemText(i,0))
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CRISKTournamentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRISKTournamentDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress1);
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Control(pDX, IDC_DLL_LIST, m_DllList);
	DDX_Text(pDX, IDC_N_PLAYERS, m_nPlayers);
	DDX_Text(pDX, IDC_TOTAL_GAMES, m_nGames);
	DDX_Text(pDX, IDC_N_REPETITIONS, m_nRepetitions);
	DDX_Text(pDX, IDC_PLAYERS_PER_GAME, m_PPG);
	DDX_Text(pDX, IDC_CURRENT_GAME, m_CurrentGame);
	DDX_Text(pDX, IDC_GAMES_PLAYED, m_GamesPlayed);
	DDX_Text(pDX, IDC_TIME_REMAINING, m_TimeRemaining);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRISKTournamentDlg, CDialog)
	//{{AFX_MSG_MAP(CRISKTournamentDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_STOP, OnStartStop)
	ON_BN_CLICKED(IDC_ADD_DLL, OnAddDll)
	ON_BN_CLICKED(IDC_REMOVE_DLL, OnRemoveDll)
	ON_EN_CHANGE(IDC_N_REPETITIONS, OnChangeNRepetitions)
	ON_EN_CHANGE(IDC_PLAYERS_PER_GAME, OnChangePlayersPerGame)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRISKTournamentDlg message handlers

BOOL CRISKTournamentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_DllList.InsertColumn(0,"File Name");
	m_DllList.InsertColumn(1,"Player Name");
	m_DllList.InsertColumn(2,"Total Points");
	m_DllList.InsertColumn(3,"1st Place Finishes");
	m_DllList.SetColumnWidth(0,LVSCW_AUTOSIZE_USEHEADER);
	m_DllList.SetColumnWidth(1,LVSCW_AUTOSIZE_USEHEADER);
	m_DllList.SetColumnWidth(2,LVSCW_AUTOSIZE_USEHEADER);
	m_DllList.SetColumnWidth(3,LVSCW_AUTOSIZE_USEHEADER);
	m_Progress1.SetRange(0,100);
	LoadData();
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRISKTournamentDlg::OnPaint() 
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
HCURSOR CRISKTournamentDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRISKTournamentDlg::OnStartStop() 
{
	// TODO: Add your control notification handler code here
	if (m_IsRunning)
	{
		// try to stop the tournament
		if (m_WorkerThread.m_Processing)
		{
			//m_WorkerThread.PostQuitMessage(0);
		}
		else
			EndProcessing();
	}
	else
	{
		// try to start the tournament
		srand(time(0));
		EnableConfiguration(FALSE);
		GetDlgItem(IDC_START_STOP)->SetWindowText("Stop");
		SaveData();
		m_IsRunning = TRUE;
		m_StartTime = CTime::GetCurrentTime();
		
		m_nGamesPlayed = 0;
		m_WorkerThread.SetGameData(m_PPG,m_nPlayers,m_nRepetitions,&m_nGamesPlayed);
		
		for (int i = 0; i < m_nPlayers; i++)
			m_WorkerThread.SetDLLName(i,m_DllList.GetItemText(i,0));
		
		m_WorkerThread.CreateThread();

		
		SetTimer(ID_UPDATE,500,NULL);
	}
}

void CRISKTournamentDlg::OnAddDll() 
{
	// TODO: Add your control notification handler code here
	CFileDialog getDLLNameDlg(TRUE, "*.dll", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Dynamic Link Libraries (*.dll)|*.dll||"); 
	getDLLNameDlg.m_ofn.lpstrTitle = "Select Player DLL file";
	if (getDLLNameDlg.DoModal()==IDOK)
	{
		AddPlayer(getDLLNameDlg.GetPathName());
		UpdateData(FALSE);
	}
	SetCurrentDirectory(workingDirectory);
}

void CRISKTournamentDlg::OnRemoveDll() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CRISKTournamentDlg::TestDLL(CString fileName, CString &PlayerName)
{
    if (IsDLLPathInUse(fileName))
	{
		MessageBox ("This DLL is already in use.  Please select a different DLL for use.","Error",MB_ICONINFORMATION);
		return FALSE;
	}
	else
	{
        if (TestPlayerDLL(fileName.GetBuffer(0), PlayerName.GetBuffer(100)) == FALSE)
		{
			CString message;
			message.Format("Failed to load DLL %s.  %s",fileName.GetBuffer(0),"Error");
			MessageBox (message);
			return FALSE;
        }
		else
		{
			return TRUE;
		}   
    }
}

int Permutations(int n, int r)
{
	int k = 1;
	for (int i = n; i > n - r; i--)
		k *= i;
	return k;
}

void CRISKTournamentDlg::ComputeGames()
{
	if (m_nRepetitions < 1 || m_PPG < 2)
		m_nGames = 0;
	else
	{
		m_nGames = Permutations(m_nPlayers,m_PPG) * m_nRepetitions;
	}
	GetDlgItem(IDC_START_STOP)->EnableWindow(m_nGames > 0);
}


BOOL CRISKTournamentDlg::AddPlayer(CString FileName)
{
	CString PlayerName;
	if(TestDLL(FileName,PlayerName))
	{
		if (m_DllList.m_hWnd)
		{
			m_DllList.InsertItem(m_nPlayers,FileName);
			m_DllList.SetItemText(m_nPlayers,1,PlayerName);
			m_DllList.SetColumnWidth(0,LVSCW_AUTOSIZE);
			m_DllList.SetColumnWidth(1,LVSCW_AUTOSIZE);
		}
		m_nPlayers++;
		int upper = m_nPlayers;
		if (upper < 2) 
			upper = 2;
		m_spin1.SetRange(2,upper);
		ComputeGames();
		return TRUE;
	}
	return FALSE;
}

void CRISKTournamentDlg::SaveData() 
{
	// TODO: Add extra validation here
	CFile fout("Last DLL File List.txt",CFile::modeWrite|CFile::modeCreate);
	CArchive ar(&fout,CArchive::store);
	CString fileName;
	ar.Write(&m_nPlayers,sizeof(int));
	ar.Write(&m_nRepetitions,sizeof(int));
	ar.Write(&m_PPG,sizeof(int));

	for (int i = 0; i < m_nPlayers; i++)
	{
		fileName = CString(m_DllList.GetItemText(i,0)) + CString("\n");
		ar.WriteString(fileName);
	}
	ar.Close();
	fout.Close();
}

void CRISKTournamentDlg::LoadData()
{
	TRY
	{
		CFile fin("Last DLL File List.txt",CFile::modeRead);
		CArchive ar(&fin,CArchive::load);
		CString fileName;
		int nDLLs;
		ar.Read(&nDLLs,sizeof(int));
		ar.Read(&m_nRepetitions,sizeof(int));
		ar.Read(&m_PPG,sizeof(int));
		m_nPlayers = 0;
		for (int i = 0; i < nDLLs; i++)
		{
			ar.ReadString(fileName);
			AddPlayer(fileName);
		}
		UpdateData(FALSE);
		ar.Close();
		fin.Close();
	}
	CATCH(CFileException, pEx)
	{
		// Simply show an error message to the user.
		m_nPlayers = 0;
	}
	END_CATCH
}

void CRISKTournamentDlg::OnChangeNRepetitions() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CWnd * ctrl1 = GetDlgItem(IDC_N_REPETITIONS);
	CWnd * ctrl2 = GetDlgItem(IDC_PLAYERS_PER_GAME);
	if (ctrl1 && ctrl2 && ctrl1->GetWindowTextLength() > 0 &&
		ctrl2->GetWindowTextLength() > 0)
	{
		UpdateData();
		ComputeGames();
		UpdateData(FALSE);
	}
}

void CRISKTournamentDlg::OnChangePlayersPerGame() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CWnd * ctrl1 = GetDlgItem(IDC_N_REPETITIONS);
	CWnd * ctrl2 = GetDlgItem(IDC_PLAYERS_PER_GAME);
	if (ctrl1 && ctrl2 && ctrl1->GetWindowTextLength() > 0 &&
		ctrl2->GetWindowTextLength() > 0)
	{
		UpdateData();
		ComputeGames();
		UpdateData(FALSE);
	}
}

void CRISKTournamentDlg::EnableConfiguration(BOOL Enable)
{
	GetDlgItem(IDC_N_PLAYERS)->EnableWindow(Enable);
	GetDlgItem(IDC_PLAYERS_PER_GAME)->EnableWindow(Enable);
	GetDlgItem(IDC_N_REPETITIONS)->EnableWindow(Enable);
	GetDlgItem(IDC_TOTAL_GAMES)->EnableWindow(Enable);
	GetDlgItem(IDC_SPIN1)->EnableWindow(Enable);
	GetDlgItem(IDC_T1)->EnableWindow(Enable);
	GetDlgItem(IDC_T2)->EnableWindow(Enable);
	GetDlgItem(IDC_T3)->EnableWindow(Enable);
	GetDlgItem(IDC_T4)->EnableWindow(Enable);
	GetDlgItem(IDC_T5)->EnableWindow(Enable);
}

void CRISKTournamentDlg::OnTimer(UINT nIDEvent) 
{
	
// TODO: Add your message handler code here and/or call default
	if (nIDEvent==ID_UPDATE)
	{
		m_CurrentGame = "( ";
		for (int i = 0; i < m_WorkerThread.PPG; i++)
		{
			CString mk;
			if (i < m_WorkerThread.PPG - 1)
				mk.Format("%i, ",m_WorkerThread.currentPlayers[i]);
			else
				mk.Format("%i )",m_WorkerThread.currentPlayers[i]);
			m_CurrentGame += mk;
		}
		if (m_WorkerThread.m_Processing)
		{
			m_GamesPlayed.Format("%i/%i",m_nGamesPlayed,m_nGames);
			if (m_nGamesPlayed > 0)
			{
				m_Progress1.SetPos(m_nGamesPlayed * 100 / m_nGames);
				int SecondsElapsed = (CTime::GetCurrentTime() - m_StartTime).GetTotalSeconds();
				int TotalSeconds = SecondsElapsed * m_nGames / m_nGamesPlayed;
				int SecondsRemaining = TotalSeconds - SecondsElapsed;
				int HoursRemaining = SecondsRemaining / 3600;
				SecondsRemaining -= HoursRemaining * 3600;
				int MinutesRemaining = SecondsRemaining / 60;
				SecondsRemaining -= MinutesRemaining * 60;

				if (HoursRemaining > 0)
					m_TimeRemaining.Format("%i Hours %i Minutes",HoursRemaining,MinutesRemaining);
				else
					m_TimeRemaining.Format("%i Minutes %i Seconds",MinutesRemaining,SecondsRemaining);
			}
			else
			{
				m_TimeRemaining = "?";
			}
		}
		else
		{
			m_Progress1.SetPos(100);
			int SecondsElapsed = (CTime::GetCurrentTime() - m_StartTime).GetTotalSeconds();
			
			int HoursElapsed = SecondsElapsed / 3600;
			SecondsElapsed -= HoursElapsed * 3600;
			int MinutesElapsed = SecondsElapsed / 60;
			SecondsElapsed -= MinutesElapsed * 60;

			if (HoursElapsed > 0)
				m_TimeRemaining.Format("Completed in %i Hours %i Minutes",HoursElapsed,MinutesElapsed);
			else
				m_TimeRemaining.Format("Completed in %i Minutes %i Seconds",MinutesElapsed,SecondsElapsed);
			KillTimer(ID_UPDATE);
			EndProcessing();
		}

		UpdateData(FALSE);
	}
}

void CRISKTournamentDlg::EndProcessing()
{
	EnableConfiguration(TRUE);
	GetDlgItem(IDC_START_STOP)->SetWindowText("Start");
	m_IsRunning = FALSE;
}
