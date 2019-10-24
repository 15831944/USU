// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog allows you to display the values of certain input locations and check to see if they 
//		are within certain bounds.
// SystemDiagDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "LADA Control ModuleDoc.h"
#include "InputLocFileInfo.h"
#include "SystemDiagDlg.h"
#include "MinMax.h"
#include "LADADIAGDlg.h"

#include "ILProperties.h"
#include "InputLocFileInfo.h"
#include "ladastrings.h"
#include "lstring.h"
#include "ProgressDialog.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern LString Strings;
extern void DisplayErrorMessage(DWORD ErrorNum, BOOL showNum = TRUE, char *AdditionalMessage = NULL);
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

extern CString IntToString(int number);
extern int curLanguage;
extern CString ValueToString(double value, int dplaces=2, BOOL applyLanguage = FALSE);
extern CFont RussianArial;
extern void SetItemFont(UINT controlID, CWnd *window);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


/////////////////////////////////////////////////////////////////////////////
// CSystemDiagDlg dialog

// Constructor
// doc is the current document
// group is the group number
// allowChangeGroup if allowed to change the group
// ILs is the pointer to the locations
// nGroup is the number of locations to get
// ptrReturnData is the pointer to the data being returned
CSystemDiagDlg::CSystemDiagDlg
(CLADAControlModuleDoc *doc, int group, BOOL showTopControls,
 int * ILs, int nGroup, double *ptrReturnData, BOOL isauto, BOOL showBottomControls,  CWnd* pParent /*=NULL*/)
	: CDialog(CSystemDiagDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystemDiagDlg)
	m_wGroup = group;
	//}}AFX_DATA_INIT
	m_ShowBottomControls = showBottomControls;
	pDoc = doc;
	values = NULL;
	m_InputList = ILs;
	m_nIList = nGroup;
	m_ptrReturnData = ptrReturnData;
	m_ShowTopControls = showTopControls;
	m_wGroup = group;
	IsAutomatic = isauto;
	fileinfo = NULL;
	m_InputLocationIndex = NULL;
}

// destructor
CSystemDiagDlg::~CSystemDiagDlg()
{
	delete [] values;
	values = NULL;
	delete [] m_InputList;
	delete [] m_InputLocationIndex;
	m_InputList = NULL;
}

// Data Exchange
void CSystemDiagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemDiagDlg)
	DDX_Control(pDX, IDC_GROUP, m_cGroup);
	DDX_Control(pDX, IDC_DIAGLIST, m_cdiag);
	DDX_CBIndex(pDX, IDC_GROUP, m_wGroup);
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(CSystemDiagDlg, CDialog)
	//{{AFX_MSG_MAP(CSystemDiagDlg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_NOTIFY(NM_DBLCLK, IDC_DIAGLIST, OnDblclkDiaglist)
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	ON_CBN_SELCHANGE(IDC_GROUP, OnSelchangeGroup)
	ON_BN_CLICKED(IDC_CREATENEWGROUP, OnCreatenewgroup)
	ON_BN_CLICKED(IDC_LOAD_VALIDATION, OnLoadValidation)
	ON_BN_CLICKED(IDC_VALIDATE_ALL, OnValidateAll)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemDiagDlg message handlers

