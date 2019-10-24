#include <AfxWin.h>
#include <AfxExt.h>
#include <ddraw.h>
#include <d3d.h>
#include <d3drm.h>
#include <d3drmwin.h>
#include <mmsystem.h>
#include "RMApp.h"
#include "RMWin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(RMApp, CWinApp)
	//{{AFX_MSG_MAP(RMApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

RMApp::RMApp()
{
	rmwin=0;
	m_pMainWnd=0;
}

BOOL RMApp::InitInstance()
{
	ASSERT(m_pMainWnd);
	m_pMainWnd->ShowWindow( SW_SHOWNORMAL );
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

const int NUMFRAMESPERUPDATE=20;

BOOL RMApp::OnIdle(LONG count) 
{
	ASSERT( RMWin::d3drm );
	ASSERT( rmwin );

	static DWORD framecount;
	framecount++;
	
	static D3DVALUE sceneinc=D3DVALUE(1);

	static int delay=NUMFRAMESPERUPDATE;
	delay--;
	if (delay==0)
	{
		delay=NUMFRAMESPERUPDATE;

		static DWORD thistime, lasttime;
		lasttime=thistime;
		thistime=timeGetTime();
		D3DVALUE seconds=D3DVALUE(thistime-lasttime)/D3DVALUE(1000);

		if (framecount>100)
		{
			int fps=(int)(D3DVALUE(NUMFRAMESPERUPDATE)/seconds);
			sceneinc=D3DVALUE(60)/D3DVALUE(fps);
			if (sceneinc>D3DVALUE(1))
				sceneinc=D3DVALUE(1);
		}

	}
	
	rmwin->OnIdle( count );
	RMWin::d3drm->Tick( D3DVALUE(sceneinc) );
	return TRUE;
}

