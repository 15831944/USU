// ActiveD3DCtl.cpp : Implementation of the CActiveD3DCtrl ActiveX Control class.

#include "stdafx.h"

#define INITGUID
#include <objbase.h> 
#include <initguid.h>
#include "activeD3D.h"
#include "ActiveD3DCtl.h"
#include "ActiveD3DPpg.h"
#include <ddraw.h>
#include <d3d.h>
#include <d3drm.h>
#include <d3drmwin.h>

#pragma comment (lib,"ddraw.lib")
#pragma comment (lib,"d3drm.lib")
#pragma comment (lib,"winmm.lib")



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CActiveD3DCtrl, COleControl)




/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CActiveD3DCtrl, COleControl)
	//{{AFX_MSG_MAP(CActiveD3DCtrl)
	ON_WM_ACTIVATE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CActiveD3DCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CActiveD3DCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	DISP_STOCKPROP_READYSTATE()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CActiveD3DCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CActiveD3DCtrl, COleControl)
	//{{AFX_EVENT_MAP(CActiveD3DCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	EVENT_STOCK_READYSTATECHANGE()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CActiveD3DCtrl, 1)
	PROPPAGEID(CActiveD3DPropPage::guid)
END_PROPPAGEIDS(CActiveD3DCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CActiveD3DCtrl, "ACTIVED3D.ActiveD3DCtrl.1",
	0x8a82c334, 0xdbea, 0x11d0, 0x8f, 0x12, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CActiveD3DCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DActiveD3D =
		{ 0x8a82c332, 0xdbea, 0x11d0, { 0x8f, 0x12, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DActiveD3DEvents =
		{ 0x8a82c333, 0xdbea, 0x11d0, { 0x8f, 0x12, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwActiveD3DOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CActiveD3DCtrl, IDS_ACTIVED3D, _dwActiveD3DOleMisc)

 LPDIRECT3DRM CActiveD3DCtrl::d3drm=0;
 LPDIRECT3DRMFRAME CActiveD3DCtrl::scene=0;
 LPDIRECT3DRMDEVICE CActiveD3DCtrl::device=0;
 LPDIRECT3DRMFRAME CActiveD3DCtrl::camera=0;
 LPDIRECT3DRMVIEWPORT CActiveD3DCtrl::viewport;

 long CActiveD3DCtrl::mousex;
 long CActiveD3DCtrl::mousey;
 UINT CActiveD3DCtrl::mousestate;
/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl::CActiveD3DCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CActiveD3DCtrl

BOOL CActiveD3DCtrl::CActiveD3DCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_ACTIVED3D,
			IDB_ACTIVED3D,
			afxRegApartmentThreading,
			_dwActiveD3DOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl::CActiveD3DCtrl - Constructor

CActiveD3DCtrl::CActiveD3DCtrl()
{
	InitializeIIDs(&IID_DActiveD3D, &IID_DActiveD3DEvents);

	m_lReadyState = READYSTATE_LOADING;
	// TODO: Call InternalSetReadyState when the readystate changes.

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl::~CActiveD3DCtrl - Destructor

CActiveD3DCtrl::~CActiveD3DCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl::OnDraw - Drawing function

void CActiveD3DCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	static BOOL first = TRUE;
	if (first)
	{
		first = FALSE;
			SetTimer(1,20,NULL);
		if (CreateDevice()==FALSE)
			PostQuitMessage(0);
	}

	if (GetUpdateRect( 0, FALSE )==FALSE)
		return;

	if (device) 
	{
		LPDIRECT3DRMWINDEVICE windev;
		PAINTSTRUCT ps;
		HDC hdc;
		hdc= ::GetDC(m_hWnd);
//		BeginPaint(&ps);//ditch
		if (device->QueryInterface(IID_IDirect3DRMWinDevice, (void**)&windev)==0)
		{   
			if (windev->HandlePaint(hdc)!=0)
				AfxMessageBox("windev->HandlePaint() failure");
			windev->Release();
		}
		else 
			AfxMessageBox("Failed to create Windows device to handle WM_PAINT");
//		EndPaint(&ps);
		::ReleaseDC(m_hWnd,hdc);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl::DoPropExchange - Persistence support

void CActiveD3DCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl::OnResetState - Reset control to default state

void CActiveD3DCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl::AboutBox - Display an "About" box to the user

void CActiveD3DCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_ACTIVED3D);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DCtrl message handlers

#define VERTEX(px,py,pz,nx,ny,nz,tu,tv)  \
	{ { D3DVALUE(px),D3DVALUE(py),D3DVALUE(pz) }, \
	  { D3DVALUE(nx),D3DVALUE(ny),D3DVALUE(nz), }, \
	  D3DVALUE(tu),D3DVALUE(tv),D3DCOLOR(0) }

static D3DRMVERTEX vertexlist[]=
{
	// left face
	VERTEX( 0,0,0, -1,0,0,  0,1 ), // vertex 0
	VERTEX( 0,0,1, -1,0,0,  0,0 ),
	VERTEX( 0,1,1, -1,0,0,  1,0 ),
	VERTEX( 0,1,0, -1,0,0,  1,1 ),
	// right face
	VERTEX( 1,0,0,  1,0,0,  0,0 ),
	VERTEX( 1,1,0,  1,0,0,  1,0 ),
	VERTEX( 1,1,1,  1,0,0,  1,1 ), // vertex 6
	VERTEX( 1,0,1,  1,0,0,  0,1 ),
	// front face
	VERTEX( 0,0,0,  0,0,-1, 0,0 ), // vertex 8
	VERTEX( 0,1,0,  0,0,-1, 1,0 ),
	VERTEX( 1,1,0,  0,0,-1, 1,1 ),
	VERTEX( 1,0,0,  0,0,-1, 0,1 ),
	// back face
	VERTEX( 0,0,1,  0,0,1,  0,1 ),
	VERTEX( 1,0,1,  0,0,1,  0,0 ),
	VERTEX( 1,1,1,  0,0,1,  1,0 ), // vertex 14
	VERTEX( 0,1,1,  0,0,1,  1,1 ),
	// top face
	VERTEX( 0,1,0,  0,1,0,  0,0 ),
	VERTEX( 0,1,1,  0,1,0,  1,0 ),
	VERTEX( 1,1,1,  0,1,0,  1,1 ), // vertex 18
	VERTEX( 1,1,0,  0,1,0,  0,1 ),
	// bottom face
	VERTEX( 0,0,0,  0,-1,0, 0,0 ), // vertex 20
	VERTEX( 1,0,0,  0,-1,0, 1,0 ),
	VERTEX( 1,0,1,  0,-1,0, 1,1 ),
	VERTEX( 0,0,1,  0,-1,0, 0,1 ),
};


unsigned vertorder[] = { 0,1,2,3,4,5,6,7,8,9,10,11,
		12,13,14,15,16,17,18,19,20,21,22,23 };

struct CallbackData
{
	LPDIRECT3DRMMESH mesh;
	D3DRMGROUPINDEX group;
};

BOOL CActiveD3DCtrl::CreateScene()
{
	// ------- MESH --------
	d3drm->CreateMesh( &mesh );
	mesh->AddGroup( 24, 6, 4, vertorder, &group );
	mesh->SetVertices( group, 0, 24, vertexlist );
	mesh->Translate( D3DVALUE(-0.5), D3DVALUE(-0.5), D3DVALUE(-0.5) );
	mesh->Scale( D3DVALUE(15), D3DVALUE(15), D3DVALUE(15) );

	//-------- TEXTURE -------
//	HRSRC texture_id = FindResource( NULL, 
//			MAKEINTRESOURCE(IDR_WIN95TEXTURE), "Desert.bmp" );
//	LPDIRECT3DRMTEXTURE texture;
//	d3drm->LoadTextureFromResource( texture_id, &texture );
//	mesh->SetGroupTexture( group, texture );
//	mesh->SetGroupMapping( group, D3DRMMAP_PERSPCORRECT );
//	texture->Release();
//	texture=0;

	//------- FRAME --------
	LPDIRECT3DRMFRAME frame;
	d3drm->CreateFrame( scene, &frame );
	frame->AddVisual( mesh );
	frame->SetRotation( scene,
			D3DVALUE(0), D3DVALUE(1), D3DVALUE(0),
			D3DVALUE(.04) );

	static CallbackData cbdata;
	cbdata.mesh=mesh;
	cbdata.group=group;
	frame->AddMoveCallback( UpdateCube, &cbdata );
	frame->Release();
	frame=0;

	// --------- LIGHTS --------
	LPDIRECT3DRMLIGHT dlight;
	d3drm->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL,
			D3DVALUE(1.00), D3DVALUE(1.00), D3DVALUE(1.00), 
			&dlight );

	LPDIRECT3DRMLIGHT alight;
	d3drm->CreateLightRGB(D3DRMLIGHT_AMBIENT,
			D3DVALUE(0.50), D3DVALUE(0.50), D3DVALUE(0.50), 
			&alight );

	LPDIRECT3DRMFRAME lightframe;
	d3drm->CreateFrame( scene, &lightframe );
	lightframe->SetOrientation( scene, 
			D3DVALUE(0), D3DVALUE(-1), D3DVALUE(1),
			D3DVALUE(0), D3DVALUE(1), D3DVALUE(0) );

	lightframe->AddLight( dlight );
	lightframe->AddLight( alight );

	dlight->Release();
	dlight=0;
	alight->Release();
	alight=0;
	lightframe->Release();
	lightframe=0;

	//------ CAMERA-----------
	d3drm->CreateFrame( scene, &camera );
	camera->SetPosition( scene, 
			D3DVALUE(0), D3DVALUE(0), D3DVALUE(-50) );
	d3drm->CreateViewport( device, camera, 0, 0,	
			device->GetWidth(), device->GetHeight(), 
			&viewport );

	return TRUE;
}



BOOL CActiveD3DCtrl::CreateDevice()
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

void CActiveD3DCtrl::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	COleControl::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	LPDIRECT3DRMWINDEVICE windev;
	if (device)
	{
		if (device->QueryInterface( IID_IDirect3DRMWinDevice, (void**)&windev)==0) 
		{   
			if (windev->HandleActivate((unsigned short)MAKELONG((WORD)nState,(WORD)0))!=0) 
				AfxMessageBox("windev->HandleActivate() failure");
			windev->Release();
		}
		else 
			AfxMessageBox("device->QueryInterface(WinDevice) failure");
	}
	//CFrameWnd::OnActivate(state, other, minimize);
	
}

int CActiveD3DCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	HRESULT r;
	r = Direct3DRMCreate(&d3drm);
	if (r!=D3DRM_OK)
	{
		AfxMessageBox("Direct3DRMCreate() failed");
		return -1;
	}
	return 0;
	
	
}

void CActiveD3DCtrl::OnDestroy() 
{
	COleControl::OnDestroy();
	
	// TODO: Add your message handler code here
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

BOOL CActiveD3DCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
		COLORREF bgcolor;
	if (scene)
	{
		D3DCOLOR scenecolor=scene->GetSceneBackground();
		bgcolor=D3DCOLOR_2_COLORREF(scenecolor);
	}
	else
		bgcolor=RGB(1,1,1);

	CBrush br( bgcolor );
	CRect rc;
	GetClientRect(&rc);
	pDC->FillRect(&rc, &br);
//	return TRUE;
	
	return COleControl::OnEraseBkgnd(pDC);
}

void CActiveD3DCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	mousestate = nFlags;
	mousex = point.x;
	mousey = point.y;
	
	COleControl::OnMouseMove(nFlags, point);
}

void CActiveD3DCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	CFrameWnd::OnSize(nType, cx, cy);

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

D3DVALUE CActiveD3DCtrl::ScaleMesh(LPDIRECT3DRMMESHBUILDER mesh, D3DVALUE dim)
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

GUID* CActiveD3DCtrl::GetGUID()
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

void CActiveD3DCtrl::UpdateCube(LPDIRECT3DRMFRAME frame, void* p, D3DVALUE)
{
	CallbackData* data=(CallbackData*)p;
	static const D3DVALUE lim=D3DVALUE(5);
	static D3DVALUE control;
	static D3DVALUE inc=D3DVALUE(.25);
	static D3DRMVERTEX vert[24];

	data->mesh->GetVertices( data->group, 0, 24, vert );

	vert[0].position.x+=inc;
	vert[0].position.y+=inc;
	vert[0].position.z+=inc;
	vert[6].position.x+=inc;
	vert[6].position.y+=inc;
	vert[6].position.z+=inc;
	vert[8].position.x+=inc;
	vert[8].position.y+=inc;
	vert[8].position.z+=inc;
	vert[14].position.x+=inc;
	vert[14].position.y+=inc;
	vert[14].position.z+=inc;
	vert[18].position.x+=inc;
	vert[18].position.y+=inc;
	vert[18].position.z+=inc;
	vert[20].position.x+=inc;
	vert[20].position.y+=inc;
	vert[20].position.z+=inc;

	data->mesh->SetVertices( data->group, 0, 24, vert );

	control+=inc;
	if (control>lim || control<-lim)
		inc=-inc;

	static UINT delay;
	if (++delay<20)
		return;
	delay=0;

	LPDIRECT3DRMFRAME scene;
	frame->GetScene( &scene );

	D3DVECTOR spinvect;
	D3DRMVectorRandom( &spinvect );
	D3DVALUE spin=D3DDivide( rand()%50+1, 400 );
	frame->SetRotation( scene, 
			spinvect.x, spinvect.y, spinvect.z, 
			spin );
}

void CActiveD3DCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Render();
	
	COleControl::OnRButtonDown(nFlags, point);
}

void CActiveD3DCtrl::Render()
{
	if(scene && viewport && device){
		scene->Move(D3DVALUE(1.0));
		viewport->Clear();
		viewport->Render(scene);
		device->Update();
	}

}

void CActiveD3DCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	scene->Move(D3DVALUE(1.0));
	    viewport->Clear();
	    viewport->Render(scene);
	    device->Update();
	
	COleControl::OnTimer(nIDEvent);
}
