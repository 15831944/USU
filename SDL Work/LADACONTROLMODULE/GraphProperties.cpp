// GraphProperties.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "GraphProperties.h"

#include "LADA Control ModuleDoc.h"
#include "ChooseLocationsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFont smallRussianArial;
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);
extern void SetItemFont(UINT controlID, CWnd *window);
extern CString GetTimeSpan(const CTimeSpan & C);
extern int  curLanguage;

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
	m_ShowGraph = FALSE;
	m_DataPlotFreqSel = -1;
	m_wGraphSel = -1;
	m_VTimeSpan = _T("");
	//}}AFX_DATA_INIT
	doc = pDoc;
	m_MinPoints = 10;
	m_MaxPoints = 1000;
}


void CGraphProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphProperties)
	DDX_Control(pDX, IDC_NPOINTS, m_Points);
	DDX_Control(pDX, IDC_ACTIVE_LIST, m_ActiveList);
	DDX_Control(pDX, IDC_DATA_PLOT_FREQ, m_CDataPlotFreq);
	DDX_Control(pDX, IDC_C_WGRAPH, m_CGraphSel);
	DDX_Text(pDX, IDC_NPOINTS, m_NPoints);
	DDX_Check(pDX, IDC_SHOW_GRAPH, m_ShowGraph);
	DDX_CBIndex(pDX, IDC_DATA_PLOT_FREQ, m_DataPlotFreqSel);
	DDX_CBIndex(pDX, IDC_C_WGRAPH, m_wGraphSel);
	DDX_Text(pDX, IDC_VIS_TIME_SPAN, m_VTimeSpan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphProperties, CDialog)
	//{{AFX_MSG_MAP(CGraphProperties)
	ON_BN_CLICKED(IDC_EDIT_LIST, OnEditList)
	ON_BN_CLICKED(IDC_SHOW_GRAPH, OnShowGraph)
	ON_CBN_SELCHANGE(IDC_C_WGRAPH, OnSelchangeCWgraph)
	ON_CBN_SELCHANGE(IDC_DATA_PLOT_FREQ, OnSelchangeDataPlotFreq)
	ON_EN_KILLFOCUS(IDC_NPOINTS, OnKillfocusNpoints)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphProperties message handlers

void CGraphProperties::OnEditList() 
{
	// TODO: Add your control notification handler code here
	doc->curWindow = m_wGraphSel;
	CChooseLocationsDlg getNamesDlg(doc);
	getNamesDlg.DoModal();
	m_ActiveList.DeleteAllItems();
	for (int i = 0; i < doc->nDataGraph[m_wGraphSel]; i++)
	{
		SetStatus(i);
	}
}

void CGraphProperties::OnShowGraph() 
{
	// TODO: Add your control notification handler code here
	
}

void CGraphProperties::OnSelchangeCWgraph() 
{
	// TODO: Add your control notification handler code here
	GetCheckedItems();
	UpdateData(TRUE);
	m_ActiveList.DeleteAllItems();
	for (int i = 0; i < doc->nDataGraph[m_wGraphSel]; i++)
	{
		SetStatus(i);
	}
}

void CGraphProperties::OnSelchangeDataPlotFreq() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ShowVisibleSpan();
}

