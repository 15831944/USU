// ChooseLocationsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "ChooseLocationsDialog.h"
#include "RenameLocationDialog.h"
#include "LADA Control ModuleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void  SortDescending( int array[], int n );
extern void  SortAscending( int array[], int n );
extern void  AssociateFSLFile(char (*InputLocNameList)[2][30], CString filename = "");
extern void  SetFontText(UINT controlID, UINT stringID, CWnd *window);
extern void  SetItemFont(UINT controlID, CWnd *window);
extern CFont smallRussianArial;
extern int   curLanguage;
/////////////////////////////////////////////////////////////////////////////
// CChooseLocationsDlg dialog


CChooseLocationsDlg::CChooseLocationsDlg(char (*iNames)[2][30], int *iLocSaveList, int *nSaveList, CWnd* pParent /*=NULL*/)
	: CDialog(CChooseLocationsDlg::IDD, pParent)
{
	//char iNames[][30][2]
	//{{AFX_DATA_INIT(CChooseLocationsDlg)
	m_nLocations = 0;
	m_WhichGraphSel = -1;
	//}}AFX_DATA_INIT
	SInputLocList = iLocSaveList;
	MaxSelectedLocations = MAX_INPUT_LOCATIONS;
	AvailableStrings = MAX_INPUT_LOCATIONS;
	nILSaveList = nSaveList;
	InputLocNames = iNames;
	dType = SaveMonitorDlg;
	pDoc = NULL;
}

CChooseLocationsDlg::CChooseLocationsDlg(CLADAControlModuleDoc * doc, CWnd* pParent) // = NULL
	: CDialog(CChooseLocationsDlg::IDD, pParent)
{
	//
	
	m_WhichGraphSel = doc->curWindow;
	//
	pDoc = doc;
	InputLocNames = pDoc->InputLocationNameList;
	
	MaxSelectedLocations = 15;
	AvailableStrings = pDoc->nData;
	
	dType = DisplayLocationsDlg;

}

void CChooseLocationsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseLocationsDlg)
	DDX_Control(pDX, IDCANCEL, m_Button9);
	DDX_Control(pDX, IDOK, m_Button8);
	DDX_Control(pDX, IDC_SORT_LOCATIONS, m_Button5);
	DDX_Control(pDX, IDC_SELECT_ALLS, m_Button3);
	DDX_Control(pDX, IDC_SELECT_ALLI, m_Button2);
	DDX_Control(pDX, IDC_RENAME_LOCATION, m_Button4);
	DDX_Control(pDX, IDC_REMOVE, m_Button7);
	DDX_Control(pDX, IDC_INSERT, m_Button6);
	DDX_Control(pDX, IDC_FSL_FILE, m_Button1);
	DDX_Control(pDX, IDC_N_LOCATIONS, m_CNLocs);
	DDX_Control(pDX, IDC_WHICH_GRAPH, m_WhichGraph);
	DDX_Control(pDX, IDC_S_LOCATIONS, m_SLocations);
	DDX_Control(pDX, IDC_A_LOCATIONS, m_ALocations);
	DDX_Text(pDX, IDC_N_LOCATIONS, m_nLocations);
	DDV_MinMaxInt(pDX, m_nLocations, 0, 256);
	DDX_CBIndex(pDX, IDC_WHICH_GRAPH, m_WhichGraphSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseLocationsDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseLocationsDlg)
	ON_BN_CLICKED(IDC_SORT_LOCATIONS, OnSortLocations)
	ON_BN_CLICKED(IDC_RENAME_LOCATION, OnRenameLocation)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_FSL_FILE, OnFslFile)
	ON_LBN_DBLCLK(IDC_S_LOCATIONS, OnDblclkSLocations)
	ON_LBN_DBLCLK(IDC_A_LOCATIONS, OnDblclkALocations)
	ON_BN_CLICKED(IDC_SELECT_ALLI, OnSelectAlli)
	ON_BN_CLICKED(IDC_SELECT_ALLS, OnSelectAlls)
	ON_LBN_SELCHANGE(IDC_S_LOCATIONS, OnSelchangeSLocations)
	ON_LBN_SELCHANGE(IDC_A_LOCATIONS, OnSelchangeALocations)
	ON_CBN_SELCHANGE(IDC_WHICH_GRAPH, OnSelchangeWhichGraph)
	ON_EN_CHANGE(IDC_N_LOCATIONS, OnChangeNLocations)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseLocationsDlg message handlers

void CChooseLocationsDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	*nILSaveList = m_nLocations;
	CDialog::OnOK();
}

void CChooseLocationsDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CChooseLocationsDlg::OnSortLocations() 
{
	// TODO: Add your control notification handler code here
	SortAscending(SInputLocList,m_nLocations);
	m_SLocations.ResetContent();
	for (int i = 0; i < m_nLocations; i++){
		m_SLocations.AddString( InputLocNames[SInputLocList[i] - (dType == SaveMonitorDlg)][curLanguage] );
	}
}