// Initialization
// Sets Font
// Displays Data
BOOL CSystemDiagDlg::OnInitDialog()
{
	SetFont(&RussianArial);
	CDialog::OnInitDialog();
	m_cdiag.SetFont(&RussianArial);
	
	m_cdiag.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_PROPERTIES,this);
	SetItemFont(IDC_CREATENEWGROUP,this);
	SetItemFont(IDC_GROUP,this);
	SetItemFont(IDC_REFRESH,this);
	SetItemFont(IDC_SAVE,this);
	SetItemFont(IDOK,this);
	SetItemFont(IDC_VALIDATE_ALL,this);
	SetItemFont(IDC_LOAD_VALIDATION,this);
	
	m_cdiag.GetHeaderCtrl()->SetFont(&RussianArial);
	
	if (!m_ShowTopControls)
	{
		GetDlgItem(IDC_PROPERTIES)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GROUP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TEXT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CREATENEWGROUP)->ShowWindow(SW_HIDE);
	}
	
	if (!m_ShowBottomControls)
	{
		GetDlgItem(IDC_SAVE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LOAD_VALIDATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LOAD_VALIDATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_SAVE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LOAD_VALIDATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LOAD_VALIDATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_VALIDATE_ALL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_VALIDATE_ALL)->EnableWindow(FALSE);
	}
	else
	{
		m_cdiag.SetExtendedStyle(LVS_EX_CHECKBOXES);
	}
	
	CString a[5];
	a[0]=Strings.get(IDS_N5);
	a[1]=Strings.get(IDS_N6);
	a[2]=Strings.get(IDS_N7);
	a[3]=Strings.get(IDS_N8);
	a[4]=Strings.get(IDS_N9);
	
	for (int x=0;x<5;x++)
	{
		m_cdiag.InsertColumn(x,a[x],LVCFMT_LEFT,80);
	}

	if (m_InputList)  // if a specified list of input locations is given
	{
		int * temp = m_InputList;
		m_InputList = new int[m_nIList];
		memcpy(m_InputList,temp,sizeof(int)*m_nIList);
		// that way I won't delete data that is passed into the file...
		m_InputLocationIndex = new int[m_nIList];
		for (int i = 0; i < m_nIList; i++)
		{
			m_InputLocationIndex[i] = pDoc->InputLocationToIndex[m_InputList[i]-1];//takes a zero based location
		}
	}
	else // if no specified list is given
	{
		if (pDoc->nILFiles > 0)
		{
			GetDlgItem(IDC_GROUP)->ShowWindow(SW_SHOW);
			SetGroupInfo();

			if (m_ShowTopControls)
			{
				for (x = 0; x < pDoc->nILFiles; x++)
					m_cGroup.AddString(pDoc->m_ILData[x].m_Name);
				m_cGroup.SetCurSel(m_wGroup);
			}
			else
			{
				
				m_cGroup.AddString(fileinfo->m_Name);
				m_cGroup.SetCurSel(0);
			}
		}
		else // no specified group, no specified list, no locations...
		{
			GetDlgItem(IDC_TEXT2)->EnableWindow(FALSE);
			GetDlgItem(IDC_GROUP)->EnableWindow(FALSE);
			GetDlgItem(IDC_PROPERTIES)->EnableWindow(FALSE);
			m_nIList = 0;
		}
	}

	if (!pDoc->commObject)
	{
		MessageBox(IDS_M_CANT_GET_DATA, IDS_ERROR, MB_ICONWARNING);
		//m_cdiag.GetHeaderCtrl()->EnableWindow(FALSE);
		//GetDlgItem(IDC_DIAGLIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	}

	if ( m_nIList )
	{
		// get the data
		load();
	}
	else
	{
		//MessageBox(IDS_M_NO_DATA_TO_RETRIEVE, IDS_ERROR, MB_ICONWARNING);
		m_wGroup = -1;
		//GetDlgItem(IDC_PROPERTIES)->EnableWindow(FALSE);
		//GetDlgItem(IDC_GROUP)->EnableWindow(FALSE);
		//GetDlgItem(IDC_TEXT1)->EnableWindow(FALSE);
		//GetDlgItem(IDC_TEXT2)->EnableWindow(FALSE);
		
	}
	SetStrings();
	if (IsAutomatic)
		OnOK();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// Saves the information to a file
void CSystemDiagDlg::OnSave() 
{
	// Ok, if there is a group, save it under that name, if it is not a group,
	// save it under the name the user gives...
	// In both cases show the save dialog box.
	CTime theTime = CTime::GetCurrentTime();
	CString fileName;

	char fileNameBuff[100];
	CString s = theTime.Format( "%H;%M;%S, %B %d, %Y" );
	if (m_wGroup >= 0)	
		wsprintf(fileNameBuff,"%s\\%s %s.%s", pDoc->dataFolder, pDoc->m_ILData[m_wGroup].m_Name, s, InputLocationExtension);
	else
		wsprintf(fileNameBuff,"%s\\%s %s.%s", pDoc->dataFolder, "Input Locations", s, InputLocationExtension);
		
	fileName = fileNameBuff;
	
	CFileDialog fDlg(FALSE, InputLocationExtension, fileName, OFN_HIDEREADONLY, "Input Location Files (*.il)|*.il|All Files(*.*)|*.*|",NULL);

	if (fDlg.DoModal() != IDOK)
		return;


	HANDLE hFile = CreateFile(fDlg.GetPathName(), 
			GENERIC_WRITE, 
			FILE_SHARE_READ, 
			NULL, 
			CREATE_ALWAYS, 
			FILE_ATTRIBUTE_ARCHIVE, 
			NULL);

	if (hFile == INVALID_HANDLE_VALUE){
		CloseHandle(hFile);
		DisplayErrorMessage(GetLastError());
		return;
	}
	
	CFile file((int)hFile);
	CArchive ar(&file,CArchive::store);
	CString d;

	
	// add header
	// Input Locations, 1,2,3,4,5,6,7,8,9
	ar.WriteString("  Time:\t");
	ar.WriteString( theTime.Format( "%H:%M:%S, %B %d, %Y\n") );
	if (m_wGroup >= 0)
	ar.WriteString("Group Name:\t " + pDoc->m_ILData[m_wGroup].m_Name + "\n");
	ar.WriteString("Name\tValue\tMin\tMax\tStatus\n");
	for (int i = 0; i < m_nIList; i++)
	{
		// To write the input location number to file:
		//d = ValueToString(ptrInfo->m_Locations[i] + 1, 0);
		// To write the input location name to file
		if (m_InputLocationIndex[i] != -1)
			d = pDoc->InputLocationNameList[m_InputLocationIndex[i]][curLanguage];
		else
			d = "? CR10X I.L. " + IntToString(m_InputList[i]);
	
		ar.WriteString(d + "\t");

		if (pDoc->commObject)
			ar.WriteString(ValueToString(values[i])+"\t");
		else
			ar.WriteString("???\t");
		
		if (m_InputLocationIndex[i] != -1 && pDoc->m_HasMinMax[m_InputLocationIndex[i]])
		{
			double min = pDoc->m_minValues[m_InputLocationIndex[i]];
			double max = pDoc->m_maxValues[m_InputLocationIndex[i]];
			ar.WriteString(ValueToString(min)+"\t");
			ar.WriteString(ValueToString(max)+"\t");
			if (pDoc->commObject)
				ar.WriteString((values[i] >= min && values[i] <= max)?"OK\n":"FAIL\n");
			else
				ar.WriteString("???\n");
		}
		else
		{
			ar.WriteString("-\t-\t-\n");
		}
	}

	ar.Close();
	file.Close();
}

//Selects something or other
void CSystemDiagDlg::OnSelect() 
{
}

// Exits
void CSystemDiagDlg::OnOK() 
{
	GetCheckedItems();
	CDialog::OnOK();
}

// Gets the values that are requested
void CSystemDiagDlg::GetValues()
{
	DWORD startTime = timeGetTime();
	BOOL collectCancelled = FALSE;
	CString wText;
	ProgressDialog CollectProgress(&collectCancelled, wText, Strings.get(IDS_M_COLLECTING_LOCATIONS));
	CollectProgress.Create(PROGRESS_DIALOG);
	pDoc->GetInputLocations(m_InputList,m_nIList,values, 24);
	CollectProgress.Close();
	
	if (m_ptrReturnData)
	{
		memcpy(m_ptrReturnData,values,sizeof(double)*m_nIList);
	}
	DWORD totalTime = timeGetTime() - startTime;
	//MessageBox(IntToString((int)totalTime), CString("Total Time"));
}

// loads a group and displays the information
void CSystemDiagDlg::load()
{
	//CWaitCursor wCursor;

	m_cdiag.DeleteAllItems();

	if (pDoc->commObject)
	{
		if (values)
			delete [] values;
		values = new double[m_nIList];
		GetValues();
	}

	for (int x = 0; x < m_nIList; x++)
	{
		if (m_InputLocationIndex[x] != -1)
			m_cdiag.InsertItem( x, pDoc->InputLocationNameList[m_InputLocationIndex[x]][curLanguage]);
		else 
			m_cdiag.InsertItem( x, "? CR10X I.L. " + IntToString(m_InputList[x]) );

		if (pDoc->commObject)
			m_cdiag.SetItemText(x,1,ValueToString(values[x]));
		else
			m_cdiag.SetItemText(x,1,"???");

		if (m_InputLocationIndex[x] != -1 && pDoc->m_HasMinMax[m_InputLocationIndex[x]])
		{
			double min = pDoc->m_minValues[m_InputLocationIndex[x]];
			double max = pDoc->m_maxValues[m_InputLocationIndex[x]];
			m_cdiag.SetItemText(x,2,ValueToString(min));
			m_cdiag.SetItemText(x,3,ValueToString(max));
			if (pDoc->commObject)
				m_cdiag.SetItemText(x,4,(values[x] >= min && values[x] <= max)?"OK":"FAIL");
			else
				m_cdiag.SetItemText(x,4,"???");
		}
		else
		{
			m_cdiag.SetItemText(x,2,"-");
			m_cdiag.SetItemText(x,3,"-");
			m_cdiag.SetItemText(x,4,"-");
		}

	}
	SetCheckedItems();
	for (int c = 0; c < 5; c++)
		m_cdiag.SetColumnWidth(c,LVSCW_AUTOSIZE_USEHEADER);
	
}

/*void CSystemDiagDlg::OnDoubleclicked1001() 
{

}
*/

// Allows you to set the bounds for an input location
void CSystemDiagDlg::OnDblclkDiaglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int wIL = m_cdiag.GetSelectionMark();
	if ( wIL != -1 && m_InputLocationIndex[wIL] != -1 )
	{
		MinMax dlg( pDoc->m_minValues[m_InputLocationIndex[wIL]], pDoc->m_maxValues[m_InputLocationIndex[wIL]] );
		if (dlg.DoModal() == IDOK)
		{
			m_cdiag.SetItemText(wIL,2,ValueToString(dlg.m_vmin));
			m_cdiag.SetItemText(wIL,3,ValueToString(dlg.m_vmax));
		
			pDoc->m_minValues[m_InputLocationIndex[wIL]] = dlg.m_vmin;
			pDoc->m_maxValues[m_InputLocationIndex[wIL]] = dlg.m_vmax;
			pDoc->m_HasMinMax[m_InputLocationIndex[wIL]] = TRUE;
			pDoc->m_DoValidation[m_InputLocationIndex[wIL]] = dlg.m_Validate;
			m_cdiag.SetCheck(wIL,dlg.m_Validate);

			if (values)
				m_cdiag.SetItemText(wIL,4,(values[wIL] >= dlg.m_vmin && values[wIL] <= dlg.m_vmax)?"OK":"FAIL");
			else
				m_cdiag.SetItemText(wIL,4,"???");
			pDoc->SetModifiedFlag();
		}
		SetStrings();	
	}
	
	*pResult = 0;
}

