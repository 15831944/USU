#include <AfxWin.h>
#include <AfxExt.h>
#include <ddraw.h>
#include <d3d.h>
#include <d3drm.h>
#include <d3drmwin.h>
#include "RMApp.h"
#include "RMWin.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(RMWin, CFrameWnd)
	//{{AFX_MSG_MAP(RMWin)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LPDIRECT3DRM RMWin::d3drm;
LPDIRECT3DRMFRAME RMWin::scene;
LPDIRECT3DRMDEVICE RMWin::device;
LPDIRECT3DRMFRAME RMWin::camera;
LPDIRECT3DRMVIEWPORT RMWin::viewport;

long RMWin::mousex;
long RMWin::mousey;
UINT RMWin::mousestate;


RMWin::RMWin()
{
	Initvars();
}

RMWin::RMWin(int w, int h)
{
	Initvars();
	winrect.right=w;
	winrect.bottom=h;
}

void RMWin::Initvars()
{
	colormodel=D3DCOLOR_MONO;
	winrect=rectDefault;
    RMApp* pApp = (RMApp*)AfxGetApp();
    pApp->rmwin = this;
}

BOOL RMWin::Create(const CString& sTitle,int icon,int menu)
{
	CString sClassName;

	sClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,LoadCursor(0, IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1), LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(icon)));

	BOOL r=CFrameWnd::Create( sClassName, sTitle, WS_OVERLAPPEDWINDOW, winrect, 0, MAKEINTRESOURCE(menu));

	return r;
}

int RMWin::OnCreate(LPCREATESTRUCT)
{
	HRESULT r;
	r = Direct3DRMCreate(&d3drm);
	if (r!=D3DRM_OK)
	{
		AfxMessageBox("Direct3DRMCreate() failed");
		return -1;
	}
	return 0;
}

BOOL RMWin::CreateDevice()
{
	HRESULT r;
	CWaitCursor cur;

	r = DirectDrawCreateClipper( 0, &clipper, 0 );
	if (r!=D3DRM_OK)
	{
		AfxMessageBox("DirectDrawCreateClipper() failed");
		return FALSE;
	}

	r = clipper->SetHWnd( 0, m_hWnd );
	if (r!=DD_OK)
	{
		AfxMessageBox("clipper->SetHWnd() failed");
		return FALSE;
	}

	RECT rect;
	::GetClientRect( m_hWnd, &rect );

	r = d3drm->CreateDeviceFromClipper( clipper, GetGUID(), 
			rect.right, rect.bottom, 
			&device );

	if (r!=D3DRM_OK)
	{
		AfxMessageBox("CreateDeviceFromClipper() failed");
		return FALSE;
	}

	device->SetQuality( D3DRMRENDER_GOURAUD );

	HDC hdc = ::GetDC( m_hWnd );
	int bpp = ::GetDeviceCaps( hdc, BITSPIXEL );
	::ReleaseDC( m_hWnd, hdc );

	switch ( bpp )
	{
	case 8:
		//device->SetDither( FALSE );
		break;
	case 16:
		device->SetShades( 32 );
		d3drm->SetDefaultTextureColors( 64 );
		d3drm->SetDefaultTextureShades( 32 );
		device->SetDither( FALSE );
		break;
	case 24:
	case 32:
		device->SetShades( 256 );
		d3drm->SetDefaultTextureColors( 64 );
		d3drm->SetDefaultTextureShades( 256 );
		device->SetDither( FALSE );
		break;
	}

	d3drm->CreateFrame( 0, &scene );
	
	if (CreateScene()==FALSE)
	{
		AfxMessageBox("CreateScene() failed");
		return FALSE;
	}
	ASSERT( camera );
	ASSERT( viewport );
	return TRUE;
}

void RMWin::OnActivate(UINT state, CWnd* other, BOOL minimize)
{
	LPDIRECT3DRMWINDEVICE windev;
	if (device)
	{
		if (device->QueryInterface( IID_IDirect3DRMWinDevice, (void**)&windev)==0) 
		{   
			if (windev->HandleActivate((unsigned short)MAKELONG((WORD)state,(WORD)0))!=0) 
				AfxMessageBox("windev->HandleActivate() failure");
			windev->Release();
		}
		else 
			AfxMessageBox("device->QueryInterface(WinDevice) failure");
	}
	CFrameWnd::OnActivate(state, other, minimize);
}

