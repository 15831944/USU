// TreeListLL.h: interface for the TreeListLL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREELISTLL_H__F7CA36D1_7798_11D5_8D12_00104B945A14__INCLUDED_)
#define AFX_TREELISTLL_H__F7CA36D1_7798_11D5_8D12_00104B945A14__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//the object of each node
struct TLNode
{
	char *BENames;
	CString TreeName;
	int Length;
	TLNode *next;
};

class TreeListLL  
{
public:
	TreeListLL();
	virtual ~TreeListLL();
	void Push(int size, newNames);
	int Count();
	bool Find(char *);
private:
	TLNode *Head;
	int Total;

};

#endif // !defined(AFX_TREELISTLL_H__F7CA36D1_7798_11D5_8D12_00104B945A14__INCLUDED_)
