// Find.cpp : implementation file
//

#include "stdafx.h"
#include "String Editor.h"
#include "Find.h"
#include "StringInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFind dialog


CFind::CFind(CStringEditorDoc* pdoc,CWnd* pParent /*=NULL*/)
	: CDialog(CFind::IDD, pParent)
{
	pDoc=pdoc;
	//{{AFX_DATA_INIT(CFind)
	m_label = FALSE;
	m_string = FALSE;
	m_find = _T("");
	//}}AFX_DATA_INIT
}


void CFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFind)
	DDX_Check(pDX, IDC_CHECK1, m_label);
	DDX_Check(pDX, IDC_CHECK2, m_string);
	DDX_Text(pDX, IDC_EDIT1, m_find);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFind, CDialog)
	//{{AFX_MSG_MAP(CFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFind message handlers

void CFind::OnOK() 
{
	pDoc->m_foundnumber=-1;
	UpdateData(TRUE);
	pDoc->m_findfind=m_find;
	pDoc->m_findlabel=m_label;
	pDoc->m_findstring=m_string;
	for (int x=0;(x<pDoc->m_nStrings && pDoc->m_foundnumber<0);x++)
	{
		if (m_label==TRUE && IsInside(m_find,pDoc->m_s[x].m_Symbol))
		{
			pDoc->m_foundnumber=x;
		}
		if (m_string==TRUE)
		{
			for (int y=0; y<pDoc->m_nLanguages;y++)
				if (IsInside(m_find,pDoc->m_s[x].m_Strings[y]))
				{
					pDoc->m_foundnumber=x;
				}
		}
	}
	
	CDialog::OnOK();
}

BOOL CFind::IsInside(CString a, CString b)
{
	CString temp;
	int y=b.GetLength();
	int z=a.GetLength();
	for (int x=0;x<(y-z+1);x++)
	{
		temp=b.Mid(x);
		temp=temp.Left(z);
		if (!temp.CollateNoCase(a))
		{
			return TRUE;
		}
	}
	return FALSE;
		

}

BOOL CFind::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_string=TRUE;
	m_label=TRUE;
	UpdateData(FALSE);
	GetDlgItem(IDC_EDIT1)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