void RMWin::OnPaint() 
{
	static BOOL first = TRUE;
	if (first)
	{
		first = FALSE;
		if (CreateDevice()==FALSE)
			PostQuitMessage(0);
	}

	if (GetUpdateRect( 0, FALSE )==FALSE)
		return;

	if (device) 
	{
		LPDIRECT3DRMWINDEVICE windev;
		PAINTSTRUCT ps;
		BeginPaint(&ps);
		if (device->QueryInterface(IID_IDirect3DRMWinDevice, (void**)&windev)==0)
		{   
			if (windev->HandlePaint(ps.hdc)!=0)
				AfxMessageBox("windev->HandlePaint() failure");
			windev->Release();
		}
		else 
			AfxMessageBox("Failed to create Windows device to handle WM_PAINT");
		EndPaint(&ps);
	}
}

void RMWin::OnSize(UINT type, int cx, int cy)
{
	CFrameWnd::OnSize(type, cx, cy);

	if (!device)
		return;

	int width = cx;
	int height = cy;

	if (width && height) 
	{
		int view_width = viewport->GetWidth();
		int view_height = viewport->GetHeight();
		int dev_width = device->GetWidth();
		int dev_height = device->GetHeight();

		if (view_width == width && view_height == height)
			return;

		int old_dither = device->GetDither();
		D3DRMRENDERQUALITY old_quality = device->GetQuality();
		int old_shades = device->GetShades();

		viewport->Release();
		device->Release();
		d3drm->CreateDeviceFromClipper( clipper, GetGUID(), width, height, &device );

		device->SetDither(old_dither);
		device->SetQuality(old_quality);
		device->SetShades(old_shades);

		width = device->GetWidth();
		height = device->GetHeight();
		d3drm->CreateViewport(device, camera,0, 0, width, height, &viewport);
	}
}

void RMWin::OnMouseMove( UINT state, CPoint point )
{
	mousestate = state;
	mousex = point.x;
	mousey = point.y;
}

BOOL RMWin::OnEraseBkgnd( CDC* pDC ) 
{
	COLORREF bgcolor;
	if (scene)
	{
		D3DCOLOR scenecolor=scene->GetSceneBackground();
		bgcolor=D3DCOLOR_2_COLORREF(scenecolor);
	}
	else
		bgcolor=RGB(0,0,0);

	CBrush br( bgcolor );
	CRect rc;
	GetClientRect(&rc);
	pDC->FillRect(&rc, &br);
	return TRUE;
}

void RMWin::OnDestroy()
{
	if (scene)
	{
		scene->Release();
		scene=0;
	}

	if (device)
	{
		device->Release();
		device=0;
	}

	if (d3drm)
	{
		d3drm->Release();
		d3drm=0;
	}

	if (clipper)
	{
		clipper->Release();
		clipper=0;
	}
}

D3DVALUE RMWin::ScaleMesh( LPDIRECT3DRMMESHBUILDER mesh, D3DVALUE dim)
{
	D3DRMBOX box;
	mesh->GetBox( &box );
	D3DVALUE sizex = box.max.x - box.min.x;
	D3DVALUE sizey = box.max.y - box.min.y;
	D3DVALUE sizez = box.max.z - box.min.z;
	D3DVALUE largedim=D3DVALUE(0);
	if (sizex>largedim)
		largedim=sizex;
	if (sizey>largedim)
		largedim=sizey;
	if (sizez>largedim)
		largedim=sizez;
	D3DVALUE scalefactor = dim/largedim;
	mesh->Scale( scalefactor, scalefactor, scalefactor );
	return scalefactor;
}


GUID* RMWin::GetGUID()
{
	static GUID* lpguid;
	HRESULT r;

	D3DFINDDEVICESEARCH searchdata;
	memset(&searchdata, 0, sizeof searchdata);
	searchdata.dwSize = sizeof searchdata;
	searchdata.dwFlags = D3DFDS_COLORMODEL;
	searchdata.dcmColorModel = colormodel;

	static D3DFINDDEVICERESULT resultdata;
	memset( &resultdata, 0, sizeof resultdata );
	resultdata.dwSize = sizeof resultdata;

	LPDIRECTDRAW ddraw;
	r = DirectDrawCreate( 0, &ddraw, 0 );
	if (r!=DD_OK)
	{
		AfxMessageBox("DirectDrawCreate() failed");
		return 0;
	}

	LPDIRECT3D d3d;
	r = ddraw->QueryInterface( IID_IDirect3D, (void**)&d3d );
	if ( r != D3DRM_OK )
	{
		AfxMessageBox("d3drm->QueryInterface() failed\n");
		ddraw->Release();
		return 0;
	}

	r=d3d->FindDevice( &searchdata, &resultdata );
	if ( r==D3D_OK )
		lpguid = &resultdata.guid;
	else
	{
		AfxMessageBox("FindDevice() failed");
		lpguid=0;
	}
	
	d3d->Release();
	ddraw->Release();

	return lpguid;
}


