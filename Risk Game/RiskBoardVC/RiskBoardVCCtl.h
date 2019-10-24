#if !defined(AFX_RISKBOARDVCCTL_H__8EB15BEB_9D20_11D5_B021_0002E3059EB4__INCLUDED_)
#define AFX_RISKBOARDVCCTL_H__8EB15BEB_9D20_11D5_B021_0002E3059EB4__INCLUDED_

#include "Picture.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RiskBoardVCCtl.h : Declaration of the CRiskBoardVCCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCCtrl : See RiskBoardVCCtl.cpp for implementation.

struct CountryInfo
{
	short OwnerID;
	short nArmies;
	BOOL needRedraw;
};

class CRiskBoardVCCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRiskBoardVCCtrl)

// Constructor
public:
	CRiskBoardVCCtrl();
	int OwnerMen[6];
	CountryInfo Countries[43];
	CFont myLargeFont;
	CFont mySmallFont;
	POINT * CountryPosition;
	BYTE * MapData;
	CBitmap m_bmpMen[6];
	CBitmap m_bmpMaskMan;
	BOOL ScrollTimerEnabled;
	int MouseY;
	int MouseX;
	int ClientWidth;
	int ClientHeight;
	int PositionLeft;
	int PositionTop;
	int BoardHeight;
	int BoardWidth;
	CDC ManMemDC;
	CDC BoardMemDC;
	CBitmap m_bmpBoard;

	int GetScrollAmount(int position);
	int FindRegion(POINT p);
	void LoadMap();
	void GetMousePos(int &x, int &y);
	void DoScrolling();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRiskBoardVCCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRiskBoardVCCtrl();

	DECLARE_OLECREATE_EX(CRiskBoardVCCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CRiskBoardVCCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRiskBoardVCCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRiskBoardVCCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRiskBoardVCCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRiskBoardVCCtrl)
	afx_msg short GetBoardMode();
	afx_msg void SetBoardMode(short nNewValue);
	afx_msg BOOL GetScrollWhileOutOfWindow();
	afx_msg void SetScrollWhileOutOfWindow(BOOL bNewValue);
	afx_msg void SetArmies(short Country, short OwnerID, short nArmies);
	afx_msg void SetOwnerColor(short OwnerID, short ColorID);
	afx_msg void RefreshMap();
	afx_msg void SetMapFocus(short CountryID);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CRiskBoardVCCtrl)
	void FireDragToCountry(short CountryA, short CountryB)
		{FireEvent(eventidDragToCountry,EVENT_PARAM(VTS_I2  VTS_I2), CountryA, CountryB);}
	void FireCountryClick(short CountryID, short ShiftDown)
		{FireEvent(eventidCountryClick,EVENT_PARAM(VTS_I2  VTS_I2), CountryID, ShiftDown);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:

	HMODULE hMod;
	CGdiObject * ptrOldBMP;
	short CountryB;
	short CountryA;
	void DoInitialization(CDC * pDC, const CRect & rcBounds);
	BOOL m_Initialized;
	enum {
	//{{AFX_DISP_ID(CRiskBoardVCCtrl)
	dispidBoardMode = 1L,
	dispidScrollWhileOutOfWindow = 2L,
	dispidSetArmies = 3L,
	dispidSetOwnerColor = 4L,
	dispidRefreshMap = 5L,
	dispidSetMapFocus = 6L,
	eventidDragToCountry = 1L,
	eventidCountryClick = 2L,
	//}}AFX_DISP_ID
	};
private:
	CPicture m_RiskBoard;
	BOOL m_ScrollOutOfWindow;
	short m_Mode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISKBOARDVCCTL_H__8EB15BEB_9D20_11D5_B021_0002E3059EB4__INCLUDED)
