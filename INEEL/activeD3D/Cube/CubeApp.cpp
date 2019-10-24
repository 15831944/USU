#include <AfxWin.h>
#include <AfxExt.h>
#include <ddraw.h>
#include <d3d.h>
#include <d3drm.h>
#include <d3drmwin.h>
#include "CubeApp.h"
#include "CubeWin.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(CubeApp, RMApp)
	//{{AFX_MSG_MAP(CubeApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CubeApp theapp;

BOOL CubeApp::InitInstance()
{
#ifdef _DEBUG
//	afxTraceEnabled=FALSE;
#endif
	CubeWin* win=new CubeWin;
	if (!win->Create( "Cutting-Edge Cube Demo", IDI_ICON, IDR_MAINMENU ))
		return FALSE;
	win->SetColorModel( D3DCOLOR_MONO );
	m_pMainWnd=win;
	return RMApp::InitInstance();
}
