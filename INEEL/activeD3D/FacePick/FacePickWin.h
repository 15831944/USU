#ifndef FACEPICKWIN_H
#define FACEPICKWIN_H


#include "RMWin.h"

class FacePickWin : public RMWin
{
public:
	FacePickWin();
	BOOL CreateScene();
protected:
	//{{AFX_MSG(FacePickWin)
	afx_msg void OnRenderWireframe();
	afx_msg void OnRenderUnlit();
	afx_msg void OnRenderGouraud();
	afx_msg void OnRenderFlat();
	afx_msg void OnUpdateRenderWireframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRenderFlat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRenderUnlit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRenderGouraud(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnColorsFace();
	afx_msg void OnColorsMesh();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnDestroy();
	afx_msg void OnHelpAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static void UpdateDrag(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta);
	int PickFace( const CPoint& point );
	void OnIdle( long );
private:
	LPDIRECT3DRMMESHBUILDER meshbuilder;
	LPDIRECT3DRMFRAME meshframe;
	D3DCOLOR pickcolor;
	D3DVALUE meshscale;
	static BOOL drag;
	static BOOL end_drag;
	static int last_x, last_y;
};


#endif
