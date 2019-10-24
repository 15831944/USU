// StringLList.h: interface for the CStringLList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGLLIST_H__2606F131_5A83_11D5_8CF2_00104B945A14__INCLUDED_)
#define AFX_STRINGLLIST_H__2606F131_5A83_11D5_8CF2_00104B945A14__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "Node.h"



class CStringLList  
{
public:
	void Delete();
	void Push(CString, double Lev= 0.0);
	double Pop(CString &);
	CStringLList(CStringLList &);
	CStringLList();
	virtual ~CStringLList();
	int Count();
private:
	Node * head;
	int total;
	Node * tail;
};

#endif // !defined(AFX_STRINGLLIST_H__2606F131_5A83_11D5_8CF2_00104B945A14__INCLUDED_)
