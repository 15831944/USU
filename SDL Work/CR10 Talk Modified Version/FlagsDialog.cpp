// FlagsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "FlagsDialog.h"
#include "global defs.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// FlagsDialog dialog


FlagsDialog::FlagsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(FlagsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(FlagsDialog)
	//}}AFX_DATA_INIT
	FlagWindowCount++;
}

// all the data that may be altered:


BOOL FlagsDialog::OnInitDialog()
{   
	//memcpy(TAvailableInputLocations, AvailableInputLocations, sizeof(AvailableInputLocations));
	//memcpy(TInputLocScreenList, InputLocScreenList, sizeof(InputLocScreenList));
	//TInputLocScreenRequests = InputLocScreenRequests;

	if (ModifyWhichFlags == 0)
		ModifyWhichFlags = USERFLAGS;

	CComboBox *cBox;
	for (int i = 0; i < 8; i++){
		cBox = (CComboBox *) GetDlgItem(IDC_FLAGFREQ1 + i);
		for (int j = 0; j < 16; j++){
			cBox->AddString(Frequencies[j]);
		}
	}
	DisplayAllFlagInfo();

	return TRUE;
}
	
void FlagsDialog::DisplayAllFlagInfo(){
	ShowWhichFlags();
	ShowToggleOn();
	for (int i = 1; i <= 8; i++){
		ShowFlagName(i);
		ShowFlagStatus(i);
		ShowToggleState(i);
	}
}

void FlagsDialog::ShowWhichFlags(){
	((CButton *) GetDlgItem(IDC_RUSERFLAGS))->SetCheck(ModifyWhichFlags == USERFLAGS);
	((CButton *) GetDlgItem(IDC_RPORTFLAGS))->SetCheck(ModifyWhichFlags == PORTFLAGS);
}

void FlagsDialog::ShowToggleOn(){
	((CButton *) GetDlgItem(IDC_CTOGGLEON))->SetCheck(DoToggleFlags[ModifyWhichFlags]);
	for (int i = 1; i <= 8; i++){
		(GetDlgItem(IDC_R1 + i - 1))->EnableWindow(DoToggleFlags[ModifyWhichFlags]);
		(GetDlgItem(IDC_RE1 + i - 1))->EnableWindow(DoToggleFlags[ModifyWhichFlags]);
		(GetDlgItem(IDC_FLAGFREQ1 + i - 1))->EnableWindow(DoToggleFlags[ModifyWhichFlags]);
	}
}

void FlagsDialog::ShowFlagName(int whichFlag){ 
	((CStatic *) GetDlgItem(IDC_FLAGNAME1 + whichFlag - 1))->SetWindowText(FlagNames[whichFlag - 1][ModifyWhichFlags]);
}
void FlagsDialog::ShowFlagStatus(int whichFlag){
	((CButton *) GetDlgItem(IDC_FSTATUS1 + whichFlag - 1))->SetCheck(FlagStatus[whichFlag - 1][ModifyWhichFlags]);
	CButton *CJustOnceButton = (CButton *) GetDlgItem(IDC_R1 + whichFlag - 1);
	BOOL justOnceButton = FlagStatus[whichFlag - 1][ModifyWhichFlags];
	if (justOnceButton)
		CJustOnceButton->SetWindowText("On");
	else
		CJustOnceButton->SetWindowText("Off");
	CJustOnceButton->SetCheck(justOnceButton);
}
void FlagsDialog::ShowToggleState(int whichFlag){
// show toggle state is a little more complicated
	//BOOL justOnceButton = toggleFlags[whichFlag - 1][ModifyWhichFlags] == JUSTONCE;
	CButton *CJustOnceButton = (CButton *) GetDlgItem(IDC_R1 + whichFlag - 1);
	BOOL justOnceButton = FlagStatus[whichFlag - 1][ModifyWhichFlags];
	if (justOnceButton)
		CJustOnceButton->SetWindowText("On");
	else
		CJustOnceButton->SetWindowText("Off");
	CJustOnceButton->SetCheck(justOnceButton);

	BOOL continualButton = toggleFlags[whichFlag - 1][ModifyWhichFlags] == CONTINUAL;
	((CButton *) GetDlgItem(IDC_RE1 + whichFlag - 1))->SetCheck(continualButton);
// next show the frequency
	((CComboBox *) GetDlgItem(IDC_FLAGFREQ1 + whichFlag - 1))->SetCurSel(toggleFlagsFreqLevel[whichFlag - 1][ModifyWhichFlags]);
}

void FlagsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FlagsDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FlagsDialog, CDialog)
	//{{AFX_MSG_MAP(FlagsDialog)
	ON_BN_CLICKED(IDC_CTOGGLEON, OnCtoggleon)
	ON_CBN_SELCHANGE(IDC_FLAGFREQ1, OnSelchangeFlagfreq1)
	ON_CBN_SELCHANGE(IDC_FLAGFREQ2, OnSelchangeFlagfreq2)
	ON_CBN_SELCHANGE(IDC_FLAGFREQ3, OnSelchangeFlagfreq3)
	ON_CBN_SELCHANGE(IDC_FLAGFREQ4, OnSelchangeFlagfreq4)
	ON_CBN_SELCHANGE(IDC_FLAGFREQ5, OnSelchangeFlagfreq5)
	ON_CBN_SELCHANGE(IDC_FLAGFREQ6, OnSelchangeFlagfreq6)
	ON_CBN_SELCHANGE(IDC_FLAGFREQ7, OnSelchangeFlagfreq7)
	ON_CBN_SELCHANGE(IDC_FLAGFREQ8, OnSelchangeFlagfreq8)
	ON_BN_CLICKED(IDC_R1, OnR1)
	ON_BN_CLICKED(IDC_R2, OnR2)
	ON_BN_CLICKED(IDC_R3, OnR3)
	ON_BN_CLICKED(IDC_R4, OnR4)
	ON_BN_CLICKED(IDC_R5, OnR5)
	ON_BN_CLICKED(IDC_R6, OnR6)
	ON_BN_CLICKED(IDC_R7, OnR7)
	ON_BN_CLICKED(IDC_R8, OnR8)
	ON_BN_CLICKED(IDC_RE1, OnRe1)
	ON_BN_CLICKED(IDC_RE2, OnRe2)
	ON_BN_CLICKED(IDC_RE3, OnRe3)
	ON_BN_CLICKED(IDC_RE4, OnRe4)
	ON_BN_CLICKED(IDC_RE5, OnRe5)
	ON_BN_CLICKED(IDC_RE6, OnRe6)
	ON_BN_CLICKED(IDC_RE7, OnRe7)
	ON_BN_CLICKED(IDC_RE8, OnRe8)
	ON_BN_CLICKED(IDC_RPORTFLAGS, OnRportflags)
	ON_BN_CLICKED(IDC_RUSERFLAGS, OnRuserflags)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FlagsDialog message handlers

void FlagsDialog::OnCtoggleon() 
{
	// TODO: Add your control notification handler code here
	NeedSetJCommand = TRUE;
	DoToggleFlags[ModifyWhichFlags] = (DoToggleFlags[ModifyWhichFlags] ? 0 : 1);
	ShowToggleOn();
}

void FlagsDialog::OnSelchangeFlagfreq1() 
{
	// TODO: Add your control notification handler code here
	
}

void FlagsDialog::OnSelchangeFlagfreq2() 
{
	// TODO: Add your control notification handler code here
	
}

void FlagsDialog::OnSelchangeFlagfreq3() 
{
	// TODO: Add your control notification handler code here
	
}

void FlagsDialog::OnSelchangeFlagfreq4() 
{
	// TODO: Add your control notification handler code here
	
}

