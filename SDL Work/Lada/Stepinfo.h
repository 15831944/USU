// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This class holds the information for each step during checkout and setup
// Stepinfo.h: interface for the Stepinfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEPINFRO_H__EA80EA35_8326_11D4_A864_0000E880BB29__INCLUDED_)
#define AFX_STEPINFRO_H__EA80EA35_8326_11D4_A864_0000E880BB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class Stepinfo  
{
public:
	CString m_Text;												// Title for the instruction box
	Stepinfo();													// Constructor
	Stepinfo(int x, CString y, int z,CString a[], CString t);	// 2nd Constructor
	virtual ~Stepinfo();										// Destructor
	int m_checks;												// Number of substeps
	int m_step;													// Step number
	CString m_title;											// Step title
	CString m_Steps[9];											// Substep Titles
};

#endif // !defined(AFX_STEPINFRO_H__EA80EA35_8326_11D4_A864_0000E880BB29__INCLUDED_)
