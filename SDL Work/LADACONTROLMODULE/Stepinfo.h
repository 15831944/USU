// Stepinfo.h: interface for the Stepinfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEPINFRO_H__EA80EA35_8326_11D4_A864_0000E880BB29__INCLUDED_)
#define AFX_STEPINFRO_H__EA80EA35_8326_11D4_A864_0000E880BB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "LADASetupDlg.h"
class Stepinfo  
{
public:

	CString m_Text;
	Stepinfo();
	Stepinfo(int x, CString y, int z,CString a[], CString t);
	virtual ~Stepinfo();
	int m_checks;
	int m_step;
	CString m_title;
	CString m_Steps[9];
};

#endif // !defined(AFX_STEPINFRO_H__EA80EA35_8326_11D4_A864_0000E880BB29__INCLUDED_)
