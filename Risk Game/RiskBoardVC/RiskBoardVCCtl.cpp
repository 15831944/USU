// RiskBoardVCCtl.cpp : Implementation of the CRiskBoardVCCtrl ActiveX Control class.

#include "stdafx.h"
#include "RiskBoardVC.h"
#include "RiskBoardVCCtl.h"
#include "RiskBoardVCPpg.h"
#include <fstream.h>
#include "Picture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int minScrollAmount = 2;
const int maxScrollAmount = 40;
const int BorderScrollArea = 50;

IMPLEMENT_DYNCREATE(CRiskBoardVCCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRiskBoardVCCtrl, COleControl)
	//{{AFX_MSG_MAP(CRiskBoardVCCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRiskBoardVCCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRiskBoardVCCtrl)
	DISP_PROPERTY_EX(CRiskBoardVCCtrl, "BoardMode", GetBoardMode, SetBoardMode, VT_I2)
	DISP_PROPERTY_EX(CRiskBoardVCCtrl, "ScrollWhileOutOfWindow", GetScrollWhileOutOfWindow, SetScrollWhileOutOfWindow, VT_BOOL)
	DISP_FUNCTION(CRiskBoardVCCtrl, "SetArmies", SetArmies, VT_EMPTY, VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION(CRiskBoardVCCtrl, "SetOwnerColor", SetOwnerColor, VT_EMPTY, VTS_I2 VTS_I2)
	DISP_FUNCTION(CRiskBoardVCCtrl, "RefreshMap", RefreshMap, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRiskBoardVCCtrl, "SetMapFocus", SetMapFocus, VT_EMPTY, VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRiskBoardVCCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRiskBoardVCCtrl)
	EVENT_CUSTOM("DragToCountry", FireDragToCountry, VTS_I2  VTS_I2)
	EVENT_CUSTOM("CountryClick", FireCountryClick, VTS_I2  VTS_I2)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRiskBoardVCCtrl, 1)
	PROPPAGEID(CRiskBoardVCPropPage::guid)
END_PROPPAGEIDS(CRiskBoardVCCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRiskBoardVCCtrl, "RISKBOARDVC.RiskBoardVCCtrl.1",
	0x8eb15bde, 0x9d20, 0x11d5, 0xb0, 0x21, 0, 0x2, 0xe3, 0x5, 0x9e, 0xb4)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRiskBoardVCCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRiskBoardVC =
		{ 0x8eb15bdc, 0x9d20, 0x11d5, { 0xb0, 0x21, 0, 0x2, 0xe3, 0x5, 0x9e, 0xb4 } };