void CChooseLocationsDlg::OnRenameLocation() 
{
		// TODO: Add your control notification handler code here
	int SelectedRight = m_SLocations.GetSelCount();
	int SelectedLeft = m_ALocations.GetSelCount();
	int whichSelection;
	
	int whichLocation;

	if (SelectedRight == 1 && SelectedLeft == 0 ){
		m_SLocations.GetSelItems(1, &whichSelection);
		
		if (dType == DisplayLocationsDlg)
			whichLocation = SInputLocList[whichSelection] + 1;
		else
			whichLocation = SInputLocList[whichSelection];
		
	}
	else if (SelectedLeft == 1 && SelectedRight == 0 ){
		m_ALocations.GetSelItems(1, &whichSelection);
		whichLocation = whichSelection + 1;
	
	}
	else {
		MessageBox("Please select one location to rename.","Rename");
		return;
	}
	
	RenameLocation(whichLocation);
}

void CChooseLocationsDlg::RenameLocation(int whichLocation)
{
	// this will now take a zero based location
	whichLocation--;

	CString OldName = &InputLocNames[whichLocation][curLanguage][4];
	char newName[31];
	newName[0] = '\0';
	CRenameLocationDialog cNewName(OldName, newName,
		"Input Location", "Rename Input Location Dialog", whichLocation + 1, TRUE, this );
	cNewName.DoModal();
	
	strcpy(&InputLocNames[whichLocation][curLanguage][4], newName);
	for (int i = 0; i < m_nLocations; i++){
		if (SInputLocList[i] == whichLocation + (dType == SaveMonitorDlg)){
			m_SLocations.DeleteString( i );
			m_SLocations.InsertString( i, InputLocNames[whichLocation][curLanguage] );
		}
	}
	m_ALocations.DeleteString( whichLocation );
	m_ALocations.InsertString( whichLocation, InputLocNames[whichLocation][curLanguage] );
}

void CChooseLocationsDlg::OnRemove() 
{
	// TODO: Add your control notification handler code here
	int * currRightSelections = new int[MaxSelectedLocations];
	int currRightS;
	
	currRightS = m_SLocations.GetSelCount();
	if (currRightS){
		if (dType == DisplayLocationsDlg)
			pDoc->graphListModified[m_WhichGraphSel] = TRUE;
		m_SLocations.GetSelItems(MaxSelectedLocations, currRightSelections);
		SortDescending(currRightSelections, currRightS );
		for (int i = 0; i < currRightS; i++){
			m_SLocations.DeleteString( currRightSelections[i] );
			m_nLocations--;
			for (int j = currRightSelections[i]; j < m_nLocations; j++)
				SInputLocList[j] = SInputLocList[j+1];
		}
	}
	else {
		MessageBox("There are no items selected to remove.","Error",MB_ICONEXCLAMATION);
	}
	delete [] currRightSelections;
	m_SLocations.UpdateWindow();
	UpdateData(FALSE);
}

void CChooseLocationsDlg::OnInsert() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	int * currLeftSelections = new int[AvailableStrings];
	int currLeftS;
	
	currLeftS = m_ALocations.GetSelCount();

	int LocsToAdd = currLeftS;
		if (currLeftS){
		if (m_nLocations < MaxSelectedLocations) {
			m_ALocations.GetSelItems(AvailableStrings, currLeftSelections);

			BOOL alreadyUpdated;
			for (int i = 0; i < currLeftS && m_nLocations < MaxSelectedLocations; i++){
				alreadyUpdated = FALSE;
				LocsToAdd--;
				
				for (int j = 0; j < m_nLocations; j++){
					if (currLeftSelections[i] + (dType == SaveMonitorDlg) == SInputLocList[j])
						alreadyUpdated = TRUE;
				}
				if (!alreadyUpdated){
					if (dType == DisplayLocationsDlg){
						SInputLocList[m_nLocations++] = currLeftSelections[i];
						pDoc->graphListModified[m_WhichGraphSel] = TRUE;
					}
					else 
						SInputLocList[m_nLocations++] = currLeftSelections[i] + 1;
				
					m_SLocations.AddString( InputLocNames[currLeftSelections[i]][curLanguage] );
				}
				if (m_nLocations == MaxSelectedLocations && LocsToAdd != 0){
					MessageBox("Not all requested locations could be inserted","Error",MB_ICONEXCLAMATION);
					break;
				}	
			}
		}

		if (m_nLocations == MaxSelectedLocations && LocsToAdd != 0){
			MessageBox("There is no room to insert more input locations","Error",MB_ICONEXCLAMATION);
			MessageBox("Please delete currently selected input locations\n"
				       "before inserting more input locations.","Warning");
		}
	}
	else {
		MessageBox("There are no items selected to insert.","Error",MB_ICONEXCLAMATION);
	}
	UpdateData(FALSE);
	delete [] currLeftSelections;
	m_ALocations.SetSel( -1, FALSE ); // unselects all strings

}

