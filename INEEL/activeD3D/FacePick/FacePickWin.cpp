#include <AfxWin.h>
#include <AfxExt.h>
#include <math.h>
#define INITGUID
#include <ddraw.h>
#include <d3d.h>
#include <d3drm.h>
#include <d3drmwin.h>
#include "FacePickWin.h"
#include "resource.h"
#include "HelpDialog.h"

#pragma comment (lib,"ddraw.lib")
#pragma comment (lib,"d3drm.lib")
#pragma comment (lib,"winmm.lib")


BEGIN_MESSAGE_MAP(FacePickWin, RMWin)
	//{{AFX_MSG_MAP(FacePickWin)
	ON_COMMAND(ID_RENDER_WIREFRAME, OnRenderWireframe)
	ON_COMMAND(ID_RENDER_UNLIT, OnRenderUnlit)
	ON_COMMAND(ID_RENDER_GOURAUD, OnRenderGouraud)
	ON_COMMAND(ID_RENDER_FLAT, OnRenderFlat)
	ON_UPDATE_COMMAND_UI(ID_RENDER_WIREFRAME, OnUpdateRenderWireframe)
	ON_UPDATE_COMMAND_UI(ID_RENDER_FLAT, OnUpdateRenderFlat)
	ON_UPDATE_COMMAND_UI(ID_RENDER_UNLIT, OnUpdateRenderUnlit)
	ON_UPDATE_COMMAND_UI(ID_RENDER_GOURAUD, OnUpdateRenderGouraud)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_COLORS_FACE, OnColorsFace)
	ON_COMMAND(ID_COLORS_MESH, OnColorsMesh)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_WM_DESTROY()
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL FacePickWin::drag;
BOOL FacePickWin::end_drag;
int FacePickWin::last_x;
int FacePickWin::last_y;


FacePickWin::FacePickWin()
{
	meshbuilder=0;
	meshframe=0;
	pickcolor=D3DRGB(1,0,0);
	meshscale=D3DVALUE(1);
}

BOOL FacePickWin::CreateScene()
{
	scene->SetSceneBackgroundRGB( D3DVALUE(.2), D3DVALUE(.2), D3DVALUE(.2) );

	// ------- MESH --------
	D3DRMLOADRESOURCE resinfo;
	resinfo.hModule=NULL;
	resinfo.lpName=MAKEINTRESOURCE( IDR_D3DMESH );
	resinfo.lpType="MESH";
	d3drm->CreateMeshBuilder( &meshbuilder );
	meshbuilder->Load( &resinfo, NULL, D3DRMLOAD_FROMRESOURCE, NULL, NULL );
	meshbuilder->SetQuality( D3DRMRENDER_FLAT );
	ScaleMesh( meshbuilder, D3DVALUE(25) );

	//------- FRAME ------
	d3drm->CreateFrame( scene, &meshframe );
	meshframe->AddVisual( meshbuilder );
	meshframe->SetRotation( scene,
			D3DVALUE(1), D3DVALUE(0), D3DVALUE(0),
			D3DVALUE(.05) );
	meshframe->AddMoveCallback( UpdateDrag, NULL );

	// --------- LIGHTS --------
	LPDIRECT3DRMLIGHT dlight;
	d3drm->CreateLightRGB( D3DRMLIGHT_DIRECTIONAL,
			D3DVALUE(1.00), D3DVALUE(1.00), D3DVALUE(1.00), 
			&dlight );

	LPDIRECT3DRMLIGHT alight;
	d3drm->CreateLightRGB( D3DRMLIGHT_AMBIENT,
			D3DVALUE(0.40), D3DVALUE(0.40), D3DVALUE(0.40), 
			&alight );

	LPDIRECT3DRMFRAME lightframe;
	d3drm->CreateFrame( scene, &lightframe );
	lightframe->AddLight( dlight );
	lightframe->AddLight( alight );
	lightframe->SetOrientation( scene, 
			D3DVALUE(0), D3DVALUE(-1), D3DVALUE(1),
			D3DVALUE(0), D3DVALUE(1), D3DVALUE(0) );

	dlight->Release();
	dlight=0;
	alight->Release();
	alight=0;
	lightframe->Release();
	lightframe=0;

	//------ CAMERA-----------
	d3drm->CreateFrame( scene, &camera );
	camera->SetPosition( scene, D3DVALUE(0), D3DVALUE(0), D3DVALUE(-50));
	d3drm->CreateViewport( device, camera, 0, 0,	
			device->GetWidth(), device->GetHeight(), 
			&viewport);

	return TRUE;
}

void FacePickWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int faceindex=PickFace( point );
	if (faceindex!=-1)
	{
		LPDIRECT3DRMFACEARRAY facearray;
		meshbuilder->GetFaces( &facearray );

		LPDIRECT3DRMFACE face;
		facearray->GetElement( faceindex, &face );
		face->SetColor( pickcolor );

		face->Release();
		facearray->Release();
	}
	else if (!drag)
	{
		drag=TRUE;
		last_x = GetMouseX();
		last_y = GetMouseY();
		SetCapture();
		ShowCursor(FALSE);
	}	
	RMWin::OnLButtonDown(nFlags, point);
}

void FacePickWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (drag)
	{
		end_drag=TRUE;
		ReleaseCapture();
		ShowCursor(TRUE);
	}
	RMWin::OnLButtonUp(nFlags, point);
}

void FacePickWin::UpdateDrag(LPDIRECT3DRMFRAME frame, void*, D3DVALUE)
{
	if (drag)
	{   
		double delta_x = GetMouseX() - last_x;
		double delta_y = GetMouseY() - last_y;
		last_x = GetMouseX();
		last_y = GetMouseY();
		double delta_r = sqrt(delta_x * delta_x + delta_y * delta_y);
		double radius = 50;
		double denom= sqrt(radius * radius + delta_r * delta_r);

		if (!(delta_r == 0 || denom == 0))
			frame->SetRotation( 0,
					D3DDivide(-delta_y, delta_r),
					D3DDivide(-delta_x, delta_r),
					D3DVALUE(0.0),
					D3DDivide(delta_r, denom) );
	}

	if (end_drag)
	{
		drag=FALSE;
		end_drag=FALSE;
	}
}

void FacePickWin::OnIdle(long)
{
	if (drag && meshframe)
	{
		meshframe->SetRotation( 0, 
				D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0), 
				D3DVAL(0.0) );
	}
}

int FacePickWin::PickFace( const CPoint& point )
{
	HRESULT r;
	LPDIRECT3DRMPICKEDARRAY pickarray;

	viewport->Pick( point.x, point.y, &pickarray );

	int faceindex=-1;
	DWORD numpicks=pickarray->GetSize();
	if (numpicks>0)
	{
		LPDIRECT3DRMVISUAL visual;
		LPDIRECT3DRMFRAMEARRAY framearray;
		D3DRMPICKDESC pickdesc;

		r=pickarray->GetPick( 0, &visual, &framearray, &pickdesc );
		if (r==D3DRM_OK)
		{
			faceindex=pickdesc.ulFaceIdx;
			visual->Release();
			framearray->Release();
		}
	}
	pickarray->Release();
	return faceindex;
}

void FacePickWin::OnDestroy() 
{
	RMWin::OnDestroy();
	
	meshbuilder->Release();
	meshbuilder=0;
}

void FacePickWin::OnColorsFace() 
{
	CColorDialog dialog( 0, CC_RGBINIT );
	dialog.m_cc.rgbResult = D3DCOLOR_2_COLORREF( pickcolor );
	if (dialog.DoModal()==IDOK)
	{
		COLORREF clr = dialog.GetColor();
		pickcolor = COLORREF_2_D3DCOLOR( clr );
	}
}

void FacePickWin::OnColorsMesh() 
{
	CColorDialog dialog;
	if (dialog.DoModal()==IDOK)
	{
		COLORREF clr = dialog.GetColor();
		D3DCOLOR meshcolor = COLORREF_2_D3DCOLOR( clr );
		meshbuilder->SetColor( meshcolor );
	}
}