// Allows you to change the properties of a group
void CSystemDiagDlg::OnProperties() 
{
	CInputLocFileInfo fInfo;

	if (m_wGroup != -1)
	{
		fInfo = *fileinfo;
		CILProperties gDlg(pDoc, &fInfo, m_wGroup);
		if (gDlg.DoModal() == IDOK)
		{
			*fileinfo = fInfo;
			CWaitCursor wCursor;
			if (gDlg.doResetTimer)
				ResetGroupTimer();
			SetGroupInfo();
			load();
			m_cGroup.DeleteString( m_wGroup );
			m_cGroup.InsertString( m_wGroup, fileinfo->m_Name );
			m_cGroup.SetCurSel( m_wGroup );
			pDoc->SetModifiedFlag();
		}
		SetStrings();	
		LVCOLUMN* x=new LVCOLUMN;
		char* tempst=new char[20];
		for (int y=0;y<5;y++)
		{
			x->mask=LVCF_TEXT;
			x->pszText=tempst;
			x->cchTextMax=20;
			m_cdiag.GetColumn(y,x);
			CString a=Strings.get(IDS_N5+y);
			LPTSTR temp=a.GetBuffer(0);
			x->pszText=temp;
			m_cdiag.SetColumn(y,x);
		}
		delete [] tempst;
		delete [] x;
	}

}

