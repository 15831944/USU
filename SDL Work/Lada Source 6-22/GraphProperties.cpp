// This is Version 1.0 PLEASE DOCUMENT CHANGES
// GraphProperties.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "GraphProperties.h"

#include "LADA Control ModuleDoc.h"
#include "ChooseLocationsDialog.h"
#include "LString.h"
#include "LadaStrings.h"
#include "LADA Control ModuleView.h"
#include "HistoryClass.h"
#include "GraphCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

extern CFont RussianArial;
extern void SetItemFont(UINT controlID, CWnd *window);
extern CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4);
extern int  curLanguage;
extern LString Strings;
extern UINT IDS_TEMP;
extern CTimeSpan DataPlotFreqTable[7];
//extern int BackPointsTable[4];
//extern CTimeSpan DataRetrievalFreqTable[10];
//extern CTimeSpan DataSaveFreqTable[7];
//extern CTimeSpan CreateFileFreqTable[3];
//extern int CreateFileBySizeTable[3];

/////////////////////////////////////////////////////////////////////////////
// CGraphProperties dialog


CGraphProperties::CGraphProperties(CLADAControlModuleDoc *pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CGraphProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphProperties)
	m_NPoints = 0;
	m_DataPlotFreqSel = -1;
	m_wGraphSel = -1;
	m_VTimeSpan = _T("");
	m_AutoWrap = FALSE;
	m_UseMilitaryTime = FALSE;
	m_GraphName = _T("");
	m_wShowGraph = -1;
	//}}AFX_DATA_INIT
	doc = pDoc;
	m_MinPoints = 10;
	m_MaxPoints = 1000;
	ptrCurrentGraph = NULL;
}


void CGraphProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphProperties)
	DDX_Control(pDX, IDC_SHOW_GRAPH, m_cShowGraph);
	DDX_Control(pDX, IDC_BACKCOLOR, m_cBackColor);
	DDX_Control(pDX, IDC_NPOINTS, m_Points);
	DDX_Control(pDX, IDC_ACTIVE_LIST, m_ActiveList);
	DDX_Control(pDX, IDC_DATA_PLOT_FREQ, m_CDataPlotFreq);
	DDX_Control(pDX, IDC_C_WGRAPH, m_CGraphSel);
	DDX_Text(pDX, IDC_NPOINTS, m_NPoints);
	DDX_CBIndex(pDX, IDC_DATA_PLOT_FREQ, m_DataPlotFreqSel);
	DDX_CBIndex(pDX, IDC_C_WGRAPH, m_wGraphSel);
	DDX_Text(pDX, IDC_VIS_TIME_SPAN, m_VTimeSpan);
	DDX_Check(pDX, IDC_AUTO_WRAP, m_AutoWrap);
	DDX_Check(pDX, IDC_MILITARY_TIME, m_UseMilitaryTime);
	DDX_Text(pDX, IDC_GRAPH_NAME, m_GraphName);
	DDX_CBIndex(pDX, IDC_SHOW_GRAPH, m_wShowGraph);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphProperties, CDialog)
	//{{AFX_MSG_MAP(CGraphProperties)
	ON_BN_CLICKED(IDC_EDIT_LIST, OnEditList)
	ON_CBN_SELCHANGE(IDC_C_WGRAPH, OnSelchangeCWgraph)
	ON_CBN_SELCHANGE(IDC_DATA_PLOT_FREQ, OnSelchangeDataPlotFreq)
	ON_EN_KILLFOCUS(IDC_NPOINTS, OnKillfocusNpoints)
	ON_BN_CLICKED(IDC_BACKCOLOR, OnBackcolor)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DELETE_GRAPH, OnDeleteGraph)
	ON_BN_CLICKED(IDC_NEW_GRAPH, OnNewGraph)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphProperties message handlers

