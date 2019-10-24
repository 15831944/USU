// ColorCheckButton.cpp : implementation file
//

#include "stdafx.h"
#include "ColorCheckButton.h"

#include "Resource.h"
#include "GraphButtonForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorCheckButton

CColorCheckButton::CColorCheckButton()
:CButton()
{
}

CColorCheckButton::~CColorCheckButton()
{
}


BEGIN_MESSAGE_MAP(CColorCheckButton, CButton)
	//{{AFX_MSG_MAP(CColorCheckButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorCheckButton message handlers

void CColorCheckButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	UINT uStyle = DFCS_BUTTONCHECK;   // This code only works with buttons.
  	
	/*
	if (lpDrawItemStruct->itemAction & ODA_FOCUS){
		CRect focusRect(lpDrawItemStruct->rcItem);

		focusRect.left = 16;
		focusRect.top = (focusRect.bottom - 18) / 2;
		focusRect.bottom = focusRect.top + 18;

		::DrawFocusRect(lpDrawItemStruct->hDC,&focusRect);
	}
	*/

	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE | ODA_SELECT ){
		int right = lpDrawItemStruct->rcItem.right;
		lpDrawItemStruct->rcItem.top = (lpDrawItemStruct->rcItem.bottom - 13) / 2;
		lpDrawItemStruct->rcItem.bottom = lpDrawItemStruct->rcItem.top + 13;
		uStyle |= (state ? DFCS_CHECKED : 0);
		lpDrawItemStruct->rcItem.left = 0;
		lpDrawItemStruct->rcItem.right = 13;
		::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, 
			DFC_BUTTON, uStyle);
		
		CRect fillRect(lpDrawItemStruct->rcItem);
		fillRect.OffsetRect(CPoint(13 + SPACE_1,0));
		FillRect(lpDrawItemStruct->hDC, &fillRect, CreateSolidBrush(BColor));
		DrawEdge(  lpDrawItemStruct->hDC,&fillRect,EDGE_SUNKEN,BF_RECT);

		if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
		{
			lpDrawItemStruct->rcItem.left = 26 + SPACE_1 + SPACE_2;
			lpDrawItemStruct->rcItem.right = right;
			// Get the button's text.   
			CString strText;
			GetWindowText(strText);   
			//COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255,0,0));
			::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
				&lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER);//|DT_CENTER);
			//::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
		}
	}

}

void CColorCheckButton::CreateButton(LPCTSTR buttonText, CRect &rect, CWnd *pP, UINT nID, COLORREF color, BOOL s, CFont *pFont)
{
	pParent = pP;
	state = s;
	Create(buttonText,WS_VISIBLE|WS_CHILD|BS_OWNERDRAW, rect, pParent, nID);
	BColor = color;
	if (pFont)
		SetFont(pFont);
}

void CColorCheckButton::OnClicked() 
{
	// TODO: Add your control notification handler code here
	DWORD pos = GetMessagePos();
    CPoint pt(LOWORD(pos), HIWORD(pos));
    ScreenToClient(&pt);
	
	if (pt.x < 12)
	{
		// change check status
		state ^= 1;
		int whichButton = GetDlgCtrlID();
		((CGraphButtonForm*)pParent)->ClickCheckBox(whichButton);
		
	}
	else if (pt.x > 14 && pt.x < 27)
	{
		// change color
	}
	else if (pt.x > 26 + SPACE_1 + SPACE_2)
	{
		// change name

	}

	Invalidate();
	UpdateWindow();
	
}

void CColorCheckButton::SetCheck(int nCheck){
	state = nCheck;
}

int CColorCheckButton::GetCheck() const{
	return state;
}
