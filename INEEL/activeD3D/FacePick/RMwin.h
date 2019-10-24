#ifndef RMWIN_H
#define RMWIN_H

class RMWin : public CFrameWnd
{
public:
	RMWin();
	RMWin(int w,int h);
	BOOL Create(const CString& sTitle,int icon,int menu);
	void SetColorModel( D3DCOLORMODEL cm )  { colormodel=cm; }
	inline COLORREF D3DCOLOR_2_COLORREF(D3DCOLOR d3dclr);
	inline D3DCOLOR COLORREF_2_D3DCOLOR(COLORREF cref);
protected:
	static int GetMouseX()    { return mousex; }
	static int GetMouseY()    { return mousey; }
	D3DVALUE ScaleMesh( LPDIRECT3DRMMESHBUILDER, D3DVALUE );
	virtual void OnIdle( long ) { }
protected:
	//{{AFX_MSG(RMWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnActivate(UINT state, CWnd* other, BOOL minimize);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT type, int cx, int cy);
	afx_msg void OnMouseMove( UINT state, CPoint point );
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Initvars();
	virtual BOOL CreateScene() = 0;
	BOOL CreateDevice();
	GUID* GetGUID();
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
	friend class RMApp;
};

inline D3DCOLOR RMWin::COLORREF_2_D3DCOLOR(COLORREF cref)
{
	D3DVALUE r=D3DVALUE(GetRValue(cref))/D3DVALUE(255);
	D3DVALUE g=D3DVALUE(GetGValue(cref))/D3DVALUE(255);
	D3DVALUE b=D3DVALUE(GetBValue(cref))/D3DVALUE(255);
	return D3DRMCreateColorRGB( r, g, b );
}

inline COLORREF RMWin::D3DCOLOR_2_COLORREF(D3DCOLOR d3dclr)
{
	D3DVALUE red=D3DVALUE(255)*D3DRMColorGetRed(d3dclr);
	D3DVALUE green=D3DVALUE(255)*D3DRMColorGetGreen( d3dclr );
	D3DVALUE blue=D3DVALUE(255)*D3DRMColorGetBlue( d3dclr );
	return RGB((int)red,(int)green,(int)blue);
}

#endif