void CChooseLocationsDlg::OnFslFile() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Associating an FSL file will overwrite existing input"
		"location names with those in an FSL file."
		"Do you wish to continue?","Warning",MB_ICONQUESTION | MB_ICONWARNING | MB_YESNO) == IDYES){
		AssociateFSLFile(InputLocNames);
		m_SLocations.ResetContent();
		m_ALocations.ResetContent();
		//memcpy(InputLocNames, AvailableInputLocations, sizeof(AvailableInputLocations));
		for (int i = 0; i < AvailableStrings; i++){
			if ( i < m_nLocations )	
				m_SLocations.AddString( InputLocNames[SInputLocList[i] - (dType == SaveMonitorDlg)][curLanguage] );
			m_ALocations.AddString( InputLocNames[i][curLanguage] );
		}
	}
}

void CChooseLocationsDlg::OnDblclkSLocations() 
{
	// TODO: Add your control notification handler code here
	int currSel = m_SLocations.GetCurSel();
	RenameLocation(SInputLocList[currSel]);
}

void CChooseLocationsDlg::OnDblclkALocations() 
{
	// TODO: Add your control notification handler code here
	int currSel = m_ALocations.GetCurSel();
	RenameLocation(currSel + 1);
	
}

void CChooseLocationsDlg::SetFontText(UINT controlID, UINT stringID){
	::SetFontText(controlID,stringID,this);
}

BOOL CChooseLocationsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetFont(&smallRussianArial);
	CString s;
	s.LoadString(IDS_MTITLE);
	SetWindowText(s);

	// TODO: Add extra initialization here
	switch(dType){
	case SaveMonitorDlg:{
		
		break;
	}
	case DisplayLocationsDlg:{
		m_WhichGraph.EnableWindow(TRUE);
		m_WhichGraph.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TEXT2)->ShowWindow(SW_SHOW);
		for (int i = 0; i < pDoc->numGraphs; i++)
			m_WhichGraph.AddString(CString(char('1'+i)));
		m_WhichGraph.SetCurSel(0);
		m_nLocations = pDoc->nDataGraph[m_WhichGraphSel];
		SInputLocList = pDoc->DataIndex[m_WhichGraphSel];
		nILSaveList = &pDoc->nDataGraph[m_WhichGraphSel];
		ShowGraphChoices();
		break;
	}
	}
	for (int i = 0; i < AvailableStrings && InputLocNames[i][curLanguage] != '\0'; i++)
		m_ALocations.AddString(InputLocNames[i][curLanguage]);
	
	for ( i = 0; i < 7; i++)
		SetFontText(IDC_FSL_FILE+i,IDS_MBUTTON1+i);
	SetFontText(IDOK, IDS_OK);
	SetFontText(IDCANCEL, IDS_CANCEL);
	
	for ( i = 0; i < 4; i++)
		SetFontText(IDC_TEXT1+i,IDS_MTEXT1+i);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseLocationsDlg::ShowGraphChoices()
{
	m_SLocations.ResetContent();
	m_nLocations = *nILSaveList;
	UpdateData(FALSE);
	for (int i = 0; i < *nILSaveList; i++){
		m_SLocations.AddString(InputLocNames[SInputLocList[i]][curLanguage]);
	}
}

void CChooseLocationsDlg::OnSelectAlli() 
{
	// TODO: Add your control notification handler code here
	m_ALocations.SetSel( -1, TRUE );
}

void CChooseLocationsDlg::OnSelectAlls() 
{
	// TODO: Add your control notification handler code here
	m_SLocations.SetSel( -1, TRUE );
}

void CChooseLocationsDlg::OnSelchangeSLocations() 
{
	// TODO: Add your control notification handler code here
	// is the shift button down?
	short shiftStatus = GetKeyState(VK_SHIFT);
	if (shiftStatus && shiftStatus != 1){
		int wSel = m_SLocations.GetCurSel();
		int SelStatus = m_SLocations.GetSel( wSel ) ;

		while (wSel > 0 && m_SLocations.GetSel(--wSel) != SelStatus){
			m_SLocations.SetSel(wSel, SelStatus);
		}
	}
}

void CChooseLocationsDlg::OnSelchangeALocations() 
{
	// TODO: Add your control notification handler code here
	short shiftStatus = GetKeyState(VK_SHIFT);
	if (shiftStatus && shiftStatus != 1){
		int wSel = m_ALocations.GetCurSel();
		int SelStatus = m_ALocations.GetSel( wSel ) ;

		while (wSel > 0 && m_ALocations.GetSel(--wSel) != SelStatus){
			m_ALocations.SetSel(wSel, SelStatus);
		}
	}
}

void CChooseLocationsDlg::OnSelchangeWhichGraph() 
{
	// TODO: Add your control notification handler code here
	// Update the original data, how many items are selected.
	*nILSaveList = m_nLocations;
	UpdateData(TRUE);
	// set the pointers to the right places in pDoc
	SInputLocList = pDoc->DataIndex[m_WhichGraphSel];
	nILSaveList = &pDoc->nDataGraph[m_WhichGraphSel];
	ShowGraphChoices();
}

void CChooseLocationsDlg::OnChangeNLocations() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
