// This is Version 1.0 PLEASE DOCUMENT CHANGES
// Step.cpp : implementation file
//

#include "stdafx.h"
//#include "LADASetup.h"
#include "Step.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Step dialog


Step::Step(int x, CString y, int z,CString a[])
{
	m_checks=z;
	m_step=x;
	m_title=y;
	for (int b=0;b<9;b++)
		m_Steps[b]=a[b];
}
Step::Step()
{
}