void CGraphProperties::OnEditList() 
{
	// TODO: Add your control notification handler code here
	
	doc->curWindow = m_wGraphSel;
	CChooseLocationsDlg getNamesDlg(doc);
	if (getNamesDlg.DoModal()==IDOK)
	{
		m_ActiveList.DeleteAllItems();
		for (int i = 0; i < ptrCurrentGraph->nItems; i++)
		{
			SetStatus(i);
		}
		doc->SetModifiedFlag();
	}
}

void CGraphProperties::OnSelchangeCWgraph() 
{
	int prevSel = m_wGraphSel;
	UpdateData(TRUE);
	
	if (doc->nGraphCollections > 0)
	{
		// save status of current graph
		if (ptrCurrentGraph)
		{
			if (ptrCurrentGraph->name != m_GraphName)
			{
				ptrCurrentGraph->name = m_GraphName;
				m_CGraphSel.DeleteString(prevSel);
				m_CGraphSel.InsertString(prevSel,m_GraphName);
			}

			GetCheckedItems();

			// check to see if we are replacing a graph...
			// don't display this graph
			// pane 1
			// pane 2
			// pane 3
						
			if (m_wShowGraph && (m_wShowGraph - 1 != ptrCurrentGraph->whichPane))
			{
				// clear the current graph from a pane if it is already in a pane
				if (ptrCurrentGraph->whichPane != -1)
				{
					doc->PaneToCollectionIndex[ptrCurrentGraph->whichPane] = -1;	
				}
				
				// if there is already a graph in the desired location,
				if (doc->PaneToCollectionIndex[m_wShowGraph-1] != -1)
				{
					// try and find an empty spot for it
					for (int i = 0; i < doc->nPanes; i++)
					{
						if (i != m_wShowGraph - 1 && doc->PaneToCollectionIndex[i] == -1)
						{
							doc->GraphCollection[doc->PaneToCollectionIndex[m_wShowGraph-1]].whichPane = i;
							doc->PaneToCollectionIndex[i] = doc->PaneToCollectionIndex[m_wShowGraph-1];
							break;
						}
					}
				}
							
				ptrCurrentGraph->whichPane = m_wShowGraph-1;
				doc->PaneToCollectionIndex[m_wShowGraph-1] = prevSel;
			}
			else if (m_wShowGraph == 0)
			{
				doc->PaneToCollectionIndex[ptrCurrentGraph->whichPane] = -1;
				ptrCurrentGraph->whichPane = -1;
			}
			
			doc->paneModified[ptrCurrentGraph->whichPane] = TRUE;
		}

		//if (prevSel != m_wGraphSel) // if we have actually switched graphs
		//{
			ptrCurrentGraph = &doc->GraphCollection[m_wGraphSel];
			m_ActiveList.DeleteAllItems();		
			m_GraphName = ptrCurrentGraph->name;
			
			m_wShowGraph = ptrCurrentGraph->whichPane + 1;

			for (int i = 0; i < ptrCurrentGraph->nItems; i++)
			{
				SetStatus(i);
			}
		//}

	}
	else
	{
		// disable all graph stuff, except for 'new'
		m_ActiveList.DeleteAllItems();
		m_GraphName = "";
		m_wShowGraph = 0;

	}
	UpdateData(FALSE);
	
	
}

void CGraphProperties::OnSelchangeDataPlotFreq() 
{
	UpdateData(TRUE);
	ShowVisibleSpan();
}

