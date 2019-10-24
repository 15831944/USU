#if !defined(AFX_ACTIVED3DCTL_H__8A82C342_DBEA_11D0_8F12_444553540000__INCLUDED_)
#define AFX_ACTIVED3DCTL_H__8A82C342_DBEA_11D0_8F12_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ddraw.h>
#include <d3d.h>
#include <d3drm.h>
#include <d3drmwin.h>

// ActiveD3DCtl.h : Declaration of the CActiveD3DCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl : See ActiveD3DCtl.cpp for implementation.

class CActiveD3DCtrl : public COleControl
{
	DECLARE_DYNCREATE(CActiveD3DCtrl)

// Constructor
public:
	CActiveD3DCtrl();
	virtual void OnIdle( long ) { }
	inline COLORREF D3DCOLOR_2_COLORREF(D3DCOLOR d3dclr);
	inline D3DCOLOR COLORREF_2_D3DCOLOR(COLORREF cref);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveD3DCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CActiveD3DCtrl();

	DECLARE_OLECREATE_EX(CActiveD3DCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CActiveD3DCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CActiveD3DCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CActiveD3DCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CActiveD3DCtrl)
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CActiveD3DCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CActiveD3DCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	void Render();
	GUID* GetGUID();
	D3DVALUE ScaleMesh( LPDIRECT3DRMMESHBUILDER mesh, D3DVALUE dim);
	BOOL CreateDevice();
	BOOL CreateScene();
	enum {
	//{{AFX_DISP_ID(CActiveD3DCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};

protected:
	static LPDIRECT3DRM d3drm;
	static LPDIRECT3DRMFRAME scene;
	static LPDIRECT3DRMDEVICE device;
	static LPDIRECT3DRMFRAME camera;
	static LPDIRECT3DRMVIEWPORT viewport;
private:
	static long mousex;
	static long mousey;
	static UINT mousestate;
	D3DCOLORMODEL colormodel;
	CRect winrect;
	LPDIRECTDRAWCLIPPER clipper;
	LPDIRECT3DRMMESH mesh;
	D3DRMGROUPINDEX group;
	static void UpdateCube(LPDIRECT3DRMFRAME, void*, D3DVALUE);
};

inline D3DCOLOR CActiveD3DCtrl::COLORREF_2_D3DCOLOR(COLORREF cref)
{
	D3DVALUE r=D3DVALUE(GetRValue(cref))/D3DVALUE(255);
	D3DVALUE g=D3DVALUE(GetGValue(cref))/D3DVALUE(255);
	D3DVALUE b=D3DVALUE(GetBValue(cref))/D3DVALUE(255);
	return D3DRMCreateColorRGB( r, g, b );
}

inline COLORREF CActiveD3DCtrl::D3DCOLOR_2_COLORREF(D3DCOLOR d3dclr)
{
	D3DVALUE red=D3DVALUE(255)*D3DRMColorGetRed(d3dclr);
	D3DVALUE green=D3DVALUE(255)*D3DRMColorGetGreen( d3dclr );
	D3DVALUE blue=D3DVALUE(255)*D3DRMColorGetBlue( d3dclr );
	return RGB((int)red,(int)green,(int)blue);
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVED3DCTL_H__8A82C342_DBEA_11D0_8F12_444553540000__INCLUDED)
