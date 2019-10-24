// SelectTestObject.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SelectTestObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectTestObject dialog


SelectTestObject::SelectTestObject(CString *words, int *position, int &nItems, BOOL IsDelete /*=FALSE*/, CWnd* pParent /*=NULL*/)
	: CDialog(SelectTestObject::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectTestObject)
	//}}AFX_DATA_INIT
	m_IsDelete = IsDelete;
	m_NItems = &nItems;
	m_TArray = words;
	m_Object = position;
	m_curSel = -1;
	if (IsDelete){
		for (int i = 0; i < *m_NItems; i++)
			m_Object[i] = -1;
	}
	else
		*m_Object = 0;
}



void SelectTestObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectTestObject)
	DDX_Control(pDX, IDC_NUM_SELECTED, m_NumSelected);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectTestObject, CDialog)
	//{{AFX_MSG_MAP(SelectTestObject)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectTestObject message handlers

void SelectTestObject::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	if (!m_IsDelete){
		if (m_curSel != -1)
			m_List1.SetSel( m_curSel, FALSE );

		m_List1.GetSelItems(1,&m_curSel);
	}

}

void SelectTestObject::OnOK() 
{
	// TODO: Add extra validation here
	//int nSelected = m_List1.GetSelCount();
	if (!m_IsDelete)
		m_List1.GetSelItems( 1, m_Object );
	else
		m_List1.GetSelItems( *m_NItems, m_Object );

	*m_NItems = m_List1.GetSelCount();
	CDialog::OnOK();
}

BOOL SelectTestObject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_IsDelete){
		SetWindowText("Select object(s) to delete");
	}

	for (int i = 0; i < *m_NItems; i++)
		m_List1.AddString(m_TArray[i]);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
