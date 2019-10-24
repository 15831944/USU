// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog allows you to select certain input locations for graphs and files
// ChooseLocationsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "ChooseLocationsDialog.h"
#include "RenameLocationDialog.h"
#include "LADA Control ModuleDoc.h"
#include "Lstring.h"
#include "LadaStrings.h"
#include "GraphCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);	// Message Box
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);		// Message Box
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);				// Message Box
#undef MessageBox
#define MessageBox MyMessageBox

extern void  SortDescending( int array[], int n );		// Sorts in Descending order
extern void  SortAscending( int array[], int n );		// Sorts in Ascending order
extern int   AssociateFile(char (*InputLocNameList)[2][30], int maxNum, CString filename = "", int wType = 0, int ArrayID = 0); // This fills InputLocNameList with the input locations in the FSL File
extern void  SetItemFont(UINT controlID, CWnd *window);					// Sets an item to a font
extern CFont RussianArial;							// The font used
extern int   curLanguage;								// The current language
extern LString Strings;									// The strings in all languages
/////////////////////////////////////////////////////////////////////////////
// CChooseLocationsDlg dialog


// Constructor
// inames is
// iLocSaveList is
// nSaveList is
// Available is
CChooseLocationsDlg::CChooseLocationsDlg(InputListType *iNames, int *iLocSaveList, 
										 int *nSaveList, int Available, CWnd* pParent)
										 // = MAX_INPUT_LOCATIONS
										 // = NULL
	: CDialog(CChooseLocationsDlg::IDD, pParent)
{
	//char iNames[][30][2]
	//{{AFX_DATA_INIT(CChooseLocationsDlg)
	m_nLocations = 0;
	m_WhichGraphSel = -1;
	//}}AFX_DATA_INIT
	MaxSelectedLocations = Available;
	SInputLocList = new int[MaxSelectedLocations];
	ptrSelectedItems = iLocSaveList;
	memcpy(SInputLocList,iLocSaveList,sizeof(int)*Available);
	//SInputLocList = iLocSaveList;
	AvailableStrings = Available;
	nILSaveList = nSaveList;
	InputLocNames = iNames;
	dType = SaveMonitorDlg;
	pDoc = NULL;
}

// Constructor
// doc is the current document
CChooseLocationsDlg::CChooseLocationsDlg(CLADAControlModuleDoc * doc, CWnd* pParent) // = NULL
	: CDialog(CChooseLocationsDlg::IDD, pParent)
{
	m_WhichGraphSel = doc->curWindow;
	pDoc = doc;
	InputLocNames = pDoc->InputLocationNameList;
	MaxSelectedLocations = 15;
	AvailableStrings = pDoc->nInputLocations;
	dType = DisplayLocationsDlg;
	ptrSelectedItems = pDoc->GraphCollection[m_WhichGraphSel].DataIndex;

}

CChooseLocationsDlg::~CChooseLocationsDlg()
{
	delete [] SInputLocList;
}

// Data Exchange
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

// Message Maps
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseLocationsDlg message handlers

// Called when the OK button is pressed
// Saves the list of locations selected
void CChooseLocationsDlg::OnOK() 
{
	UpdateData(TRUE);
	OnSortLocations();
	*nILSaveList = m_nLocations;
	memcpy(ptrSelectedItems,SInputLocList,sizeof(int)*MaxSelectedLocations);
	CDialog::OnOK();
}

// Called when the Cancel button is pressed
void CChooseLocationsDlg::OnCancel() 
{
	CDialog::OnCancel();
}

// Sorts the locations in Ascending Order
void CChooseLocationsDlg::OnSortLocations() 
{	
	SortAscending(SInputLocList,m_nLocations);
	m_SLocations.ResetContent();
	for (int i = 0; i < m_nLocations; i++){
		m_SLocations.AddString( InputLocNames[SInputLocList[i] /*- (dType == SaveMonitorDlg)*/][curLanguage] );
	}
}

