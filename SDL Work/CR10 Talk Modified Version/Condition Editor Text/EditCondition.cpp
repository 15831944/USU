// EditCondition.cpp : implementation file
//

#include "stdafx.h"
#include "EditCondition.h"
#include "ChooseItem.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// EditCondition dialog


EditCondition::EditCondition(CWnd* pParent /*=NULL*/)
	: CDialog(EditCondition::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditCondition)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL EditCondition::OnInitDialog(){
	CDialog::OnInitDialog();
	
	for (int i = 0; i < 6; i++){
	
		int rValue = m_Item_List.AddString(ConditionalItems[i]);
	}
	
	m_Item_List.SetCurSel(Variable);
	OnSelchangeItemList();

	return FALSE; // unless the focus is explicitly set to a control
}

void EditCondition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditCondition)
	DDX_Control(pDX, IDC_DIRECTION_TEXT, m_DirectionText);
	DDX_Control(pDX, IDC_VARIABLE, m_Variable);
	DDX_Control(pDX, IDC_ITEM_LIST, m_Item_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditCondition, CDialog)
	//{{AFX_MSG_MAP(EditCondition)
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, OnSelchangeItemList)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditCondition message handlers

void EditCondition::OnSelchangeItemList() 
{

	//m_Item_List.SetFocus();
	m_Variable.ResetContent();
	int CurSel;
	if ((CurSel = m_Item_List.GetCurSel()) != LB_ERR){
		if (CurSel != Parenthesis){
			m_Variable.EnableWindow(TRUE);
			m_Variable.ShowWindow(SW_SHOW);
		}
		if (CurSel < IntConst){
			m_Variable.ShowDropDown(TRUE);
			for (int i = 0; i < 6; i++)
				m_Variable.AddString(ConditionalItemsSpecific[CurSel][i]);
			
		}
		switch (CurSel){
			case Variable:
				m_DirectionText.SetWindowText("Please select the type of variable to add");
				break;
			case Operator:
				m_DirectionText.SetWindowText("Please select the operator to add to the expression");
				break;
			case RelOperator:
				m_DirectionText.SetWindowText("Please choose a relational operator to insert");
				break;
			case IntConst:
				m_DirectionText.SetWindowText("Please enter an integer value");
				m_Variable.ShowDropDown(FALSE);
				break;
			case DoubConst:
				m_DirectionText.SetWindowText("Please enter a floating type value");
				m_Variable.ShowDropDown(FALSE);
				break;
			case Parenthesis:
				m_DirectionText.SetWindowText("Scroll cursor to insert location for parenthesis");
				m_Variable.EnableWindow(FALSE);
				m_Variable.ShowWindow(SW_HIDE);
				break;
		}
		m_Variable.SetFocus();
		m_Variable.SetCurSel(0);
	}
}

void EditCondition::OnInsert() 
{
	// TODO: Add your control notification handler code here
	int CurItem = m_Item_List.GetCurSel();
	int CurSpecItem = m_Variable.GetCurSel();
	switch (CurItem){
		case Variable:
			switch (CurSpecItem){
			case InputLocation:
				// choose which input location
				int whichLocation;
				CChooseItem selList(&whichItem, AvailableLocations, numberItems, "Select Input Location",this);
				break;
			case FlagValue:
				// choose flag
				break;
			case ProgramRunTime:
				break;
			default:
				MessageBox("Please select a valid list box item");
			}
			break;
		case Operator:
			m_DirectionText.SetWindowText("Please select the operator to add to the expression");
			break;
		case RelOperator:
			m_DirectionText.SetWindowText("Please choose a relational operator to insert");
			break;
		case IntConst:
			m_DirectionText.SetWindowText("Please enter an integer value");
			m_Variable.ShowDropDown(FALSE);
			break;
		case DoubConst:
			m_DirectionText.SetWindowText("Please enter a floating type value");
			m_Variable.ShowDropDown(FALSE);
			break;
		case Parenthesis:
			m_DirectionText.SetWindowText("Scroll cursor to insert location for parenthesis");
			m_Variable.EnableWindow(FALSE);
			m_Variable.ShowWindow(SW_HIDE);
			break;
		}
	
}
