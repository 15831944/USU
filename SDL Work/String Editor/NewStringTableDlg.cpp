// NewStringTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "String Editor.h"
#include "NewStringTableDlg.h"

#include "String EditorDoc.h"
#include "StringInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewStringTableDlg dialog


CNewStringTableDlg::CNewStringTableDlg(CStringEditorDoc *p, CWnd* pParent /*=NULL*/)
	: CDialog(CNewStringTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewStringTableDlg)
	m_FontName = _T("");
	m_langName = _T("");
	m_langNumber = 0;
	m_nLanguages = 0;
	m_fSize = 0;
	//}}AFX_DATA_INIT
	pDoc = p;
	m_ptrNames = NULL;
	IsInitialized = FALSE;
}


void CNewStringTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewStringTableDlg)
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
	DDX_Control(pDX, IDC_NLANGUAGES, m_CNLanguages);
	DDX_Control(pDX, IDC_LNUMBER, m_CLNumber);
	DDX_Text(pDX, IDC_FONTNAME, m_FontName);
	DDX_Text(pDX, IDC_LNAME, m_langName);
	DDV_MaxChars(pDX, m_langName, 30);
	DDX_Text(pDX, IDC_LNUMBER, m_langNumber);
	DDX_Text(pDX, IDC_NLANGUAGES, m_nLanguages);
	DDV_MinMaxInt(pDX, m_nLanguages, 1, 20);
	DDX_Text(pDX, IDC_FSIZE, m_fSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewStringTableDlg, CDialog)
	//{{AFX_MSG_MAP(CNewStringTableDlg)
	ON_BN_CLICKED(IDC_CHANGEFONT, OnChangefont)
	ON_EN_CHANGE(IDC_NLANGUAGES, OnChangeNlanguages)
	ON_EN_CHANGE(IDC_LNUMBER, OnChangeLnumber)
	ON_EN_CHANGE(IDC_LNAME, OnChangeLname)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewStringTableDlg message handlers

void CNewStringTableDlg::OnChangefont() 
{
	// TODO: Add your control notification handler code here
	
	
	
	CFontDialog newFontDlg(&m_LogFont,CF_SCREENFONTS|CF_LIMITSIZE|CF_INITTOLOGFONTSTRUCT|CF_TTONLY);
	newFontDlg.m_cf.nSizeMin = 8;
	newFontDlg.m_cf.nSizeMax = 16;
	if (newFontDlg.DoModal() == IDOK)
	{
		memcpy(&m_LogFont,newFontDlg.m_cf.lpLogFont,sizeof(LOGFONT));
		m_FontName = m_LogFont.lfFaceName;
		m_fSize = newFontDlg.GetSize() / 10;
		UpdateData(FALSE);
	}
}

void CNewStringTableDlg::OnChangeNlanguages() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (IsInitialized)
	{
		char sBuf[4];
		m_CNLanguages.GetWindowText(sBuf,5);
		if (strlen(sBuf) > 0)
		{
			
			int pnl = m_nLanguages;
			if (UpdateData())
			{
				m_Spin.SetRange(1,m_nLanguages);
				m_Spin.EnableWindow(m_nLanguages > 1);
				m_CLNumber.EnableWindow(m_nLanguages > 1);
				
				CString *tPtr = new CString[m_nLanguages];
				for (int i = 0; i < m_nLanguages; i++){
					if (i < pnl) 
						tPtr[i] = m_ptrNames[i];
					else
						tPtr[i] = "";
				}
				delete [] m_ptrNames;
				m_ptrNames = tPtr;
				
				if (m_nLanguages < m_langNumber)
				{
					m_langNumber = m_nLanguages;
				}
				m_langName = m_ptrNames[m_langNumber-1];
				UpdateData(FALSE);
			}
		}
	}
	
}

void CNewStringTableDlg::OnChangeLnumber() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (IsInitialized)
	{
		char sBuf[4];
		m_CLNumber.GetWindowText(sBuf,5);
		if (strlen(sBuf) > 0)
		{
			int pln = m_langNumber;
			if (UpdateData() && (m_langNumber > 0 && m_langNumber <= m_nLanguages) )
			{
				m_langName = m_ptrNames[m_langNumber-1];
			}
			else
			{
				m_langNumber = pln;
			}
			UpdateData(FALSE);
		}
	}
}

BOOL CNewStringTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_FontName = "Arial";
	m_fSize = 9;

	memset(&m_LogFont,0,sizeof(LOGFONT));
	m_LogFont.lfHeight = 12;
	m_LogFont.lfCharSet = DEFAULT_CHARSET;
	strncpy(m_LogFont.lfFaceName,m_FontName,LF_FACESIZE); 

	m_nLanguages = 1;
	m_Spin.SetRange(1,m_nLanguages);
	m_Spin.EnableWindow(m_nLanguages > 1);
	m_CLNumber.EnableWindow(m_nLanguages > 1);
	m_ptrNames = new CString[m_nLanguages];
	for (int i = 0; i < m_nLanguages; i++)
		m_ptrNames[i] = "";
	m_langNumber = 1;
	m_langName = m_ptrNames[m_langNumber-1];
	
	IsInitialized = TRUE;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewStringTableDlg::OnChangeLname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (IsInitialized)
	{
		if (UpdateData())
		{
			m_ptrNames[m_langNumber-1] = m_langName;
		}
	}
}

void CNewStringTableDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_LNAME)->SetFocus();
	*pResult = 0;
}

void CNewStringTableDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (UpdateData())
	{
		pDoc->m_CHARSET = m_LogFont.lfCharSet;
		pDoc->m_FontName = m_LogFont.lfFaceName;
		pDoc->m_FontHeight = m_LogFont.lfHeight;		
		pDoc->m_nLanguages = m_nLanguages;		
		pDoc->m_nStrings = 0;
		pDoc->m_nAllocatedStrings = 100;
		//pDoc->m_s = new CStringInfo[pDoc->m_nAllocatedStrings];
//		for (int i = 0; i < pDoc->m_nAllocatedStrings; i++)
//			pDoc->m_s[i].SetString(m_nLanguages);
		
		pDoc->m_LanguageNames = new CString[pDoc->m_nLanguages];
		
		for (int j = 0; j < pDoc->m_nLanguages; j++)
		{
			pDoc->m_LanguageNames[j] = m_ptrNames[j];
		}
	
		CDialog::OnOK();
	}
}

CNewStringTableDlg::~CNewStringTableDlg()
{
//	delete m_ptrNames;

}