// Called when you you press the Rename Location button
// Allows you to change the name of a location
// Determines which side you have selected and makes sure you only have one selected
void CChooseLocationsDlg::OnRenameLocation() 
{
	int SelectedRight = m_SLocations.GetSelCount();
	int SelectedLeft = m_ALocations.GetSelCount();
	int whichSelection;
	
	int whichLocation;

	if (SelectedRight == 1 && SelectedLeft == 0 ){
		m_SLocations.GetSelItems(1, &whichSelection);
		
		//if (dType == DisplayLocationsDlg)
			whichLocation = SInputLocList[whichSelection] + 1;
		//else
		//	whichLocation = SInputLocList[whichSelection];
		
	}
	else if (SelectedLeft == 1 && SelectedRight == 0 ){
		m_ALocations.GetSelItems(1, &whichSelection);
		whichLocation = whichSelection + 1;
	
	}
	else {
		MessageBox(Strings.get(IDS_M_SELECT_LOCATION),Strings.get(IDS_PROGRAM_NAME));
		SetStrings();
		return;
	}
	
	RenameLocation(whichLocation);
}

// This function allows you to rename input locations by calling the CRenameLocationDialog
void CChooseLocationsDlg::RenameLocation(int whichLocation)
{
	// this will now take a zero based location
	whichLocation--;

	//CString OldName = &InputLocNames[whichLocation][curLanguage][4];
	//char newName[31];
	//newName[0] = '\0';
	//CRenameLocationDialog(int whichLocation,
	//							 int wTextIDS,
	//							 CLADAControlModuleDoc *pDoc,
	//							 BOOL showNumber /*=TRUE */, 
	//							 CWnd* pParent /*=NULL*/)

	CRenameLocationDialog cNewName(whichLocation, IDS_INPUT_LOCATION, &InputLocNames[whichLocation], TRUE, this );
	cNewName.DoModal();
	SetStrings();
	
	//strcpy(&InputLocNames[whichLocation][curLanguage][4], newName);
	for (int i = 0; i < m_nLocations; i++){
		if (SInputLocList[i] == whichLocation /*+ (dType == SaveMonitorDlg)*/){
			m_SLocations.DeleteString( i );
			m_SLocations.InsertString( i, InputLocNames[whichLocation][curLanguage] );
		}
	}
	m_ALocations.DeleteString( whichLocation );
	m_ALocations.InsertString( whichLocation, InputLocNames[whichLocation][curLanguage] );
}

// Called when the Remove button is pressed 
// Removes the selected items from the right list
void CChooseLocationsDlg::OnRemove() 
{
	int * currRightSelections = new int[MaxSelectedLocations];
	int currRightS;
	
	currRightS = m_SLocations.GetSelCount();
	if (currRightS){
		if (dType == DisplayLocationsDlg)
		{
			if (pDoc->GraphCollection[m_WhichGraphSel].whichPane != -1)
				pDoc->paneModified[pDoc->GraphCollection[m_WhichGraphSel].whichPane] = TRUE;

		}
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
		MessageBox(Strings.get(IDS_M_NO_SELECTED_ITEMS),Strings.get(IDS_ERROR),MB_ICONEXCLAMATION);
		SetStrings();
	}
	delete [] currRightSelections;
	m_SLocations.UpdateWindow();
	UpdateData(FALSE);
}

// Called when the Insert Button is pressed
// Inserts the selected items from the left list into the right list
void CChooseLocationsDlg::OnInsert() 
{
	int * currLeftSelections = new int[AvailableStrings];
	int currLeftS;	// The number of selections in the left list
	
	currLeftS = m_ALocations.GetSelCount();

	int LocsToAdd = currLeftS;
	if (currLeftS)
	{
		if (m_nLocations < MaxSelectedLocations) 
		{
			m_ALocations.GetSelItems(AvailableStrings, currLeftSelections);

			BOOL alreadyUpdated;
			for (int i = 0; i < currLeftS && m_nLocations < MaxSelectedLocations; i++)
			{
				alreadyUpdated = FALSE;
				LocsToAdd--;
				
				for (int j = 0; j < m_nLocations; j++)
				{
					if (currLeftSelections[i] /*+ (dType == SaveMonitorDlg)*/ == SInputLocList[j])
						alreadyUpdated = TRUE;
				}
				if (!alreadyUpdated)
				{
					//if (dType == DisplayLocationsDlg){
					SInputLocList[m_nLocations++] = currLeftSelections[i];
					
					if (dType == DisplayLocationsDlg && 
						pDoc->GraphCollection[m_WhichGraphSel].whichPane != -1)
						pDoc->paneModified[pDoc->GraphCollection[m_WhichGraphSel].whichPane] = TRUE;

					m_SLocations.AddString( InputLocNames[currLeftSelections[i]][curLanguage] );
				}
				if (m_nLocations == MaxSelectedLocations && LocsToAdd != 0)
				{
					MessageBox(IDS_M_COULD_NOT_INSERT,IDS_ERROR,MB_ICONEXCLAMATION);
					SetStrings();
					break;
				}	
			}
		}

		if (m_nLocations == MaxSelectedLocations && LocsToAdd != 0){
			MessageBox(IDS_M_NO_ROOM_TO_INSERT,IDS_ERROR,MB_ICONEXCLAMATION);
			SetStrings();
			MessageBox(IDS_M_DELETE_LOCATIONS,IDS_ERROR);
			SetStrings();
		}
	}
	else {
		MessageBox(IDS_M_NO_SELECTED_ITEMS_INSERT,IDS_ERROR,MB_ICONEXCLAMATION);
		SetStrings();
	}
	UpdateData(FALSE);
	delete [] currLeftSelections;
	m_ALocations.SetSel( -1, FALSE ); // unselects all strings

}