BOOL CGraphProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT1)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT4)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT6)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT3)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT2)->SetFont(&RussianArial);
	GetDlgItem(IDC_SHOW_GRAPH)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT7)->SetFont(&RussianArial);
	GetDlgItem(IDC_EDIT_LIST)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT9)->SetFont(&RussianArial);
	GetDlgItem(IDC_MILITARY_TIME)->SetFont(&RussianArial);
	GetDlgItem(IDC_AUTO_WRAP)->SetFont(&RussianArial);
	GetDlgItem(IDOK)->SetFont(&RussianArial);
	
	GetDlgItem(IDC_DATA_PLOT_FREQ)->SetFont(&RussianArial);
	GetDlgItem(IDC_NPOINTS)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT5)->SetFont(&RussianArial);
	GetDlgItem(IDC_VIS_TIME_SPAN)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_WGRAPH)->SetFont(&RussianArial);
	GetDlgItem(IDC_ACTIVE_LIST)->SetFont(&RussianArial);

	GetDlgItem(IDC_TEXT8)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT10)->SetFont(&RussianArial);
	GetDlgItem(IDC_GRAPH_NAME)->SetFont(&RussianArial);
	GetDlgItem(IDC_SHOW_GRAPH)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEW_GRAPH)->SetFont(&RussianArial);
	GetDlgItem(IDC_DELETE_GRAPH)->SetFont(&RussianArial);

	CString s;
	if (doc->nGraphCollections)
	{
		for (int i = 0; i < doc->nGraphCollections; i++)
			m_CGraphSel.AddString(doc->GraphCollection[i].name);//CString(char (i + '1')));
	}
	else
		EnableGraphs(FALSE);

	char * sPtr = s.GetBuffer(12);
	m_MaxPoints = doc->nBackPoints;
	wsprintf(sPtr,"(10 - %i)",doc->nBackPoints);
	s.ReleaseBuffer();
	GetDlgItem(IDC_TEXT5)->SetWindowText(s);

	m_InitialNPoints = m_NPoints = doc->nBackPoints;
	//m_ShowGraph = TRUE;
	m_wGraphSel = 0;
	m_DataPlotFreqSel = 0;

	for ( int i = 0; i < 7; i++)
	{
		if (doc->dataPlotFreq == DataPlotFreqTable[i])
			m_DataPlotFreqSel = i;
	}
	m_InitialGraphFreqSel = m_DataPlotFreqSel;

	m_ActiveList.SetExtendedStyle(LVS_EX_CHECKBOXES);
	CRect rect;
	m_ActiveList.GetClientRect(&rect);
	m_ActiveList.InsertColumn(0,LPCTSTR(NULL),LVCFMT_LEFT,rect.Width());
	
	m_AutoWrap = doc->DoAutoWrap;
	m_UseMilitaryTime = doc->m_UseMilitaryTime;

	SetStrings(FALSE);
	if (doc->nGraphCollections > 0)
	{	
		m_wGraphSel = 0;
	}
	OnSelchangeCWgraph();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGraphProperties::SetStatus(int whichItem)
{
	m_ActiveList.InsertItem(whichItem,
		doc->InputLocationNameList[ptrCurrentGraph->DataIndex[whichItem]][curLanguage]);
	m_ActiveList.SetCheck(whichItem, ptrCurrentGraph->isItemChecked[whichItem]);
}

void CGraphProperties::ShowVisibleSpan()
{
	UpdateData(TRUE);
	CTimeSpan visibleSpan = CTimeSpan(time_t(DataPlotFreqTable[m_DataPlotFreqSel].GetTotalSeconds() * m_NPoints));
	m_VTimeSpan = GetTimeSpan(visibleSpan, 2);
	UpdateData(FALSE);
}

void CGraphProperties::OnKillfocusNpoints() 
{
	// TODO: Add your control notification handler code here
	m_Points.SetModify(TRUE);
	OnOK();
}

void CGraphProperties::GetCheckedItems()
{
	BOOL checkStatus;
	for ( int i = 0; i < ptrCurrentGraph->nItems; i++)
	{
		checkStatus = m_ActiveList.GetCheck(i);
		if (ptrCurrentGraph->isItemChecked[i] != checkStatus)
		{
			ptrCurrentGraph->isItemChecked[i] = checkStatus;
			if (ptrCurrentGraph->whichPane != -1)
				doc->paneModified[ptrCurrentGraph->whichPane] = TRUE;
		}
	}
}