BOOL CGraphProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetFont(&smallRussianArial);
	for (int i = 0; i < 6; i++)
		SetItemFont(IDC_TEXT1 + i, this);
	for ( i = 0; i < 2; i++)
		SetItemFont(IDC_SHOW_GRAPH + i, this);
	SetItemFont(IDOK, this);
	CString s;

	for (i = 0; i < doc->numGraphs; i++)
		m_CGraphSel.AddString(CString(char (i + '1')));


	for (i = 0 ; i < 7; i++){
		s.LoadString(IDS_N_DATAPLOT1 + i);
		m_CDataPlotFreq.AddString(s);
	}

	char * sPtr = s.GetBuffer(12);
	m_MaxPoints = doc->nBackPoints;
	wsprintf(sPtr,"(10 - %i)",doc->nBackPoints);
	s.ReleaseBuffer();
	GetDlgItem(IDC_TEXT5)->SetWindowText(s);

	m_NPoints = doc->nBackPoints;
	m_ShowGraph = TRUE;
	m_wGraphSel = 0;
	m_DataPlotFreqSel = 0;

	for ( i = 0; i < 7; i++){
		if (doc->dataPlotFreq == DataPlotFreqTable[i])
			m_DataPlotFreqSel = i;
	}
	m_ActiveList.SetExtendedStyle(LVS_EX_CHECKBOXES);
	CRect rect;
	m_ActiveList.GetClientRect(&rect);
	m_ActiveList.InsertColumn(0,LPCTSTR(NULL),LVCFMT_LEFT,rect.Width());

	m_ActiveList.DeleteAllItems();
	for ( i = 0; i < doc->nDataGraph[m_wGraphSel]; i++)
	{
		SetStatus(i);
	}

	UpdateData(FALSE);
	ShowVisibleSpan();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGraphProperties::SetStatus(int whichItem)
{
	m_ActiveList.InsertItem(whichItem,
		doc->InputLocationNameList[doc->DataIndex[m_wGraphSel][whichItem]][curLanguage]);
	m_ActiveList.SetCheck(whichItem, doc->ItemChecked[m_wGraphSel][whichItem]);
}

void CGraphProperties::ShowVisibleSpan()
{
	UpdateData(TRUE);
	CTimeSpan visibleSpan = CTimeSpan(time_t(DataPlotFreqTable[m_DataPlotFreqSel].GetTotalSeconds() * m_NPoints));
	m_VTimeSpan = GetTimeSpan(visibleSpan);
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
	for ( int i = 0; i < doc->nDataGraph[m_wGraphSel]; i++)
	{
		checkStatus = m_ActiveList.GetCheck(i);
		if (doc->ItemChecked[m_wGraphSel][i] != checkStatus){
			doc->ItemChecked[m_wGraphSel][i] = checkStatus;
			doc->graphListModified[m_wGraphSel] = TRUE;
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
	GetCheckedItems();
	CDialog::OnOK();
}
/*
void CGraphProperties::OnItemchangedActiveList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 1;//0;
}

void CGraphProperties::OnClickActiveList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_Counter++;
	UpdateData(FALSE);

	DWORD pos = GetMessagePos();
    CPoint pt(LOWORD(pos), HIWORD(pos));
    m_ActiveList.ScreenToClient(&pt);

    // Get indexes of the first and last visible items in listview
    // control.
    int index = m_ActiveList.GetTopIndex();
    int last_visible_index = index + m_ActiveList.GetCountPerPage();
    if (last_visible_index > m_ActiveList.GetItemCount())
        last_visible_index = m_ActiveList.GetItemCount();

	//wStatus &= ~mask;

    // Loop until number visible items has been reached.
    while (index <= last_visible_index)
    {
        // Get the bounding rectangle of an item. If the mouse
        // location is within the bounding rectangle of the item,
        // you know you have found the item that was being clicked.
		CRect r;
        m_ActiveList.GetItemRect(index, &r, LVIR_BOUNDS);
        if (r.PtInRect(pt))
        {
			//UINT flag = LVIS_SELECTED | LVIS_FOCUSED;
            //wList.SetItemState(index, flag, flag);
			//wStatus |= mask;
			//wList.SetSelectionMark(index);
			UINT State = m_ActiveList.GetItemState( index, LVIF_STATE ) ;
			doc->ItemChecked[m_wGraphSel][index] = (doc->ItemChecked[m_wGraphSel][index] ?
				FALSE : TRUE);
			m_ActiveList.SetCheck(index, doc->ItemChecked[m_wGraphSel][index]);
			State = m_ActiveList.GetItemState( index, LVIF_STATE ) ;
            break;
        }

          // Get the next item in listview control.
        index++;
    }
	//SetButtonStatus(mask);
	*pResult = 0;
}
*/