// This is called when the Fsl File button is pressed
// It resets the contents and allows you to load the input locations from a fsl file
void CChooseLocationsDlg::OnFslFile() 
{
	if (MessageBox(IDS_M_ASSOCIATE_WILL_OVERWRITE,IDS_WARNING, MB_ICONQUESTION | MB_ICONWARNING | MB_YESNO) == IDYES)
	{
		int maxLocs;
		if (pDoc)
			maxLocs = pDoc->nInputLocations;
		else
			maxLocs = MAX_INPUT_LOCATIONS;

		AvailableStrings = AssociateFile(InputLocNames, maxLocs); //
		
		m_SLocations.ResetContent();
		m_ALocations.ResetContent();
		//memcpy(InputLocNames, AvailableInputLocations, sizeof(AvailableInputLocations));
		for (int i = 0; i < AvailableStrings; i++){
			if ( i < m_nLocations )	
				m_SLocations.AddString( InputLocNames[SInputLocList[i] ][curLanguage] );//- (dType == SaveMonitorDlg)
			m_ALocations.AddString( InputLocNames[i][curLanguage] );
		}
	}
	SetStrings();

}

// This is called when you double click on an input location in the right list box
// It allows you to rename it
void CChooseLocationsDlg::OnDblclkSLocations() 
{
	int currSel = m_SLocations.GetCurSel();
	RenameLocation(SInputLocList[currSel] + 1);
}

// This is called when you double click on an input location in the left list box
// It allows you to rename it
void CChooseLocationsDlg::OnDblclkALocations() 
{
	int currSel = m_ALocations.GetCurSel();
	RenameLocation(currSel + 1);
	
}

// This allows you the set the font of text
//void CChooseLocationsDlg::SetFontText(UINT controlID, UINT stringID){
//	::SetFontText(controlID,stringID,this);
//}