void CGraphProperties::OnOK() 
{
	// TODO: Add extra validation here
	if (m_Points.GetModify()){
		UpdateData(TRUE);
		if (m_NPoints > m_MaxPoints){
			m_NPoints = m_MaxPoints;
			UpdateData(FALSE);
		}
		else if (m_NPoints < m_MinPoints){
			m_NPoints = m_MinPoints;
			UpdateData(FALSE);
		}

		m_Points.SetModify(FALSE);

		ShowVisibleSpan();
		return;
	}
	UpdateData();
	if (m_InitialGraphFreqSel != m_DataPlotFreqSel)
	{
		doc->SetModifiedFlag();
		doc->m_pMainView->KillTimer(UPDATE_GRAPH_TIMER);
		doc->dataPlotFreq = DataPlotFreqTable[m_DataPlotFreqSel];
		DWORD timeS = doc->dataPlotFreq.GetTotalSeconds() * 1000;
		doc->m_pMainView->SetTimer(UPDATE_GRAPH_TIMER,timeS,NULL);
		
	}
	if (m_InitialNPoints != m_NPoints)
	{
		// the number of back points changed...

	}

	OnSelchangeCWgraph();
	//GetCheckedItems();
	doc->DoAutoWrap = m_AutoWrap;
	doc->m_UseMilitaryTime = m_UseMilitaryTime;

	CDialog::OnOK();
}

void CGraphProperties::SetStrings(BOOL Update)
{
	if (Update)
		UpdateData(TRUE);

	int prevSel = m_DataPlotFreqSel;
	
	SetWindowText(Strings.get(IDS_E0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_E1));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_E2));
	GetDlgItem(IDC_TEXT6)->SetWindowText(Strings.get(IDS_E3));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_E4));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_E5));
	GetDlgItem(IDC_SHOW_GRAPH)->SetWindowText(Strings.get(IDS_E6));
	GetDlgItem(IDC_TEXT7)->SetWindowText(Strings.get(IDS_E7));
	GetDlgItem(IDC_EDIT_LIST)->SetWindowText(Strings.get(IDS_E8));
	GetDlgItem(IDC_TEXT9)->SetWindowText(Strings.get(IDS_E9));
	GetDlgItem(IDC_MILITARY_TIME)->SetWindowText(Strings.get(IDS_E11));
	GetDlgItem(IDC_AUTO_WRAP)->SetWindowText(Strings.get(IDS_E12));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	
	GetDlgItem(IDC_TEXT8)->SetWindowText(Strings.get(IDS_E13));
	GetDlgItem(IDC_TEXT10)->SetWindowText(Strings.get(IDS_E14));
	GetDlgItem(IDC_NEW_GRAPH)->SetWindowText(Strings.get(IDS_E15));
	GetDlgItem(IDC_DELETE_GRAPH)->SetWindowText(Strings.get(IDS_E16));

	GetDlgItem(IDC_SHOW_GRAPH)->SetWindowText(Strings.get(IDS_E12));

	m_CDataPlotFreq.ResetContent();
	for ( int i = 0 ; i < 7; i++)
		m_CDataPlotFreq.AddString(Strings.get(IDS_N_DATAPLOT1 + i));
	
	m_ActiveList.DeleteAllItems();

	if (ptrCurrentGraph)
	{
		for ( i = 0; i < ptrCurrentGraph->nItems; i++)
		{
			SetStatus(i);
		}
	}
	m_DataPlotFreqSel = prevSel;
	UpdateData(FALSE);
	ShowVisibleSpan();

}

void CGraphProperties::OnBackcolor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog pickColorDlg;
	if (pickColorDlg.DoModal() == IDOK)
	{
		doc->SetModifiedFlag();
		doc->backgroundBrushColor = pickColorDlg.GetColor();
		doc->backgroundBrush.DeleteObject();
		doc->backgroundBrush.CreateSolidBrush(doc->backgroundBrushColor);
		Invalidate(FALSE);
	}
	SetStrings();
}

