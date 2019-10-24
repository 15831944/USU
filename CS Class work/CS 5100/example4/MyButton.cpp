// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "Drawing.h"
#include "MyButton.h"
#include "ModelessD.h"
#include "DrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyButton

MyButton::MyButton()
{
	dialogNumber = 0;
}

MyButton::~MyButton()
{
}


BEGIN_MESSAGE_MAP(MyButton, CButton)
	//{{AFX_MSG_MAP(MyButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyButton message handlers

void MyButton::OnClicked() 
{
	ModelessD * p = new ModelessD(this);
	p->Create();
}
