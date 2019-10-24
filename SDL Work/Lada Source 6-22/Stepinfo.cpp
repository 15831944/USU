// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This class holds the information for each step during checkout and setup
// Stepinfo.cpp: implementation of the Stepinfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Stepinfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Basic constructor
Stepinfo::Stepinfo()
{

}

//Basic destructor
Stepinfo::~Stepinfo()
{

}

// Different Constructor
// x is the step
// y is the title of that step
// z is the amount of substeps in the set
// a is the list of substep 
// t is the title for the instruction box
Stepinfo::Stepinfo(int x, CString y, int z,CString a[],CString t)
{
	m_checks=z;
	m_step=x;
	m_title=y;
	for (int b=0;b<9;b++)
		m_Steps[b]=a[b];
	m_Text=t;
}

