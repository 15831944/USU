// MonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MonitorDlg.h"
#include "global defs.h"

#include "RenameLocation.h"
#include "CR10 Talk Main.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/


/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog


CMonitorDlg::CMonitorDlg(CMainWindow* pParent /*=NULL*/)
	: CDialog(CMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMonitorDlg)
	m_LSValue = 0;
	m_SaveFinalStorage = FALSE;
	//}}AFX_DATA_INIT
	pParentWindow = pParent;
	m_LSValue = InputLocSaveRequests;
	m_SaveFinalStorage = SaveFinalStorage;
}

BOOL CMonitorDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();      // TODO: Add extra initialization here
	memcpy(TFreqLevel, FreqLevel, sizeof(FreqLevel));
	memcpy(TUpdateItems, UpdateItems, sizeof(UpdateItems));
	memcpy(TAvailableInputLocations, AvailableInputLocations, sizeof(AvailableInputLocations));
	memcpy(TInputLocScreenList, InputLocScreenList, sizeof(InputLocScreenList));
	TInputLocScreenRequests = InputLocScreenRequests;
	TInputLocSaveRequests = InputLocSaveRequests;

	for (int i = 0; i < MAX_INPUT_LOCATIONS; i++){
		if ( i < TInputLocScreenRequests )	
			m_Selected_Locations.AddString( TAvailableInputLocations[TInputLocScreenList[i] - 1] );
		m_Available_Locations.AddString( TAvailableInputLocations[i] );
	}
	
	for (i = 0; i < 16; i++){
		m_Save_Locations_Freq.AddString(Frequencies[i]);
		m_Input_Locations_Freq.AddString(Frequencies[i]);
		m_CR10_Info_Freq.AddString(Frequencies[i]);
		
	}	
		
	m_Input_Locations_Freq.SetCurSel(TFreqLevel[INPUT_LOCATIONS]);
	m_CR10_Info_Freq.SetCurSel(TFreqLevel[CR10_INFO]);
	m_Save_Locations_Freq.SetCurSel(TFreqLevel[SAVE_LOCATIONS]);

	//char textNum[5];
	//wsprintf(textNum,"%i",TInputLocSaveRequests);
	//m_sEdit1.SetWindowText(textNum);

	ShowInputLocations(UpdateItems[INPUT_LOCATIONS]);
	ShowCR10Info(UpdateItems[CR10_INFO]);
	ShowSaveLocations(UpdateItems[SAVE_LOCATIONS]);
	
	return TRUE;   // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE}
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitorDlg)
	DDX_Control(pDX, IDC_SAVE_FS, m_SaveFS);
	DDX_Control(pDX, IDC_STEXT2, m_sText2);
	DDX_Control(pDX, IDC_STEXT3, m_sText3);
	DDX_Control(pDX, IDC_LTEXT1, m_lText1);
	DDX_Control(pDX, IDC_SAVE_LOCATIONS_FREQ, m_Save_Locations_Freq);
	DDX_Control(pDX, IDC_SEDIT, m_sEdit1);
	DDX_Control(pDX, IDC_STEXT1, m_sText1);
	DDX_Control(pDX, IDC_SAVE_LOCATIONS_C, m_Save_Locations);
	DDX_Control(pDX, IDC_MTEXT1, m_mText1);
	DDX_Control(pDX, IDC_SELECTED_LOCATIONS_L, m_Selected_Locations);
	DDX_Control(pDX, IDC_RENAME_B, m_Rename);
	DDX_Control(pDX, IDC_REMOVE_B, m_Remove);
	DDX_Control(pDX, IDC_INSERT_B, m_Insert);
	DDX_Control(pDX, IDC_INPUT_LOCATIONS_FREQ, m_Input_Locations_Freq);
	DDX_Control(pDX, IDC_CR10_INFO_FREQ, m_CR10_Info_Freq);
	DDX_Control(pDX, IDC_AVAILABLE_LOCATIONS_L, m_Available_Locations);
	DDX_Control(pDX, IDC_INPUT_LOCATIONS_C, m_Input_Locations);
	DDX_Control(pDX, IDC_CR10_INFO_C, m_CR10_Info);
	DDX_Text(pDX, IDC_SEDIT, m_LSValue);
	DDV_MinMaxInt(pDX, m_LSValue, 0, 256);
	DDX_Check(pDX, IDC_SAVE_FS, m_SaveFinalStorage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CMonitorDlg)
	ON_BN_CLICKED(IDC_CR10_INFO_C, OnCr10InfoC)
	ON_BN_CLICKED(IDC_INPUT_LOCATIONS_C, OnInputLocationsC)
	ON_CBN_SELCHANGE(IDC_CR10_INFO_FREQ, OnSelchangeCr10InfoFreq)
	ON_CBN_SELCHANGE(IDC_INPUT_LOCATIONS_FREQ, OnSelchangeInputLocationsFreq)
	ON_LBN_DBLCLK(IDC_AVAILABLE_LOCATIONS_L, OnDblclkAvailableLocationsL)
	ON_LBN_DBLCLK(IDC_SELECTED_LOCATIONS_L, OnDblclkSelectedLocationsL)
	ON_BN_CLICKED(IDC_RENAME_B, OnRenameB)
	ON_BN_CLICKED(IDC_INSERT_B, OnInsertB)
	ON_BN_CLICKED(IDC_REMOVE_B, OnRemoveB)
	ON_BN_CLICKED(IDC_SORT_LOCATIONS, OnSortLocations)
	ON_BN_CLICKED(IDC_FSL_FILE, OnFslFile)
	ON_BN_CLICKED(IDC_SAVE_LOCATIONS_C, OnSaveLocationsC)
	ON_CBN_SELCHANGE(IDC_SAVE_LOCATIONS_FREQ, OnSelchangeSaveLocationsFreq)
	ON_BN_CLICKED(IDC_SAVE_FS, OnSaveFs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg message handlers

void CMonitorDlg::OnCr10InfoC() 
{
	// TODO: Add your control notification handler code here
	ShowCR10Info(TUpdateItems[CR10_INFO] = (TUpdateItems[CR10_INFO] ? FALSE : TRUE));
}

void CMonitorDlg::ShowCR10Info(BOOL Check)
{
	DWORD sCommand = (Check ? SW_SHOW : SW_HIDE);
	m_CR10_Info.SetCheck(Check);
	m_CR10_Info_Freq.EnableWindow(Check);
	m_CR10_Info_Freq.ShowWindow(sCommand);
	m_mText1.ShowWindow(sCommand);
	if (Check) m_CR10_Info_Freq.SetFocus();
}

void CMonitorDlg::OnInputLocationsC() 
{
	// TODO: Add your control notification handler code here
	// disable everything inside the input locations box.
	
	ShowInputLocations(TUpdateItems[INPUT_LOCATIONS] = (TUpdateItems[INPUT_LOCATIONS] ? FALSE : TRUE));
}

void CMonitorDlg::ShowInputLocations(BOOL Check /*= TUpdateItems[INPUT_LOCATIONS*/)
{
	DWORD sCommand = (Check ? SW_SHOW : SW_HIDE);
	m_Input_Locations.SetCheck(Check);
	m_Available_Locations.EnableWindow(Check);
	m_Selected_Locations.EnableWindow(Check);
	m_Input_Locations_Freq.EnableWindow(Check);
	m_Insert.EnableWindow(Check);
	m_Remove.EnableWindow(Check);
	m_Rename.EnableWindow(Check);
	m_lText1.ShowWindow(sCommand);
	m_Input_Locations_Freq.ShowWindow(sCommand);
	if (Check) m_Input_Locations_Freq.SetFocus();
}

void CMonitorDlg::OnSelchangeFreq(CComboBox &whichFreq, int whichID){
	int iCurSel = whichFreq.GetCurSel();
	if (iCurSel == CB_ERR ) {
		MessageBox( "Select an item.","Choices",MB_ICONWARNING);
		return;
	}
	TFreqLevel[whichID] = iCurSel;
}

void CMonitorDlg::OnSelchangeCr10InfoFreq() 
{ OnSelchangeFreq(m_CR10_Info_Freq, CR10_INFO); }

void CMonitorDlg::OnSelchangeInputLocationsFreq() 
{ OnSelchangeFreq(m_Input_Locations_Freq, INPUT_LOCATIONS); }

void CMonitorDlg::OnSelchangeSaveLocationsFreq() 
{ OnSelchangeFreq(m_Save_Locations_Freq, SAVE_LOCATIONS); }

void CMonitorDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CMonitorDlg::OnOK() 
{
	// TODO: Add extra validation here
	memcpy(AvailableInputLocations, TAvailableInputLocations, sizeof(TAvailableInputLocations));
	if (memcmp(InputLocScreenList, TInputLocScreenList, sizeof(TInputLocScreenList))){
		NeedSetJCommand = TRUE;
		memcpy(InputLocScreenList, TInputLocScreenList, sizeof(TInputLocScreenList));
	}
	memcpy(FreqLevel, TFreqLevel, sizeof(TFreqLevel));
	memcpy(UpdateItems, TUpdateItems, sizeof(TUpdateItems));
	if (InputLocScreenRequests != TInputLocScreenRequests){
		NeedSetJCommand = TRUE;
		InputLocScreenRequests = TInputLocScreenRequests;
	}
	UpdateData(TRUE);
	InputLocSaveRequests = m_LSValue;
	SaveFinalStorage = m_SaveFinalStorage;

	CDialog::OnOK();
}

void CMonitorDlg::OnRenameB() 
{
	// TODO: Add your control notification handler code here
	int SelectedRight = m_Selected_Locations.GetSelCount();
	int SelectedLeft = m_Available_Locations.GetSelCount();
	int whichSelection;
	
	int whichLocation;

	if (SelectedRight == 1 && SelectedLeft == 0 ){
		m_Selected_Locations.GetSelItems(1, &whichSelection);
		whichLocation = TInputLocScreenList[whichSelection];
		
	}
	else if (SelectedLeft == 1 && SelectedRight == 0 ){
		m_Available_Locations.GetSelItems(1, &whichSelection);
		whichLocation = whichSelection + 1;
	
	}
	else {
		MessageBox("Please select one location to rename.","Rename");
		return;
	}
	
	RenameB(whichLocation);
}

void CMonitorDlg::OnDblclkAvailableLocationsL() 
{
	// TODO: Add your control notification handler code here
	//m_Available_Locations.GetCurrentMessage();
	int currSel = m_Available_Locations.GetCurSel();
	RenameB(currSel + 1);
	
}

void CMonitorDlg::OnDblclkSelectedLocationsL() 
{
	// TODO: Add your control notification handler code here
	int currSel = m_Available_Locations.GetCurSel();
	RenameB(TInputLocScreenList[currSel]);
}

void CMonitorDlg::RenameB(int whichLocation){
	CString OldName = TAvailableInputLocations[whichLocation - 1].Mid(4);
	char newName[31];
	newName[0] = '\0';
	CRenameLocation cNewName(OldName, newName,
		"Input Location", "Rename Input Location Dialog", whichLocation, TRUE, this );
	cNewName.DoModal();
	TAvailableInputLocations[whichLocation - 1].Replace(OldName, newName);
	for (int i = 0; i < TInputLocScreenRequests; i++){
		if (TInputLocScreenList[i] == whichLocation ){
			m_Selected_Locations.DeleteString( i );
			m_Selected_Locations.InsertString( i, TAvailableInputLocations[whichLocation - 1] );
		}
	}
	m_Available_Locations.DeleteString( whichLocation - 1 );
	m_Available_Locations.InsertString( whichLocation - 1, TAvailableInputLocations[whichLocation - 1] );

}

void CMonitorDlg::OnInsertB() 
{
	// TODO: Add your control notification handler code here
	int currLeftSelections[MAX_INPUT_LOCATIONS];
	int currLeftS;
	
	currLeftS = m_Available_Locations.GetSelCount();

	int LocsToAdd = currLeftS;
		if (currLeftS){
		if (TInputLocScreenRequests < MAX_DISPLAY_INPUT_LOCATIONS) {
			m_Available_Locations.GetSelItems(MAX_INPUT_LOCATIONS, currLeftSelections);

			BOOL alreadyUpdated;
			for (int i = 0; i < currLeftS && TInputLocScreenRequests < MAX_DISPLAY_INPUT_LOCATIONS; i++){
				alreadyUpdated = FALSE;
				LocsToAdd--;
				
				for (int j = 0; j < TInputLocScreenRequests; j++){
					if (currLeftSelections[i] + 1 == TInputLocScreenList[j])
						alreadyUpdated = TRUE;
				}
				if (!alreadyUpdated){
					TInputLocScreenList[TInputLocScreenRequests++] = currLeftSelections[i] + 1;
					m_Selected_Locations.AddString( TAvailableInputLocations[currLeftSelections[i]] );
				}
				if (TInputLocScreenRequests == MAX_DISPLAY_INPUT_LOCATIONS && LocsToAdd != 0){
					MessageBox("Not all requested locations could be inserted","Error",MB_ICONEXCLAMATION);
					break;
				}	
			}
		}

		if (TInputLocScreenRequests == MAX_DISPLAY_INPUT_LOCATIONS && LocsToAdd != 0){
			MessageBox("There is no room to insert more input locations","Error",MB_ICONEXCLAMATION);
			MessageBox("Please delete currently selected input locations\n"
				       "before inserting more input locations.","Warning");
		}
	}
	else {
		MessageBox("There are no items selected to insert.","Error",MB_ICONEXCLAMATION);
	}
	m_Available_Locations.SetSel( -1, FALSE ); // unselects all strings
}

void CMonitorDlg::OnRemoveB() 
{
	// TODO: Add your control notification handler code here
	int currRightSelections[MAX_DISPLAY_INPUT_LOCATIONS];
	int currRightS;
	
	currRightS = m_Selected_Locations.GetSelCount();
	if (currRightS){
		m_Selected_Locations.GetSelItems(MAX_DISPLAY_INPUT_LOCATIONS, currRightSelections);
		SortDescending(currRightSelections, currRightS );
		for (int i = 0; i < currRightS; i++){
			m_Selected_Locations.DeleteString( currRightSelections[i] );
			TInputLocScreenRequests--;
			for (int j = currRightSelections[i]; j < TInputLocScreenRequests; j++)
				TInputLocScreenList[j] = TInputLocScreenList[j+1];
		}

	}
	else {
		MessageBox("There are no items selected to remove.","Error",MB_ICONEXCLAMATION);
	}
	m_Selected_Locations.UpdateWindow();
}


void CMonitorDlg::OnSortLocations() 
{
	// TODO: Add your control notification handler code here
	SortAscending(TInputLocScreenList,TInputLocScreenRequests);
	m_Selected_Locations.ResetContent();
	for (int i = 0; i < TInputLocScreenRequests; i++){
		m_Selected_Locations.AddString( TAvailableInputLocations[TInputLocScreenList[i] - 1] );
	}
}

void CMonitorDlg::OnFslFile() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Associating an FSL file will overwrite existing input"
		"location names with those in an FSL file."
		"Do you wish to continue?","Warning",MB_ICONQUESTION | MB_ICONWARNING | MB_YESNO) == IDYES){
		pParentWindow->AssociateFSLFile();
		m_Selected_Locations.ResetContent();
		m_Available_Locations.ResetContent();
		memcpy(TAvailableInputLocations, AvailableInputLocations, sizeof(AvailableInputLocations));
		for (int i = 0; i < MAX_INPUT_LOCATIONS; i++){
			if ( i < TInputLocScreenRequests )	
				m_Selected_Locations.AddString( TAvailableInputLocations[TInputLocScreenList[i] - 1] );
			m_Available_Locations.AddString( TAvailableInputLocations[i] );
		}
	}
}

void CMonitorDlg::OnSaveLocationsC() 
{
	// TODO: Add your control notification handler code here
	ShowSaveLocations(TUpdateItems[SAVE_LOCATIONS] = (TUpdateItems[SAVE_LOCATIONS] ? FALSE : TRUE));
}

void CMonitorDlg::ShowSaveLocations(BOOL Check /*= TUpdateItems[SAVE_LOCATIONS]*/ )
{
	DWORD sCommand = (Check ? SW_SHOW : SW_HIDE);
	m_Save_Locations.SetCheck(Check);
	m_Save_Locations_Freq.EnableWindow(Check);
	m_sEdit1.EnableWindow(Check);
	m_Save_Locations_Freq.ShowWindow(sCommand);
	m_sText1.ShowWindow(sCommand);
	m_sText2.ShowWindow(sCommand);
	m_sText3.ShowWindow(sCommand);
	m_sEdit1.ShowWindow(sCommand);
	
	if (Check) m_Save_Locations_Freq.SetFocus();
}



void CMonitorDlg::OnSaveFs() 
{
	m_SaveFinalStorage = (m_SaveFinalStorage ? FALSE : TRUE);
	m_SaveFS.SetCheck(m_SaveFinalStorage);
	
}
