// ChooseItem.cpp : implementation file
//

#include "stdafx.h"

#include "ChooseItem.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// CChooseItem dialog


CChooseItem::CChooseItem(int *whichItem, char *Items[], int nItems, const char * DlgTitle, CWnd* pParent /*=NULL*/)
	: CDialog(CChooseItem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseItem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	CurSel = whichItem;
	PtrStrings = Items;
	NumberItems = nItems;
	if (DlgTitle != NULL)
		strcpy(DialogTitle, DlgTitle);
	else
		strcpy(DialogTitle, "Choose Item");

}

BOOL CChooseItem::OnInitDialog(){
	CDialog::OnInitDialog();
	SetWindowText(DialogTitle);
	for (int i = 0; i < NumberItems; i++)
		m_ListBox.AddString(PtrStrings[i]);
	return TRUE; // unless the focus is set to a specific item
}


void CChooseItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseItem)
	DDX_Control(pDX, IDC_COMBO1, m_ListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseItem, CDialog)
	//{{AFX_MSG_MAP(CChooseItem)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseItem message handlers

void CChooseItem::OnCancel() 
{
	// TODO: Add extra cleanup here
	*CurSel = -1;
	CDialog::OnCancel();
}

void CChooseItem::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	*CurSel = m_ListBox.GetCurSel();
}
