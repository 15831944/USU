// ProgramVariables.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ProgramVariables.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// ProgramVariables dialog


ProgramVariables::ProgramVariables(Array<ExpressionItem *> *pVars, CWnd* pParent /*=NULL*/)
	: CDialog(ProgramVariables::IDD, pParent)
{
	//{{AFX_DATA_INIT(ProgramVariables)
	m_ReadOnly = FALSE;
	m_Array = FALSE;
	m_VName = _T("");
	m_VValue = 0.0;
	m_NElements = 0;
	//}}AFX_DATA_INIT
	ProgVariables = pVars;
	nVariables = ProgVariables->length;
}


void ProgramVariables::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProgramVariables)
	DDX_Control(pDX, IDC_VLIST, m_VList);
	DDX_Check(pDX, IDC_READONLY, m_ReadOnly);
	DDX_Check(pDX, IDC_ARRAY, m_Array);
	DDX_Text(pDX, IDC_VNAME, m_VName);
	DDX_Text(pDX, IDC_VVALUE, m_VValue);
	DDX_Text(pDX, IDC_NELEMENTS, m_NElements);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProgramVariables, CDialog)
	//{{AFX_MSG_MAP(ProgramVariables)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProgramVariables message handlers

void ProgramVariables::OnAdd() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData(TRUE)){
		if (m_VValue == (double)(int) m_VValue)
			ProgVariables->Insert(new IntConstant(int(m_VValue), new CString(m_VName)));
		else
			ProgVariables->Insert(new DoubConstant(m_VValue, new CString(m_VName)));
		nVariables++;
		ShowVariableList();
	}
}

void ProgramVariables::OnDelete() 
{
	// TODO: Add your control notification handler code here
	
}

void ProgramVariables::OnEdit() 
{
	// TODO: Add your control notification handler code here
	
}

void ProgramVariables::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL ProgramVariables::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_VList.InsertColumn(0,"Variable Name",LVCFMT_LEFT, 100, 1);
	m_VList.InsertColumn(1,"Value",LVCFMT_LEFT, 50, 2);
	ShowVariableList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ProgramVariables::ShowVariableList(){
	m_VList.DeleteAllItems();
	for (int i = 0; i < ProgVariables->length; i++){
		m_VList.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, i, NULL, 0, LVIS_SELECTED, 0, 0);
		m_VList.SetItemText(i, 0, /*(LPCSTR)*/ *(*ProgVariables)[i]->GetItemText());
		m_VList.SetItemText(i, 1, /*(LPCSTR)*/ (*ProgVariables)[i]->ValueToString());
	}
}