// TournamentCfgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RISK Tournament.h"
#include "TournamentCfgDlg.h"
#include "RISK TournamentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char workingDirectory[256];
/////////////////////////////////////////////////////////////////////////////
// CTournamentCfgDlg dialog


CTournamentCfgDlg::CTournamentCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTournamentCfgDlg::IDD, pParent)
{
	ptrParent = (CRISKTournamentDlg*)pParent;
	//{{AFX_DATA_INIT(CTournamentCfgDlg)
	m_nPlayers = 0;
	m_nRepetitions = 1;
	m_PPG = 2;
	m_nGames = 0;
	//}}AFX_DATA_INIT
	m_DlgInitialized = FALSE;
}


void CTournamentCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTournamentCfgDlg)
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Control(pDX, IDC_DLL_LIST, m_DllList);
	DDX_Text(pDX, IDC_N_PLAYERS, m_nPlayers);
	DDX_Text(pDX, IDC_N_REPETITIONS, m_nRepetitions);
	DDX_Text(pDX, IDC_PLAYERS_PER_GAME, m_PPG);
	DDX_Text(pDX, IDC_TOTAL_GAMES, m_nGames);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTournamentCfgDlg, CDialog)
	//{{AFX_MSG_MAP(CTournamentCfgDlg)
	ON_BN_CLICKED(IDC_ADD_DLL, OnAddDll)
	ON_EN_CHANGE(IDC_PLAYERS_PER_GAME, OnChangePlayersPerGame)
	ON_EN_CHANGE(IDC_N_REPETITIONS, OnChangeNRepetitions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTournamentCfgDlg message handlers

BOOL CTournamentCfgDlg::TestDLL(CString fileName, CString &PlayerName)
{
    
    if (ptrParent->IsDLLPathInUse(fileName))
	{
		MessageBox ("This DLL is already in use.  Please select a different DLL for use.","Error",MB_ICONINFORMATION);
		return FALSE;
	}
	else
	{
        if (TestPlayerDLL(fileName.GetBuffer(0), PlayerName.GetBuffer(100)) == FALSE)
		{
            MessageBox ("This DLL could not be loaded correctly.  Please select a different file.");
			return FALSE;
        }
		else
		{
			return TRUE;
		}   
    }
}

void CTournamentCfgDlg::OnAddDll() 
{
	// TODO: Add your control notification handler code here
	CFileDialog getDLLNameDlg(TRUE, "*.dll", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Dynamic Link Libraries (*.dll)|*.dll||"); 
	getDLLNameDlg.m_ofn.lpstrTitle = "Select Player DLL file";
	if (getDLLNameDlg.DoModal()==IDOK)
	{
		AddPlayer(getDLLNameDlg.GetPathName());
	}
	SetCurrentDirectory(workingDirectory);
}

BOOL CTournamentCfgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_DlgInitialized = TRUE;
	// TODO: Add extra initialization here
	m_DllList.InsertColumn(0,"File Name");
	m_DllList.InsertColumn(1,"Player Name");
	m_DllList.SetColumnWidth(0,LVSCW_AUTOSIZE_USEHEADER);
	m_DllList.SetColumnWidth(1,LVSCW_AUTOSIZE_USEHEADER);
	int upper = m_nPlayers;
	if (upper < 2) 
		upper = 2;
	m_spin1.SetRange(2,upper);
	for (int i = 0; i < m_nPlayers; i++)
	{
		m_DllList.InsertItem(i,ptrParent->m_DllList.GetItemText(i,0));
		m_DllList.SetItemText(i,1,ptrParent->m_DllList.GetItemText(i,1));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int Permutations(int n, int r)
{
	int k = 1;
	for (int i = n; i > n - r; i--)
		k *= i;
	return k;
}

void CTournamentCfgDlg::ComputeGames()
{
	if (m_nRepetitions < 1 || m_PPG < 2)
		m_nGames = 0;
	else
	{
		m_nGames = Permutations(m_nPlayers,m_PPG) * m_nRepetitions;
	}
}

void CTournamentCfgDlg::OnChangePlayersPerGame() 
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

void CTournamentCfgDlg::OnChangeNRepetitions() 
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

void CTournamentCfgDlg::AddPlayer(CString FileName)
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
		ptrParent->m_DllList.InsertItem(m_nPlayers,FileName);
		ptrParent->m_DllList.SetItemText(m_nPlayers,1,PlayerName);
		m_nPlayers++;
		ComputeGames();
		if (m_DllList.m_hWnd)
			UpdateData(FALSE);
	}
}

void CTournamentCfgDlg::OnOK() 
{
	// TODO: Add extra validation here
	CFile fout("Last DLL File List.txt",CFile::modeWrite|CFile::modeCreate);
	CArchive ar(&fout,CArchive::store);
	CString fileName;
	ar.Write(&m_nPlayers,sizeof(int));
	for (int i = 0; i < m_nPlayers; i++)
	{
		fileName = CString(m_DllList.GetItemText(i,0)) + CString("\n");
		ar.WriteString(fileName);
	}
	ar.Close();
	fout.Close();
	CDialog::OnOK();
}
