// Node.h: interface for the Node class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__2606F133_5A83_11D5_8CF2_00104B945A14__INCLUDED_)
#define AFX_NODE_H__2606F133_5A83_11D5_8CF2_00104B945A14__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class Node  
{
public:
	CString item;
	Node * next;
	double riskLev;

};

#endif // !defined(AFX_NODE_H__2606F133_5A83_11D5_8CF2_00104B945A14__INCLUDED_)