const IID BASED_CODE IID_DRiskBoardVCEvents =
		{ 0x8eb15bdd, 0x9d20, 0x11d5, { 0xb0, 0x21, 0, 0x2, 0xe3, 0x5, 0x9e, 0xb4 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRiskBoardVCOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRiskBoardVCCtrl, IDS_RISKBOARDVC, _dwRiskBoardVCOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCCtrl::CRiskBoardVCCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRiskBoardVCCtrl

BOOL CRiskBoardVCCtrl::CRiskBoardVCCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegInsertable | afxRegApartmentThreading to afxRegInsertable.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_RISKBOARDVC,
			IDB_RISKBOARDVC,
			afxRegInsertable | afxRegApartmentThreading,
			_dwRiskBoardVCOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCCtrl::CRiskBoardVCCtrl - Constructor

CRiskBoardVCCtrl::CRiskBoardVCCtrl()
{
	InitializeIIDs(&IID_DRiskBoardVC, &IID_DRiskBoardVCEvents);

	// TODO: Initialize your control's instance data here.
	hMod = NULL;
	MapData = NULL;
	CountryPosition = NULL;

	m_Initialized = FALSE;

	LoadMap();

	for (int wCountry = 0; wCountry < 43; wCountry++)
	{
		Countries[wCountry].nArmies = 0;
		Countries[wCountry].OwnerID = -1;
	}

	for (int i = 0; i < 6; i++)
		OwnerMen[i] = i;

	//m_bmpBoard.LoadBitmap(IDB_LARGEBOARD);
	if (!m_RiskBoard.Load("RiskBoard.jpg"))
	{
		MessageBox("Could not load RiskBoard.jpg.  Make sure it is in the program directory.","Error",MB_ICONSTOP);
	}
	
	m_bmpMaskMan.LoadBitmap(IDB_MASK_MAN);
	m_bmpMen[0].LoadBitmap(IDB_BLUE_MAN);
	m_bmpMen[1].LoadBitmap(IDB_RED_MAN);
	m_bmpMen[2].LoadBitmap(IDB_YELLOW_MAN);
	m_bmpMen[3].LoadBitmap(IDB_GREEN_MAN);
	m_bmpMen[4].LoadBitmap(IDB_PURPLE_MAN);
	m_bmpMen[5].LoadBitmap(IDB_BLACK_MAN);

	ScrollTimerEnabled = FALSE;

	
}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCCtrl::~CRiskBoardVCCtrl - Destructor

CRiskBoardVCCtrl::~CRiskBoardVCCtrl()
{
	// TODO: Cleanup your control's instance data here.
	
	delete [] MapData;
	delete [] CountryPosition;
}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCCtrl::OnDraw - Drawing function

void CRiskBoardVCCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!m_Initialized)
	{
		DoInitialization(pdc, rcBounds);
		m_Initialized = TRUE;
	}
	
	for (int wCountry = 1; wCountry < 43; wCountry++)
	{
		if (Countries[wCountry].needRedraw == TRUE)
		{
			CGdiObject * oldObject;
			CGdiObject * oldFont;
			
			CSize textSize;
			CString text;
			int xOffSet;
			int x, y;
			int nArmies = Countries[wCountry].nArmies;

			x = CountryPosition[wCountry].x-20;
			y = CountryPosition[wCountry].y-30;
			
			BoardMemDC.SetBkMode(TRANSPARENT);
			
			oldObject = ManMemDC.SelectObject(&m_bmpMaskMan);
			BoardMemDC.BitBlt(x,y,60,60, &ManMemDC, 0,0, SRCPAINT);
			ManMemDC.SelectObject(oldObject);

			oldObject = ManMemDC.SelectObject(&m_bmpMen[OwnerMen[Countries[wCountry].OwnerID]]);
			BoardMemDC.BitBlt(x,y,60,60, &ManMemDC, 0,0, SRCAND);
			ManMemDC.SelectObject(oldObject);

			if (nArmies < 10)
				oldFont = BoardMemDC.SelectObject( &myLargeFont );
			else
				oldFont = BoardMemDC.SelectObject( &mySmallFont );
			
			text.Format("%i",nArmies);

			textSize = BoardMemDC.GetTextExtent(text);

			xOffSet = (18 - textSize.cx) / 2 + 1;

			BoardMemDC.TextOut(x+xOffSet,y+2,text);
			BoardMemDC.SelectObject( oldFont );	
			Countries[wCountry].needRedraw = FALSE;
		}
	}

	// bit block transfer image from memory DC to paint DC

	pdc->BitBlt(2,2,ClientWidth,ClientHeight,&BoardMemDC,PositionLeft,PositionTop,SRCCOPY);
	//pdc->Rectangle(0,0,ClientWidth + 3, ClientHeight + 3);
	CRect bRect = rcBounds;
	pdc->DrawEdge(&bRect,EDGE_SUNKEN,BF_RECT);

	/* 
	FillColor = vbWindowBackground
    FillStyle = vbFSTransparent
    Line (0, 0)-(ScaleWidth - 1, ScaleHeight - 1), vb3DHighlight, B
    Line (0, 0)-(ScaleWidth - 1, 0), vb3DShadow
    Line (0, 0)-(0, ScaleHeight - 1), vb3DShadow
    Line (1, 1)-(ScaleWidth - 2, 1), vb3DDKShadow
    Line (1, 1)-(1, ScaleHeight - 2), vb3DDKShadow
    Line (1, ScaleHeight - 2)-(ScaleWidth - 2, ScaleHeight - 2), vb3DLight
    Line (ScaleWidth - 2, 1)-(ScaleWidth - 2, ScaleHeight - 1), vb3DLight
    Effects3dDrawn = True*/

}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCCtrl::DoPropExchange - Persistence support

void CRiskBoardVCCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
	PX_Bool(pPX, _T("ScrollWhileOutOfWindow"), m_ScrollOutOfWindow, FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCCtrl::OnResetState - Reset control to default state

void CRiskBoardVCCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCCtrl message handlers

void CRiskBoardVCCtrl::DoInitialization(CDC *pSrcDC, const CRect &rcBounds)
{
	// create memory device context to hold image
	BoardMemDC.CreateCompatibleDC( pSrcDC );
	ManMemDC.CreateCompatibleDC( pSrcDC );

	//ptrOldBMP = BoardMemDC.SelectObject( &m_bmpBoard );
	m_RiskBoard.SelectPicture( &BoardMemDC );
	
	mySmallFont.CreateFont(17,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,0,0,PROOF_QUALITY ,0,"Arial");
	myLargeFont.CreateFont(18,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,0,0,PROOF_QUALITY ,0,"Arial");

	//CSize boardImageSize(m_bmpBoard.GetBitmapDimension());
	BoardHeight = 1273;
    BoardWidth = 2000;

	ClientHeight = rcBounds.Height() - 4;
	ClientWidth = rcBounds.Width() - 4;

    PositionTop = 0;
    PositionLeft = 0;
}

void CRiskBoardVCCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	MouseX = point.x;
    MouseY = point.y;
    if (!ScrollTimerEnabled)
        DoScrolling();
	
	//COleControl::OnMouseMove(nFlags, point);
}

void CRiskBoardVCCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	point.Offset(PositionLeft,PositionTop);
	CountryA = FindRegion(point);

	// probably check mode here...
	if (m_Mode == 0)
	{
		short shiftDown = nFlags & MK_SHIFT;
		if (shiftDown) shiftDown = -1;
		if (CountryA > 0)
			FireCountryClick(CountryA, shiftDown);
	}
//	COleControl::OnLButtonDown(nFlags, point);
}

void CRiskBoardVCCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	point.Offset(PositionLeft,PositionTop);
	CountryB = FindRegion(point);

	// probably check mode here...
	if (m_Mode == 1)
	{
		if (CountryB > 0)
			FireDragToCountry(CountryA,CountryB);
	}
		//COleControl::OnLButtonUp(nFlags, point);
}

void CRiskBoardVCCtrl::DoScrolling()
{
    BOOL needRedraw = FALSE;
    
	if (m_ScrollOutOfWindow == FALSE && (MouseX < 0 || MouseY < 0 || MouseX > ClientWidth || MouseY > ClientHeight))
	{
		ScrollTimerEnabled = FALSE;
		KillTimer(ID_DO_SCROLLING_EVENT);
		return;
	}

    if ( MouseX < BorderScrollArea )
	{
        if ( PositionLeft > 0 )
		{
            PositionLeft -= GetScrollAmount(BorderScrollArea - MouseX);
			if ( PositionLeft < 0 )
				PositionLeft = 0;
            needRedraw = TRUE;
		}
    }
    else if ( MouseX > ClientWidth - BorderScrollArea )
	{
        if ( PositionLeft < BoardWidth - ClientWidth )
		{
            PositionLeft += GetScrollAmount(MouseX - (ClientWidth - BorderScrollArea));
            if (PositionLeft > BoardWidth - ClientWidth)
				PositionLeft = BoardWidth - ClientWidth;
			needRedraw = TRUE;
		}
	}
 
    if ( MouseY < BorderScrollArea )
	{
        if ( PositionTop > 0 )
		{
            PositionTop -= GetScrollAmount(BorderScrollArea - MouseY);
			if (PositionTop < 0)
				PositionTop = 0;
            needRedraw = TRUE;
        }
    }
	else if ( MouseY > ClientHeight - BorderScrollArea )
	{
        if ( PositionTop < BoardHeight - ClientHeight )
		{
            PositionTop += GetScrollAmount(MouseY - (ClientHeight - BorderScrollArea));
			if (PositionTop > BoardHeight - ClientHeight)
				PositionTop = BoardHeight - ClientHeight;
            needRedraw = TRUE;
        }
    }

    if ( needRedraw )
	{
        if ( ScrollTimerEnabled == FALSE )
		{
            ScrollTimerEnabled = TRUE;
			SetTimer(ID_DO_SCROLLING_EVENT,40,NULL);
            
		}
        Invalidate(FALSE);
	}
    else
	{
        ScrollTimerEnabled = FALSE;
		KillTimer(ID_DO_SCROLLING_EVENT);
	}

}

void CRiskBoardVCCtrl::GetMousePos(int &x, int &y)
{
    POINT pos;
    GetCursorPos(&pos);
    ScreenToClient(&pos);

    x = pos.x;
    y = pos.y;
}

void CRiskBoardVCCtrl::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == ID_DO_SCROLLING_EVENT )
	{
		GetMousePos(MouseX, MouseY);
		DoScrolling();
	}
	else
		COleControl::OnTimer(nIDEvent);
}

int CRiskBoardVCCtrl::GetScrollAmount(int position)
{
	if (position < 0)
		position = 0;
	if (position > BorderScrollArea)
		position = BorderScrollArea;
	return position * (maxScrollAmount - minScrollAmount) / BorderScrollArea + minScrollAmount;
}