// Select a different group
void CSystemDiagDlg::OnSelchangeGroup() 
{
	GetCheckedItems();	// SAVE THE STATUS OF THE CURRENT GROUP
	m_wGroup = m_cGroup.GetCurSel(); // FIND OUT WHICH GROUP WE ARE ON NOW
	SetGroupInfo(); // UPDATE HEADERS, ETC
	load(); // SET DATA
}

void CSystemDiagDlg::ResetGroupTimer()
{
	// this function will reset an input location group timer (see the function
	// SetILTimer in CLADAControlModuleView
	if (pDoc->InCommMode && pDoc->m_pMainView)
	{
		lpfnTimerCallback lpfnTimer = &ResetTimer;
		CTime currentTime = CTime::GetCurrentTime();
		pDoc->m_pMainView->SetILTimer(m_wGroup, lpfnTimer, currentTime);
		// this function will set or reset the timer depending on the value of
		// m_Do
	}
}

// Allows you to create a new group to be displayed
void CSystemDiagDlg::OnCreatenewgroup() 
{
	CInputLocFileInfo fInfo;

	CILProperties gDlg(pDoc, &fInfo, pDoc->nILFiles);
	if (gDlg.DoModal() == IDOK)
	{
		if (pDoc->nILFiles == 0)
		{
			GetDlgItem(IDC_TEXT2)->EnableWindow(TRUE);
			GetDlgItem(IDC_GROUP)->EnableWindow(TRUE);
			GetDlgItem(IDC_PROPERTIES)->EnableWindow(TRUE);
		}
		
		m_wGroup = pDoc->nILFiles;
		pDoc->nILFiles++;
		//pDoc->saveLocations = TRUE;
		CInputLocFileInfo * tempPtr = new CInputLocFileInfo[pDoc->nILFiles];
		for (int i = 0; i < pDoc->nILFiles - 1; i++)
		{
			tempPtr[i] = pDoc->m_ILData[i];
		}
		tempPtr[i] = fInfo; // copies what was in the temporary object to the permaneant
		delete [] pDoc->m_ILData;
		pDoc->m_ILData = tempPtr; // reassigns m_ILData to the new location in memory
		CWaitCursor wCursor;
		
		ResetGroupTimer();
		
		SetGroupInfo(); // UPDATE HEADERS, ETC
		load(); // SET DATA
		
		m_cGroup.DeleteString( m_wGroup );
		m_cGroup.AddString( fileinfo->m_Name );
		m_cGroup.SetCurSel( m_wGroup );
		pDoc->SetModifiedFlag();
	}
	SetStrings();	
		LVCOLUMN* x=new LVCOLUMN;
		char* tempst=new char[20];
		for (int y=0;y<5;y++)
		{
			x->mask=LVCF_TEXT;
			x->pszText=tempst;
			x->cchTextMax=20;
			m_cdiag.GetColumn(y,x);
			CString a=Strings.get(IDS_N5+y);
			LPTSTR temp=a.GetBuffer(0);
			x->pszText=temp;
			m_cdiag.SetColumn(y,x);
		}
		delete [] tempst;
		delete [] x;
	
}