void FacePickWin::OnFileOpen() 
{
	static char BASED_CODE filter[] = "X Files (*.x)|*.x|All Files (*.*)|*.*||";
	CFileDialog opendialog( TRUE, 0, 0, OFN_FILEMUSTEXIST, filter, this );
	if ( opendialog.DoModal() == IDOK )
	{
		CWaitCursor cur;
		CString filename = opendialog.GetPathName();

		LPDIRECT3DRMMESHBUILDER builder;
		d3drm->CreateMeshBuilder( &builder );
		HRESULT r=builder->Load( (void*)(LPCTSTR)filename, 
				NULL, D3DRMLOAD_FROMFILE, NULL, NULL );
		if (r!=D3DRM_OK)
		{
			CString msg;
			msg.Format( "Failed to load file\n'%s'", filename );
			AfxMessageBox( msg );
			return;
		}

		meshframe->DeleteVisual( meshbuilder );
		meshbuilder->Release();
		meshbuilder=builder;
		meshframe->AddVisual( meshbuilder );
		meshscale=ScaleMesh( meshbuilder, D3DVALUE(25) );
	}
}

void FacePickWin::OnFileSave() 
{
	static char BASED_CODE filter[] = "X Files (*.x)|*.x||";
	CFileDialog opendialog( FALSE, ".x", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter );
	if ( opendialog.DoModal() == IDOK )
	{
		CWaitCursor cur;
		CString filename = opendialog.GetPathName();
		D3DVALUE restorescale=D3DVALUE(1)/meshscale;
		meshbuilder->Scale( restorescale, restorescale, restorescale );
		meshbuilder->Save( filename, D3DRMXOF_BINARY, D3DRMXOFSAVE_ALL );	
		meshbuilder->Scale( meshscale, meshscale, meshscale );
	}
}

void FacePickWin::OnRenderWireframe() 
{
	if (meshbuilder)
		meshbuilder->SetQuality( D3DRMRENDER_WIREFRAME );
}

void FacePickWin::OnRenderUnlit() 
{
	if (meshbuilder)
		meshbuilder->SetQuality( D3DRMRENDER_UNLITFLAT );
}

void FacePickWin::OnRenderFlat() 
{
	if (meshbuilder)
		meshbuilder->SetQuality( D3DRMRENDER_FLAT );
}

void FacePickWin::OnRenderGouraud() 
{
	if (meshbuilder)
		meshbuilder->SetQuality( D3DRMRENDER_GOURAUD );
}

void FacePickWin::OnUpdateRenderWireframe(CCmdUI* pCmdUI) 
{
	if (meshbuilder)
	{
		D3DRMRENDERQUALITY meshquality=meshbuilder->GetQuality();
		pCmdUI->SetCheck( meshquality==D3DRMRENDER_WIREFRAME );
	}
}

void FacePickWin::OnUpdateRenderUnlit(CCmdUI* pCmdUI) 
{
	if (meshbuilder)
	{
		D3DRMRENDERQUALITY meshquality=meshbuilder->GetQuality();
		pCmdUI->SetCheck( meshquality==D3DRMRENDER_UNLITFLAT );
	}
}

void FacePickWin::OnUpdateRenderFlat(CCmdUI* pCmdUI) 
{
	if (meshbuilder)
	{
		D3DRMRENDERQUALITY meshquality=meshbuilder->GetQuality();
		pCmdUI->SetCheck( meshquality==D3DRMRENDER_FLAT );
	}
}

void FacePickWin::OnUpdateRenderGouraud(CCmdUI* pCmdUI) 
{
	if (meshbuilder)
	{
		D3DRMRENDERQUALITY meshquality=meshbuilder->GetQuality();
		pCmdUI->SetCheck( meshquality==D3DRMRENDER_GOURAUD );
	}
}

void FacePickWin::OnHelpAbout() 
{
	HelpDialog dialog;
	dialog.DoModal();
}