void CRiskBoardVCCtrl::LoadMap()
{
    int fileSize = 40572;

	ifstream fin;
	fin.open("Country List.txt");
	CountryPosition = new POINT[43];
	
    for (int wCountry = 1; wCountry < 43; wCountry++)
	{	
		fin >> CountryPosition[wCountry].x >> CountryPosition[wCountry].y;
    }
	
	/*
	hMod = LoadLibrary("RiskBoardVC.ocx");
	HRSRC hRes;
	HGLOBAL resData;
	
	CString rID;
	rID.Format("#%i",BOARDDAT);
	hRes = FindResource(hMod,rID,"Binary");
	resData = LoadResource(hMod,hRes);
    MapData = (BYTE *) LockResource(resData);
	*/
	fin.close();

	fin.open("Country Data.dat",ios::binary);
	MapData = new BYTE[fileSize];
	fin.read(MapData, fileSize);
	fin.close();
	
	/*
	rID.Format("#%i",COUNTRYLIST);
	hRes = FindResource(hMod,rID,"Binary");
	resData = LoadResource(hMod,hRes);
	CountryPosition = (POINT *)LockResource(resData);
	*/
	
}

int CRiskBoardVCCtrl::FindRegion(POINT p)
{
	int shrinkfactor = 1, x, y;
    x = shrinkfactor * (p.x) / 8;
    y = shrinkfactor * (p.y) / 8;
    return MapData[x + y * 252];
}

void CRiskBoardVCCtrl::OnSize(UINT nType, int cx, int cy) 
{
	//COleControl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (nType == SIZE_RESTORED)
	{
		if (cx < BoardWidth)
			ClientWidth = cx;
		else
			ClientWidth = BoardWidth;

		if (cy < BoardHeight)
			ClientHeight = cy;
		else
			ClientHeight = BoardHeight;

		if (PositionLeft > BoardWidth - ClientWidth)
			PositionLeft = BoardWidth - ClientWidth;

		if (PositionTop > BoardHeight - ClientHeight)
			PositionTop = BoardHeight - ClientHeight;

		InvalidateControl();
	}
}

void CRiskBoardVCCtrl::SetArmies(short Country, short OwnerID, short nArmies) 
{
	Countries[Country].nArmies = nArmies;
	Countries[Country].OwnerID = OwnerID;
	Countries[Country].needRedraw = TRUE;
}

void CRiskBoardVCCtrl::SetOwnerColor(short OwnerID, short ColorID) 
{
	// TODO: Add your dispatch handler code here
	OwnerMen[OwnerID] = ColorID;
}

void CRiskBoardVCCtrl::RefreshMap() 
{
	// TODO: Add your dispatch handler code here
	InvalidateControl();
}

void CRiskBoardVCCtrl::SetMapFocus(short CountryID) 
{
	// TODO: Add your dispatch handler code here
	PositionLeft = CountryPosition[CountryID].x - ClientWidth / 2;
	PositionTop = CountryPosition[CountryID].y - ClientHeight / 2;
	if (PositionLeft < 0)
		PositionLeft = 0;
	if (PositionLeft > BoardWidth - ClientWidth)
		PositionLeft = BoardWidth - ClientWidth;
	if (PositionTop < 0)
		PositionTop = 0;
	if (PositionTop > BoardHeight - ClientHeight)
		PositionTop = BoardHeight - ClientHeight;
	
	InvalidateControl();
}

short CRiskBoardVCCtrl::GetBoardMode() 
{
	// TODO: Add your property handler here

	return m_Mode;
}

void CRiskBoardVCCtrl::SetBoardMode(short nNewValue) 
{
	// TODO: Add your property handler here
	m_Mode = nNewValue;
	SetModifiedFlag();
}

void CRiskBoardVCCtrl::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
	//BoardMemDC.SelectObject(ptrOldBMP);
	//BoardMemDC.SelectObject(hOldBMP);

	//m_bmpBoard.DeleteObject();
	
	m_bmpMaskMan.DeleteObject();
	m_bmpMen[0].DeleteObject();
	m_bmpMen[1].DeleteObject();
	m_bmpMen[2].DeleteObject();
	m_bmpMen[3].DeleteObject();
	m_bmpMen[4].DeleteObject();
	m_bmpMen[5].DeleteObject();

	BoardMemDC.DeleteDC();
	ManMemDC.DeleteDC();

	if (hMod)
		FreeLibrary(hMod);

	COleControl::OnFinalRelease();
}

/*
long CRiskBoardVCCtrl::GetCountryPosition(short CountryID, short xpos, short ypos) 
{
	// TODO: Add your dispatch handler code here
	xpos = CountryPosition[CountryID].x;
	ypos = CountryPosition[CountryID].y;
	return CountryPosition[CountryID].x;
}
*/

BOOL CRiskBoardVCCtrl::GetScrollWhileOutOfWindow() 
{
	// TODO: Add your property handler here
	return m_ScrollOutOfWindow;
}

void CRiskBoardVCCtrl::SetScrollWhileOutOfWindow(BOOL bNewValue) 
{
	// TODO: Add your property handler here
	m_ScrollOutOfWindow = bNewValue;
	SetModifiedFlag();
}
