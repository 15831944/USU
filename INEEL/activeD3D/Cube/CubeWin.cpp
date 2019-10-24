#include <AfxWin.h>
#include <AfxExt.h>
#define INITGUID
#include <ddraw.h>
#include <d3d.h>
#include <d3drm.h>
#include <d3drmwin.h>
#include "resource.h"
#include "CubeWin.h"
#include "HelpDialog.h"

#pragma comment (lib,"ddraw.lib")
#pragma comment (lib,"d3drm.lib")
#pragma comment (lib,"winmm.lib")


BEGIN_MESSAGE_MAP(CubeWin, RMWin)
	//{{AFX_MSG_MAP(CubeWin)
	ON_COMMAND(ID_RENDER_WIREFRAME, OnRenderWireframe)
	ON_COMMAND(ID_RENDER_FLAT, OnRenderFlat)
	ON_COMMAND(ID_RENDER_GOURAUD, OnRenderGouraud)
	ON_UPDATE_COMMAND_UI(ID_RENDER_WIREFRAME, OnUpdateRenderWireframe)
	ON_UPDATE_COMMAND_UI(ID_RENDER_FLAT, OnUpdateRenderFlat)
	ON_UPDATE_COMMAND_UI(ID_RENDER_GOURAUD, OnUpdateRenderGouraud)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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

CubeWin::CubeWin()
{
	mesh=0;
	group=0;
}

BOOL CubeWin::CreateScene()
{
	// ------- MESH --------
	d3drm->CreateMesh( &mesh );
	mesh->AddGroup( 24, 6, 4, vertorder, &group );
	mesh->SetVertices( group, 0, 24, vertexlist );
	mesh->Translate( D3DVALUE(-0.5), D3DVALUE(-0.5), D3DVALUE(-0.5) );
	mesh->Scale( D3DVALUE(15), D3DVALUE(15), D3DVALUE(15) );

	//-------- TEXTURE -------
	HRSRC texture_id = FindResource( NULL, 
			MAKEINTRESOURCE(IDR_WIN95TEXTURE), "TEXTURE" );
	LPDIRECT3DRMTEXTURE texture;
	d3drm->LoadTextureFromResource( texture_id, &texture );
	mesh->SetGroupTexture( group, texture );
	mesh->SetGroupMapping( group, D3DRMMAP_PERSPCORRECT );
	texture->Release();
	texture=0;

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

void CubeWin::UpdateCube(LPDIRECT3DRMFRAME frame, void* p, D3DVALUE)
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

void CubeWin::OnRenderWireframe() 
{
	if (mesh)
		mesh->SetGroupQuality( group, D3DRMRENDER_WIREFRAME );
}

void CubeWin::OnRenderFlat() 
{
	if (mesh)
		mesh->SetGroupQuality( group, D3DRMRENDER_FLAT );
}

void CubeWin::OnRenderGouraud() 
{
	if (mesh)
		mesh->SetGroupQuality( group, D3DRMRENDER_GOURAUD );
}

void CubeWin::OnUpdateRenderWireframe(CCmdUI* pCmdUI) 
{
	if (mesh)
	{
		D3DRMRENDERQUALITY meshquality = mesh->GetGroupQuality( group );
		pCmdUI->SetCheck( meshquality==D3DRMRENDER_WIREFRAME );
	}
}

void CubeWin::OnUpdateRenderFlat(CCmdUI* pCmdUI) 
{
	if (mesh)
	{
		D3DRMRENDERQUALITY meshquality = mesh->GetGroupQuality( group );
		pCmdUI->SetCheck( meshquality==D3DRMRENDER_FLAT );
	}
}

void CubeWin::OnUpdateRenderGouraud(CCmdUI* pCmdUI) 
{
	if (mesh)
	{
		D3DRMRENDERQUALITY meshquality = mesh->GetGroupQuality( group );
		pCmdUI->SetCheck( meshquality==D3DRMRENDER_GOURAUD );
	}
}

void CubeWin::OnHelpAbout() 
{
	HelpDialog dialog;
	dialog.DoModal();
}
