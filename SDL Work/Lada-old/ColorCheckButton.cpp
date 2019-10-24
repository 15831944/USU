// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This is the class that holds and displays each check for the graphs used
// ColorCheckButton.cpp : implementation file
//

#include "stdafx.h"
#include "ColorCheckButton.h"

#include "Resource.h"
#include "GraphButtonForm.h"
#include "LADA Control ModuleDoc.h"
#include "LadaStrings.h"

#include "RenameLocationDialog.h"
#include "GraphCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COLORREF DefaultColor[15];
extern CPen Pen[15];
extern int curLanguage;
/////////////////////////////////////////////////////////////////////////////
// CColorCheckButton

// Constructor
CColorCheckButton::CColorCheckButton()
:CButton()
{
}

// Destructor
CColorCheckButton::~CColorCheckButton()
{
}

// Message Maps
BEGIN_MESSAGE_MAP(CColorCheckButton, CButton)
	//{{AFX_MSG_MAP(CColorCheckButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorCheckButton message handlers

// Draws items
void CColorCheckButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
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

// Creates new boxes to be graphed
void CColorCheckButton::CreateButton(UINT style, LPCTSTR buttonText, CRect &rect, CWnd *pP, UINT nID, COLORREF color, BOOL s, CFont *pFont)
{
	pParent = pP;
	state = s;
	Create(buttonText,WS_CHILD|BS_OWNERDRAW|style, rect, pParent, nID);
	BColor = color;
	if (pFont)
		SetFont(pFont);
}

// Called when a click occurs on the item
// There are different functions depending on what was clicked
void CColorCheckButton::OnClicked() 
{
	DWORD pos = GetMessagePos();
    CPoint pt(LOWORD(pos), HIWORD(pos));
    ScreenToClient(&pt);
	CGraphButtonForm * ptrPWnd = (CGraphButtonForm *)pParent;
	CLADAControlModuleDoc * pDoc = ptrPWnd->pDoc;
	int whichButton = (GetDlgCtrlID() - IDC_FIRST_CHECKBOX) % 15;
	bool modified = false;

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
		/*
		if (pDoc->PaneToCollectionIndex[ptrPWnd->whichWindow] != -1)
		{
			CColorDialog pickColorDlg;
			if (pickColorDlg.DoModal() == IDOK)
			{
				pDoc->SetModifiedFlag();
				CGraphCollection * curCollection = &pDoc->GraphCollection[pDoc->PaneToCollectionIndex[ptrPWnd->whichWindow]];
				//BColor = curCollection->color[whichButton] = pickColorDlg.GetColor();
				BColor = DefaultColor[whichButton] = pickColorDlg.GetColor();
				Pen[whichButton].DeleteObject();
				Pen[whichButton].CreatePen(PS_SOLID, 1, BColor);
			}
		}
		*/

	}
	else if (pt.x > 26 + SPACE_1 + SPACE_2)
	{
		// change name
		// this will now take a zero based location
		
		int whichLocation = pDoc->GraphCollection[pDoc->PaneToCollectionIndex[ptrPWnd->whichWindow]].DataIndex[whichButton];
	
		CRenameLocationDialog cNewName(whichLocation, IDS_INPUT_LOCATION, &pDoc->InputLocationNameList[whichLocation], TRUE, this );
		cNewName.DoModal();
		
		if (cNewName.DoModal()==IDOK)
		{
			modified = true;
			pDoc->SetModifiedFlag();
			SetWindowText(pDoc->InputLocationNameList[whichLocation][curLanguage]);
		}
	}
	if (modified)
	{
		for (int i = 0; i < pDoc->nPanes; i++)
		{
			if (i != ptrPWnd->whichWindow)
				pDoc->paneModified[i] = TRUE;
				//pDoc->graphListModified[i] = TRUE;
		}
		pDoc->UpdateAllViews(NULL);
	}

	Invalidate();
	UpdateWindow();
	
}

// Sets a check to nCheck
void CColorCheckButton::SetCheck(int nCheck)
{
	state = nCheck;
}

// Gets the status of of Check and returns it
int CColorCheckButton::GetCheck() const
{
	return state;
}