// Sets the new list information
void CSystemDiagDlg::SetGroupInfo()
{
	fileinfo = &pDoc->m_ILData[m_wGroup];//doc->m_DiagGroup];
	m_nIList = fileinfo->m_nLocations;
	delete [] m_InputList;
	delete [] m_InputLocationIndex;
	m_InputList = new int[m_nIList];
	m_InputLocationIndex = new int[m_nIList];

	memcpy(m_InputLocationIndex, fileinfo->m_Locations, sizeof(int) * m_nIList);
	for (int i = 0; i < m_nIList; i++)
	{
		m_InputList[i] = pDoc->InputLocationList[m_InputLocationIndex[i]] + 1;
	}

}

// Sets the text to the current language
void CSystemDiagDlg::SetStrings()
{
	static int cLang = -1;
	if (cLang != curLanguage)
	{
		SetWindowText(Strings.get(IDS_N0));
		GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_N1));
		GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_N2));
		GetDlgItem(IDC_PROPERTIES)->SetWindowText(Strings.get(IDS_N3));
		GetDlgItem(IDC_CREATENEWGROUP)->SetWindowText(Strings.get(IDS_N4));
		GetDlgItem(IDC_SAVE)->SetWindowText(Strings.get(IDS_N10));
		GetDlgItem(IDC_REFRESH)->SetWindowText(Strings.get(IDS_N13));
		GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
		GetDlgItem(IDC_VALIDATE_ALL)->SetWindowText(Strings.get(IDS_N11));
		GetDlgItem(IDC_LOAD_VALIDATION)->SetWindowText(Strings.get(IDS_N12));
		LVCOLUMN* x=new LVCOLUMN;
		char* tempst=new char[20];
		for (int y=0;y<5;y++)
		{
			x->mask=LVCF_TEXT;
			x->pszText=tempst;
			x->cchTextMax=20;
			m_cdiag.GetColumn(y,x);
			CString a=Strings.get(IDS_N5+y);
			LPTSTR temp=a.GetBuffer(0);
			x->pszText=temp;
			m_cdiag.SetColumn(y,x);
		}
		delete [] tempst;
		delete [] x;
		cLang = curLanguage;
	}
}

