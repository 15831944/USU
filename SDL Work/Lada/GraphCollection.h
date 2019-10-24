// GraphCollection.h: interface for the CGraphCollection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHCOLLECTION_H__CC608E81_1573_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_GRAPHCOLLECTION_H__CC608E81_1573_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGraphCollection  
{
public:
	int whichPane;
	CGraphCollection(BOOL CreateNew = TRUE);
	virtual ~CGraphCollection();
	CGraphCollection & operator=(const CGraphCollection & right);
	ReadObject(CArchive & ar);
	WriteObject(CArchive & ar);
//attributes:
	CString name;
	int nItems;
	BOOL isItemChecked[15];
	int  DataIndex[15];
};

#endif // !defined(AFX_GRAPHCOLLECTION_H__CC608E81_1573_11D5_B690_0080AD8FBDCC__INCLUDED_)