void FlagsDialog::OnSelchangeFlagfreq5() 
{
	// TODO: Add your control notification handler code here
	
}

void FlagsDialog::OnSelchangeFlagfreq6() 
{
	// TODO: Add your control notification handler code here
	
}

void FlagsDialog::OnSelchangeFlagfreq7() 
{
	// TODO: Add your control notification handler code here
	
}

void FlagsDialog::OnSelchangeFlagfreq8() 
{
	// TODO: Add your control notification handler code here
	
}

void FlagsDialog::OnR1() { 	ChangeToggleStatus(JUSTONCE, 1); }
void FlagsDialog::OnR2() { 	ChangeToggleStatus(JUSTONCE, 2); }
void FlagsDialog::OnR3() { 	ChangeToggleStatus(JUSTONCE, 3); }
void FlagsDialog::OnR4() { 	ChangeToggleStatus(JUSTONCE, 4); }
void FlagsDialog::OnR5() { 	ChangeToggleStatus(JUSTONCE, 5); }
void FlagsDialog::OnR6() { 	ChangeToggleStatus(JUSTONCE, 6); }
void FlagsDialog::OnR7() { 	ChangeToggleStatus(JUSTONCE, 7); }
void FlagsDialog::OnR8() { 	ChangeToggleStatus(JUSTONCE, 8); }

void FlagsDialog::OnRe1(){ 	ChangeToggleStatus(CONTINUAL, 1); }
void FlagsDialog::OnRe2(){ 	ChangeToggleStatus(CONTINUAL, 2); }
void FlagsDialog::OnRe3(){ 	ChangeToggleStatus(CONTINUAL, 3); }
void FlagsDialog::OnRe4(){ 	ChangeToggleStatus(CONTINUAL, 4); }
void FlagsDialog::OnRe5(){ 	ChangeToggleStatus(CONTINUAL, 5); }
void FlagsDialog::OnRe6(){ 	ChangeToggleStatus(CONTINUAL, 6); }
void FlagsDialog::OnRe7(){ 	ChangeToggleStatus(CONTINUAL, 7); }
void FlagsDialog::OnRe8(){ 	ChangeToggleStatus(CONTINUAL, 8); }

void FlagsDialog::ChangeToggleStatus(int Status, int whichFlag){
	int cFlagDis = toggleFlags[whichFlag - 1][ModifyWhichFlags];
	int nFlagDis;
	if (Status == JUSTONCE){
		if (cFlagDis == JUSTONCE)
			nFlagDis = NEVER;
		else 
			nFlagDis = JUSTONCE;
		// disable the freq button
	}
	else { //Status == CONTINUAL
		if (cFlagDis == CONTINUAL){
			nFlagDis = NEVER;
			// disable freq button
		}
		else {
			nFlagDis = CONTINUAL;
			// enable the freq button
		}
	}
	NeedSetJCommand = TRUE;
	toggleFlags[whichFlag - 1][ModifyWhichFlags] = nFlagDis;
	ShowToggleState(whichFlag);
}

void FlagsDialog::OnRportflags() 
{
	// TODO: Add your control notification handler code here
	ModifyWhichFlags = PORTFLAGS;
	DisplayAllFlagInfo();
}

void FlagsDialog::OnRuserflags() 
{
	// TODO: Add your control notification handler code here
	ModifyWhichFlags = USERFLAGS();
	DisplayAllFlagInfo();
}

void FlagsDialog::OnOK() 
{
	// TODO: Add extra validation here
	if (m_nFlags & WF_MODALLOOP) // means it's modal???
		CDialog::OnOK();
	else
		OnClose();
}

void FlagsDialog::UpdateFlags() 
{
	for (int Flag = 1; Flag <= 8; Flag++){
		ShowFlagStatus(Flag);
	}
}

void FlagsDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
}

BOOL FlagsDialog::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	FlagWindowCount--;
	return CDialog::DestroyWindow();
}

void FlagsDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	DestroyWindow();

}
