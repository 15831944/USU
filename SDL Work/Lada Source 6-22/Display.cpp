// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog displays the information gathered in checkout
// Display.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "Display.h"
#include "checkout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Display dialog

// Constructor
// prin is the information gathered from checkout
Display::Display(CCheckout* prin,CWnd* pParent /*=NULL*/)
	: CDialog(Display::IDD, pParent)
{
	print=prin;
	//{{AFX_DATA_INIT(Display)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

//  Data Exchange
void Display::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Display)
	DDX_Control(pDX, IDC_DISPLAYBOX, m_display);
	//}}AFX_DATA_MAP
}


// Message Maps
BEGIN_MESSAGE_MAP(Display, CDialog)
	//{{AFX_MSG_MAP(Display)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Display message handlers

// Initializes dialog
// Displays data
BOOL Display::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_display.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_display.InsertColumn(0,"Probe       ");
	m_display.InsertColumn(1,"Computer Value");
	m_display.InsertColumn(2,"User Value");
	m_display.InsertColumn(3,"Units");
	
	for (int x=0;x<47;x++)
	{
		m_display.InsertItem(x,print->data[x][0],0);
		m_display.SetItemText(x,1,print->data[x][1]);
		m_display.SetItemText(x,2,print->data[x][2]);
		m_display.SetItemText(x,3,print->units[x]);
	}

	for (int i=0; i<4; i++)
		m_display.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