BOOL CSystemDiagDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		ResetStrings();
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CSystemDiagDlg::ResetStrings()
{
	SetStrings();	
		LVCOLUMN* x=new LVCOLUMN;
		char* tempst=new char[20];
		for (int y=0;y<5;y++)
		{
			x->mask=LVCF_TEXT;
			x->pszText=tempst;
			x->cchTextMax=20;
			m_cdiag.GetColumn(y,x);
			CString a=Strings.get(IDS_N5+y);
			LPTSTR temp=a.GetBuffer(0);
			x->pszText=temp;
			m_cdiag.SetColumn(y,x);
		}
		delete [] tempst;
		delete [] x;
}

void CSystemDiagDlg::OnLoadValidation() 
{
	// TODO: Add your control notification handler code here
	CString dlgString = "Validation Files (*.txt)|*.txt|All Files (*.*)|*.*|";
	CFileDialog OpenFileDialogBox(TRUE, "txt", NULL, 
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
			dlgString,
			NULL);
		OpenFileDialogBox.m_ofn.lpstrTitle = "Select Validation File";
	if ( OpenFileDialogBox.DoModal() == IDOK )
	{
		
		int location=0;
		double min=0, max;
		char comments[80];
		ifstream fin(OpenFileDialogBox.GetPathName().GetBuffer(0));
		int first;
		
		while ((first = fin.peek()) && !fin.eof())
		{
			if (first == '\\' || first == '/')
			{
				fin.getline(comments,80);
				continue;
			}
			if (!(fin >> location >> min >> max))
				break;
			int index = pDoc->InputLocationToIndex[location-1];
			if (index != -1)
			{
				pDoc->m_minValues[index] = min;
				pDoc->m_maxValues[index] = max;
				pDoc->m_HasMinMax[index] = TRUE;
				pDoc->m_DoValidation[index] = TRUE;
				break;
			}
			
			fin.getline(comments,80);
		}
		fin.close();
		pDoc->SetModifiedFlag();
		SetCheckedItems();
		load();
	}
}

void CSystemDiagDlg::GetCheckedItems()
{
	for ( int i = 0; i < m_nIList; i++)
	{
		if (m_InputLocationIndex[i] != -1 && pDoc->m_HasMinMax[m_InputLocationIndex[i]])
		{
			pDoc->m_DoValidation[m_InputLocationIndex[i]] = m_cdiag.GetCheck(i);
			pDoc->SetModifiedFlag();
		}
	}
}

void CSystemDiagDlg::SetCheckedItems()
{
	for ( int i = 0; i < m_nIList; i++)
	{
		if (m_InputLocationIndex[i] != -1)
			m_cdiag.SetCheck(i,pDoc->m_DoValidation[m_InputLocationIndex[i]]);
	}
}

void CSystemDiagDlg::ValidateAll()
{
	for ( int i = 0; i < m_nIList; i++)
	{
		if (m_InputLocationIndex[i] != -1 && pDoc->m_HasMinMax[m_InputLocationIndex[i]])
		{
			pDoc->m_DoValidation[m_InputLocationIndex[i]] = TRUE;
			m_cdiag.SetCheck(i,TRUE);
			pDoc->SetModifiedFlag();
		}
		else 
		{
			m_cdiag.SetCheck(i,FALSE);
		}
	}	
}

void CSystemDiagDlg::OnValidateAll() 
{
	// TODO: Add your control notification handler code here
	ValidateAll();
}

void CSystemDiagDlg::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	load();
}
