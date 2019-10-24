#ifndef CUBEWIN_H
#define CUBEWIN_H


#include "RMWin.h"

class CubeWin : public RMWin
{
public:
	CubeWin();
	BOOL CreateScene();
protected:
	//{{AFX_MSG(CubeWin)
	afx_msg void OnRenderWireframe();
	afx_msg void OnRenderFlat();
	afx_msg void OnRenderGouraud();
	afx_msg void OnUpdateRenderWireframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRenderFlat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRenderGouraud(CCmdUI* pCmdUI);
	afx_msg void OnHelpAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static void UpdateCube(LPDIRECT3DRMFRAME, void*, D3DVALUE);
private:
	LPDIRECT3DRMMESH mesh;
	D3DRMGROUPINDEX group;
};


#endif