void CGraphProperties::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	 //TODO: Add your message handler code here
	CRect rect;
	CRect dog;
	m_cBackColor.GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	dc.FillRect(&rect,&doc->backgroundBrush);
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CGraphProperties::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CGraphProperties::OnDeleteGraph() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_wGraphSel != -1)
	{
		CString eng = Strings.get(IDS_M_SURE_DELETE, ENGLISH) + ptrCurrentGraph->name + CString("\"?");
		CString rus = Strings.get(IDS_M_SURE_DELETE, RUSSIAN) + ptrCurrentGraph->name + CString("\"?");
		Strings.set(eng,rus,IDS_TEMP);

		if (MessageBox(IDS_TEMP,IDS_PROGRAM_NAME, MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			// if this group is in a pane de-select it
			if (ptrCurrentGraph->whichPane != -1)
			{
				doc->PaneToCollectionIndex[ptrCurrentGraph->whichPane] = -1;
			}
			m_CGraphSel.DeleteString( m_wGraphSel );

			// decrement the number of graphs
			doc->nGraphCollections--;
			CGraphCollection *temp = doc->GraphCollection;
			// resize the array
			if (doc->nGraphCollections)
			{
				doc->GraphCollection = new CGraphCollection[doc->nGraphCollections];
				// copy the data from the old array to the new array
				for (int wGroup = 0; wGroup < m_wGraphSel; wGroup++)
					doc->GraphCollection[wGroup] = temp[wGroup];	
				for (; wGroup < doc->nGraphCollections; wGroup++)
					doc->GraphCollection[wGroup] = temp[wGroup + 1];
				m_wGraphSel = 0;
				//m_cGroup.SetCurSel( 0 );
			}
			else
			{
				m_wGraphSel = -1;
				EnableGraphs(FALSE);
				doc->GraphCollection = NULL;
			}
			// delete the old array
			delete [] temp;
			// update the display
			ptrCurrentGraph = NULL;
			UpdateData(FALSE);
			OnSelchangeCWgraph();
			doc->SetModifiedFlag();
		}
		SetStrings();	
	}

	UpdateData(FALSE);
}

void CGraphProperties::OnNewGraph() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wCursor;
	OnSelchangeCWgraph();

	if (doc->nGraphCollections == 0)
		EnableGraphs(TRUE);

	doc->nGraphCollections++;
		
	CGraphCollection * tempPtr = new CGraphCollection[doc->nGraphCollections];

	for (int i = 0; i < doc->nGraphCollections - 1; i++)
		tempPtr[i] = doc->GraphCollection[i];
	
	CGraphCollection newGraphC;
	tempPtr[i] = newGraphC; // copies what was in the temporary object to the permaneant
	delete [] doc->GraphCollection;
	doc->GraphCollection = tempPtr; // reassigns m_ILData to the new location in memory
	
	m_CGraphSel.AddString( newGraphC.name );
	if (m_wGraphSel != -1)
		ptrCurrentGraph = &doc->GraphCollection[m_wGraphSel];
	else
		ptrCurrentGraph = NULL;
	m_wGraphSel = doc->nGraphCollections-1;

	UpdateData(FALSE);
	OnSelchangeCWgraph();
	doc->SetModifiedFlag();

}

void CGraphProperties::EnableGraphs(BOOL enable)
{
	// these controls should all be enabled when there is one or 
	// more graph groups in the system
	GetDlgItem(IDC_TEXT3)->EnableWindow(enable);
	GetDlgItem(IDC_C_WGRAPH)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT2)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT10)->EnableWindow(enable);
	GetDlgItem(IDC_GRAPH_NAME)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT8)->EnableWindow(enable);
	GetDlgItem(IDC_SHOW_GRAPH)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT7)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT_LIST)->EnableWindow(enable);
	GetDlgItem(IDC_ACTIVE_LIST)->EnableWindow(enable);
	GetDlgItem(IDC_DELETE_GRAPH)->EnableWindow(enable);
}