// Initialization
// Decides who is calling it and acts accordingly
// Sets the Fonts and text to the current language 
BOOL CChooseLocationsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT1)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT2)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT3)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT4)->SetFont(&RussianArial);
	GetDlgItem(IDC_FSL_FILE)->SetFont(&RussianArial);
	GetDlgItem(IDC_RENAME_LOCATION)->SetFont(&RussianArial);
	GetDlgItem(IDC_SORT_LOCATIONS)->SetFont(&RussianArial);
	GetDlgItem(IDC_INSERT)->SetFont(&RussianArial);
	GetDlgItem(IDC_REMOVE)->SetFont(&RussianArial);
	GetDlgItem(IDC_SELECT_ALLI)->SetFont(&RussianArial);
	GetDlgItem(IDC_SELECT_ALLS)->SetFont(&RussianArial);
	GetDlgItem(IDOK)->SetFont(&RussianArial);
	GetDlgItem(IDCANCEL)->SetFont(&RussianArial);
	
	GetDlgItem(IDC_WHICH_GRAPH)->SetFont(&RussianArial);
	GetDlgItem(IDC_N_LOCATIONS)->SetFont(&RussianArial);
	GetDlgItem(IDC_A_LOCATIONS)->SetFont(&RussianArial);
	GetDlgItem(IDC_S_LOCATIONS)->SetFont(&RussianArial);

	switch(dType){
	case SaveMonitorDlg:{
		
		break;
	}
	case DisplayLocationsDlg:{
		m_WhichGraph.EnableWindow(TRUE);
		m_WhichGraph.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TEXT2)->ShowWindow(SW_SHOW);
		for (int i = 0; i < pDoc->nGraphCollections; i++)
			m_WhichGraph.AddString(pDoc->GraphCollection[i].name);//CString(char('1'+i)));
		m_WhichGraph.SetCurSel(0);
		m_nLocations = pDoc->GraphCollection[m_WhichGraphSel].nItems;
		SInputLocList = new int[MaxSelectedLocations];
		memcpy(SInputLocList,pDoc->GraphCollection[m_WhichGraphSel].DataIndex, sizeof(int)*pDoc->GraphCollection[m_WhichGraphSel].nItems);
		nILSaveList = &pDoc->GraphCollection[m_WhichGraphSel].nItems;
		
		break;
	}
	}
	ShowGraphChoices();
	
	
	//for ( i = 0; i < 7; i++)
	//	SetFontText(IDC_FSL_FILE+i,IDS_MBUTTON1+i);
	//SetFontText(IDOK, IDS_OK);
	//SetFontText(IDCANCEL, IDS_CANCEL);
	//for ( i = 0; i < 4; i++)
	//	SetFontText(IDC_TEXT1+i,IDS_MTEXT1+i);
	SetStrings();

	if (pDoc)
		GetDlgItem(IDC_FSL_FILE)->EnableWindow(pDoc->nInputLocations);
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

// Called when the left Select All button is pressed
// Selects all the locations in the left box
void CChooseLocationsDlg::OnSelectAlli() 
{
	m_ALocations.SetSel( -1, TRUE );
}

// Called when the right Select All button is pressed
// Selects all the locations in the right box
void CChooseLocationsDlg::OnSelectAlls() 
{
	m_SLocations.SetSel( -1, TRUE );
}

// Called when the user clicks on text in the right box
// Allows the selection to be changed or added to
void CChooseLocationsDlg::OnSelchangeSLocations() 
{
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

// Called when the user clicks on text in the left box
// Allows the selection to be changed or added to
void CChooseLocationsDlg::OnSelchangeALocations() 
{
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
	memcpy(ptrSelectedItems,SInputLocList,sizeof(int)*MaxSelectedLocations);
	UpdateData(TRUE);
	// set the pointers to the right places in pDoc
	ptrSelectedItems = pDoc->GraphCollection[m_WhichGraphSel].DataIndex;
	memcpy(SInputLocList,ptrSelectedItems,sizeof(int)*MaxSelectedLocations);
	
	nILSaveList = &pDoc->GraphCollection[m_WhichGraphSel].nItems;
	ShowGraphChoices();
}



void CChooseLocationsDlg::SetStrings()
{
	m_ALocations.ResetContent();
	for (int i = 0; i < AvailableStrings && InputLocNames[i][curLanguage] != '\0'; i++)
		m_ALocations.AddString(InputLocNames[i][curLanguage]);

	m_SLocations.ResetContent();
	for (i = 0; i < m_nLocations; i++)
		m_SLocations.AddString( InputLocNames[SInputLocList[i]][curLanguage] );

	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_B1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_D1));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_B2));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_B3));
	GetDlgItem(IDC_FSL_FILE)->SetWindowText(Strings.get(IDS_B4));
	GetDlgItem(IDC_RENAME_LOCATION)->SetWindowText(Strings.get(IDS_B5));
	GetDlgItem(IDC_SORT_LOCATIONS)->SetWindowText(Strings.get(IDS_B6));
	GetDlgItem(IDC_INSERT)->SetWindowText(Strings.get(IDS_B7));
	GetDlgItem(IDC_REMOVE)->SetWindowText(Strings.get(IDS_B8));
	GetDlgItem(IDC_SELECT_ALLI)->SetWindowText(Strings.get(IDS_SELECTALL));
	GetDlgItem(IDC_SELECT_ALLS)->SetWindowText(Strings.get(IDS_SELECTALL));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));
	SetWindowText(Strings.get(IDS_B0));
}

BOOL CChooseLocationsDlg::PreTranslateMessage(MSG* pMsg) 
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
