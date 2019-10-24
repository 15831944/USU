// CustomBitmapButton.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CustomBitmapButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomBitmapButton

CCustomBitmapButton::CCustomBitmapButton()
{
}

CCustomBitmapButton::~CCustomBitmapButton()
{
	DestroyWindow();
}

BOOL CCustomBitmapButton::Create(LPCTSTR lpszCaption, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	CWnd* pWnd = this;
	return pWnd->Create(_T("BUTTON"), lpszCaption, dwStyle, rect, pParentWnd, nID);
}

void CCustomBitmapButton::SetStyle(DWORD style)
{
	m_Style = style;
}

/*
// Helper for radio buttons
int CWnd::GetCheckedRadioButton(int nIDFirstButton, int nIDLastButton)
{
	for (int nID = nIDFirstButton; nID <= nIDLastButton; nID++)
	{
		if (IsDlgButtonChecked(nID))
			return nID; // id that matched
	}
	return 0; // invalid ID
}

// Derived class is responsible for implementing all of these handlers
//   for owner/self draw controls
void CButton::DrawItem(LPDRAWITEMSTRUCT)
{
	ASSERT(FALSE);
}
*/
/////////////////////////////////////////////////////////////////////////////
// CBitmapButton

// LoadBitmaps will load in one, two, three or all four bitmaps
// returns TRUE if all specified images are loaded
BOOL CCustomBitmapButton::LoadBitmaps(LPCTSTR lpszBitmapResource,
	LPCTSTR lpszBitmapResourceSel, LPCTSTR lpszBitmapResourceFocus,
	LPCTSTR lpszBitmapResourceDisabled)
{
	// delete old bitmaps (if present)
	m_bitmap.DeleteObject();
	m_bitmapSel.DeleteObject();
	m_bitmapFocus.DeleteObject();
	m_bitmapDisabled.DeleteObject();

	if (!m_bitmap.LoadBitmap(lpszBitmapResource))
	{
		TRACE0("Failed to load bitmap for normal image.\n");
		return FALSE;   // need this one image
	}
	BOOL bAllLoaded = TRUE;
	if (lpszBitmapResourceSel != NULL)
	{
		if (!m_bitmapSel.LoadBitmap(lpszBitmapResourceSel))
		{
			TRACE0("Failed to load bitmap for selected image.\n");
			bAllLoaded = FALSE;
		}
	}
	if (lpszBitmapResourceFocus != NULL)
	{
		if (!m_bitmapFocus.LoadBitmap(lpszBitmapResourceFocus))
			bAllLoaded = FALSE;
	}
	if (lpszBitmapResourceDisabled != NULL)
	{
		if (!m_bitmapDisabled.LoadBitmap(lpszBitmapResourceDisabled))
			bAllLoaded = FALSE;
	}
	return bAllLoaded;
}

// SizeToContent will resize the button to the size of the bitmap
void CCustomBitmapButton::SizeToContent()
{
	ASSERT(m_bitmap.m_hObject != NULL);
	CSize bitmapSize;
	BITMAP bmInfo;
	VERIFY(m_bitmap.GetObject(sizeof(bmInfo), &bmInfo) == sizeof(bmInfo));
	VERIFY(SetWindowPos(NULL, -1, -1, bmInfo.bmWidth, bmInfo.bmHeight,
		SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE));
}

// Autoload will load the bitmap resources based on the text of
//  the button
// Using suffices "U", "D", "F" and "X" for up/down/focus/disabled
BOOL CCustomBitmapButton::AutoLoad(UINT nID, CWnd* pParent)
{
	// first attach the CBitmapButton to the dialog control
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;

	CString buttonName;
	GetWindowText(buttonName);
	ASSERT(!buttonName.IsEmpty());      // must provide a title

	LoadBitmaps(buttonName + _T("U"), buttonName + _T("D"),
	  buttonName + _T("F"), buttonName + _T("X"));

	// we need at least the primary
	if (m_bitmap.m_hObject == NULL)
		return FALSE;

	// size to content
	SizeToContent();
	return TRUE;
}

// Draw the appropriate bitmap
void CCustomBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS != NULL);
	// must have at least the first bitmap loaded before calling DrawItem
	ASSERT(m_bitmap.m_hObject != NULL);     // required

	DWORD bStyle = GetStyle();
	
	CBitmap* pBitmap = &m_bitmap;
	UINT state = lpDIS->itemState;

	if (m_Style & BS_CHECKBOX)
	{
		if ((state & ODS_DISABLED) && m_bitmapDisabled.m_hObject != NULL)
			pBitmap = &m_bitmapDisabled;   // last image for disabled
		else if (GetCheck())
			pBitmap = &m_bitmapSel;
	}
	else //if (m_Style & BS_PUSHBUTTON ) BS_PUSHBUTTON == 0x00000000L
	{
		// use the main bitmap for up, the selected bitmap for down
		if ((state & ODS_SELECTED) && m_bitmapSel.m_hObject != NULL)
			pBitmap = &m_bitmapSel;
		else if ((state & ODS_FOCUS) && m_bitmapFocus.m_hObject != NULL)
			pBitmap = &m_bitmapFocus;   // third image for focused
		else if ((state & ODS_DISABLED) && m_bitmapDisabled.m_hObject != NULL)
			pBitmap = &m_bitmapDisabled;   // last image for disabled
	}
	

	// draw the whole button
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOld = memDC.SelectObject(pBitmap);
	if (pOld == NULL)
		return;     // destructors will clean up

	CRect rect;
	rect.CopyRect(&lpDIS->rcItem);
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOld);
}



BEGIN_MESSAGE_MAP(CCustomBitmapButton, CButton)
	//{{AFX_MSG_MAP(CCustomBitmapButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomBitmapButton message handlers
