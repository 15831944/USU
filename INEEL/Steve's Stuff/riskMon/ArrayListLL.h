// ArrayListLL.h: interface for the ArrayListLL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ArrayListLL_H__F7CA36D1_7798_11D5_8D12_00104B945A14__INCLUDED_)
#define AFX_ArrayListLL_H__F7CA36D1_7798_11D5_8D12_00104B945A14__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
typedef char NAME24[25];
typedef char NameList[1000][25];

//the object of each node
struct ALNode
{
	char (*BENames)[25];  //the array of basic event names
	char (*DescOfBEs)[61];  //the description of each basic event
	char (*CompGroups)[25];
	int *Group;
	CString ArrayName;
	CString ArrayDesc;
	int Length;  //how many names are in the array
	int NumOfCompGroups;
	ALNode *Next;
};

class ArrayListLL  
{
public:
	int GetNumOfCompBEGroups();
	bool GetCompBEGroupName(int, char *);
	int CompBEGroupExists(CString);
	void Delete();
	bool SetLook(char *);
	bool GetBEName(int, char *, char *, int);
	bool Exists(char *);
	
	int NodeSize(char *);
	ArrayListLL();
	virtual ~ArrayListLL();
	
	void Push(char *arrayName, char * arraydesc, int size, char (*newNames)[25], char (*)[61]);
	int Count();

private:
	ALNode *Head;
	int Total;  //how many systems are in the linked list
	ALNode *DesiredNode;
};

#endif // !defined(AFX_ArrayListLL_H__F7CA36D1_7798_11D5_8D12_00104B945A14__INCLUDED_)
