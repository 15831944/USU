// Popup.cpp : implementation file
//

#include "stdafx.h"
#include "DrawDi.h"
#include "DrawDiDlg.h"
#include "Popup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Popup dialog


Popup::Popup(CWnd* pParent /*=NULL*/)
	: CDialog(Popup::IDD, pParent)
{
	//{{AFX_DATA_INIT(Popup)
	//}}AFX_DATA_INIT
}


void Popup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Popup)
	DDX_Control(pDX, IDC_SCROLLBAR1, m_intensity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Popup, CDialog)
	//{{AFX_MSG_MAP(Popup)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Popup message handlers

void Popup::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch(nSBCode)
	{
	case SB_LINELEFT:
		m_intensity.SetScrollPos(m_intensity.GetScrollPos()-1, TRUE);
		break;
	case SB_LINERIGHT:
		m_intensity.SetScrollPos(m_intensity.GetScrollPos()+1, TRUE);
		break;
	case SB_PAGELEFT:
		m_intensity.SetScrollPos(m_intensity.GetScrollPos()-10, TRUE);
		break;
	case SB_PAGERIGHT:
		m_intensity.SetScrollPos(m_intensity.GetScrollPos()+10, TRUE);
		break;
	case SB_THUMBPOSITION:
		m_intensity.SetScrollPos((int)nPos, TRUE);
		break;
	case SB_THUMBTRACK:
		m_intensity.SetScrollPos((int)nPos, TRUE);
		break;
	case SB_LEFT:
		m_intensity.SetScrollPos(0, TRUE);
		break;
	case SB_RIGHT:
		m_intensity.SetScrollPos(255, TRUE);
		break;
	case SB_ENDSCROLL:
		break;
	default:
		break;
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

BOOL Popup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CWnd * p = GetParent();
	CDrawDiDlg * d = (CDrawDiDlg *)p;
	m_intensity.SetScrollRange(0, 255, TRUE);
	m_intensity.SetScrollPos(d->intensity, TRUE);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Popup::OnOK() 
{
	CWnd * p = GetParent();
	CDrawDiDlg * d = (CDrawDiDlg *)p;
	d->intensity = m_intensity.GetScrollPos();
	CDialog::OnOK();
}
