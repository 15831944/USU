// Stepinfro.cpp: implementation of the Stepinfro class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "LADASetup.h"
#include "Stepinfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Stepinfo::Stepinfo()
{

}

Stepinfo::~Stepinfo()
{

}

Stepinfo::Stepinfo(int x, CString y, int z,CString a[],CString t)
{
	m_checks=z;
	m_step=x;
	m_title=y;
	for (int b=0;b<9;b++)
		m_Steps[b]=a[b];
	m_Text=t;
}

