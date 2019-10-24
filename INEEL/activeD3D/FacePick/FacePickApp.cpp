#include <AfxWin.h>
#include <AfxExt.h>
#include <ddraw.h>
#include <d3d.h>
#include <d3drm.h>
#include <d3drmwin.h>
#include "FacePickApp.h"
#include "FacePickWin.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(FacePickApp, RMApp)
	//{{AFX_MSG_MAP(FacePickApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

FacePickApp theapp;

BOOL FacePickApp::InitInstance()
{
#ifdef _DEBUG
	//afxTraceEnabled=FALSE;
#endif
	FacePickWin* win=new FacePickWin;
	if (!win->Create( "Cutting-Edge FacePick Demo", IDI_ICON, IDR_MAINMENU ))
		return FALSE;
	win->SetColorModel( D3DCOLOR_MONO );
	m_pMainWnd=win;
	return RMApp::InitInstance();
}
