#if !defined(AFX_STEP_H__EA80EA32_8326_11D4_A864_0000E880BB29__INCLUDED_)
#define AFX_STEP_H__EA80EA32_8326_11D4_A864_0000E880BB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Step.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Step dialog
#include "LADASetupDlg.h"

class Step 
{

public:
	void Reset(CLADASetupDlg);
	Step(int x, CString y, int z,CString a[]); 
	Step();// standard constructor


// Implementation
private:
	int m_step;
	CString m_title;
	int m_checks;
	CString m_Steps[9];

};


#endif // !defined(AFX_STEP_H__EA80EA32_8326_11D4_A864_0000E880BB29__INCLUDED_)
